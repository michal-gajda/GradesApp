#include "infrastructure/repositories/sqlitestudentrepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <stdexcept>
#include <algorithm>

namespace Infrastructure {

static void check(const QSqlQuery &q, const char *ctx)
{
    if (q.lastError().isValid()) {
        throw std::runtime_error(std::string(ctx) + ": " + q.lastError().text().toStdString());
    }
}

SqliteStudentRepository::SqliteStudentRepository(const QString &connectionName)
    : m_conn(connectionName) {}

QVector<Domain::Student> SqliteStudentRepository::findAll() const
{
    QSqlDatabase db = QSqlDatabase::database(m_conn);
    QSqlQuery q(db);
    q.exec("SELECT id, first_name, last_name, album_number FROM students ORDER BY last_name, first_name");
    check(q, "findAll students");

    QVector<Domain::Student> result;

    while (q.next()){
        int id = q.value(0).toInt();

        try
        {
            Domain::Student s(q.value(1).toString(), q.value(2).toString(),
                            Domain::AlbumNumber(q.value(3).toString()));
            QSqlQuery gq(db);
            gq.prepare("SELECT subject_name, passed FROM grades WHERE student_id=:id ORDER BY id");
            gq.bindValue(":id", id);
            gq.exec();
            check(gq, "findAll grades");

            while (gq.next())
            {
                s.addSubject(gq.value(0).toString(), gq.value(1).toBool());
            }
            result.append(s);
        }
        catch (...) {}
    }

    return result;
}

std::optional<Domain::Student> SqliteStudentRepository::findByAlbumNumber(const Domain::AlbumNumber &a) const
{
    for (const auto &s : findAll()){
        if (s.albumNumber() == a) {
            return s;
        }
    }

    return std::nullopt;
}

void SqliteStudentRepository::save(const Domain::Student &student)
{
    QSqlDatabase db = QSqlDatabase::database(m_conn);
    QSqlQuery q(db);
    q.prepare(
        "INSERT INTO students (first_name, last_name, album_number) VALUES (:f,:l,:a) "
        "ON CONFLICT(album_number) DO UPDATE SET first_name=excluded.first_name, last_name=excluded.last_name");
    q.bindValue(":f", student.firstName());
    q.bindValue(":l", student.lastName());
    q.bindValue(":a", student.albumNumber().value());
    q.exec();
    check(q, "save student upsert");

    q.prepare("SELECT id FROM students WHERE album_number=:a");
    q.bindValue(":a", student.albumNumber().value());
    q.exec(); check(q, "save id lookup"); q.next();
    int sid = q.value(0).toInt();

    q.prepare("DELETE FROM grades WHERE student_id=:id");
    q.bindValue(":id", sid); q.exec(); check(q, "save delete grades");

        const auto &subjects = student.subjects();

        for (const auto &subject : subjects) {
            q.prepare("INSERT INTO grades (student_id, subject_name, passed) VALUES (:s,:n,:p)");
            q.bindValue(":s", sid);
            q.bindValue(":n", subject.name);
            q.bindValue(":p", subject.passed ? 1 : 0);
        q.exec(); check(q, "save insert grade");
    }
}

void SqliteStudentRepository::remove(const Domain::AlbumNumber &albumNumber)
{
    QSqlDatabase db = QSqlDatabase::database(m_conn);
    QSqlQuery q(db);
    q.prepare("SELECT id FROM students WHERE album_number=:a");
    q.bindValue(":a", albumNumber.value()); q.exec(); check(q, "remove id lookup");

    if (!q.next()) {
        return;
    }

    int sid = q.value(0).toInt();

    q.prepare("DELETE FROM grades WHERE student_id=:id");
    q.bindValue(":id", sid); q.exec(); check(q, "remove grades");

    q.prepare("DELETE FROM students WHERE id=:id");
    q.bindValue(":id", sid); q.exec(); check(q, "remove student");
}

void SqliteStudentRepository::saveAll(const QVector<Domain::Student> &students)
{
    QSqlDatabase db = QSqlDatabase::database(m_conn);
    QSqlQuery q(db);
    q.exec("DELETE FROM grades"); check(q, "saveAll del grades");
    q.exec("DELETE FROM students"); check(q, "saveAll del students");

    for (const auto &s : students) {
        save(s);
    }
}

}
