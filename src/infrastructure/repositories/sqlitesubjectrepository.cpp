#include "infrastructure/repositories/sqlitesubjectrepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <stdexcept>

namespace Infrastructure {

static void check(const QSqlQuery &q, const char *ctx)
{
    if (q.lastError().isValid()) {
        throw std::runtime_error(std::string(ctx) + ": " + q.lastError().text().toStdString());
    }
}

SqliteSubjectRepository::SqliteSubjectRepository(const QString &connectionName)
    : m_conn(connectionName) {}

QVector<Domain::Subject> SqliteSubjectRepository::findAll() const
{
    QSqlDatabase db = QSqlDatabase::database(m_conn);
    QSqlQuery q(db);
    q.exec("SELECT name FROM subjects ORDER BY position");
    check(q, "findAll subjects");

    QVector<Domain::Subject> result;

    while (q.next())
    {
        try {
            result.append(Domain::Subject(Domain::SubjectName(q.value(0).toString())));
        } catch (...) {
        }
    }
    return result;
}

void SqliteSubjectRepository::saveAll(const QVector<Domain::Subject> &subjects)
{
    QSqlDatabase db = QSqlDatabase::database(m_conn);
    QSqlQuery q(db);
    q.exec("DELETE FROM subjects");
    check(q, "saveAll delete subjects");

    for (int i = 0; i < subjects.size(); ++i)
    {
        q.prepare("INSERT INTO subjects (name, position) VALUES (:n, :p)");
        q.bindValue(":n", subjects[i].name().value());
        q.bindValue(":p", i);
        q.exec();
        check(q, "saveAll insert subject");
    }
}

}
