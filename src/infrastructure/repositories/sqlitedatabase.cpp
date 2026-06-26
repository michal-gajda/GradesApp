#include "infrastructure/repositories/sqlitedatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <stdexcept>

namespace Infrastructure {

SqliteDatabase::SqliteDatabase(const QString &dbPath, const QString &connectionName)
    : m_connectionName(connectionName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        throw std::runtime_error("Cannot open database: " + db.lastError().text().toStdString());
    }

    createSchema();
}

SqliteDatabase::~SqliteDatabase()
{
    QSqlDatabase::database(m_connectionName).close();
    QSqlDatabase::removeDatabase(m_connectionName);
}

void SqliteDatabase::createSchema()
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery q(db);
    q.exec("PRAGMA foreign_keys = ON");

    q.exec(R"(CREATE TABLE IF NOT EXISTS subjects (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        position INTEGER NOT NULL DEFAULT 0
    ))");

    if (q.lastError().isValid()) {
        throw std::runtime_error("Schema error (subjects): " + q.lastError().text().toStdString());
    }

    q.exec(R"(CREATE TABLE IF NOT EXISTS students (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        first_name TEXT NOT NULL,
        last_name TEXT NOT NULL,
        album_number TEXT NOT NULL UNIQUE
    ))");

    if (q.lastError().isValid()) {
        throw std::runtime_error("Schema error (students): " + q.lastError().text().toStdString());
    }

    bool hasSubjectNameColumn = false;
    bool hasLegacyGradesTable = false;
    q.exec("PRAGMA table_info(grades)");

    if (q.lastError().isValid()) {
        throw std::runtime_error("Schema error (grades info): " + q.lastError().text().toStdString());
    }

    while (q.next()) {
        hasLegacyGradesTable = true;
        if (q.value(1).toString() == "subject_name") {
            hasSubjectNameColumn = true;
        }
    }

    if (hasLegacyGradesTable && !hasSubjectNameColumn) {
        q.exec("DROP TABLE grades");

        if (q.lastError().isValid()) {
            throw std::runtime_error("Schema error (drop legacy grades): " + q.lastError().text().toStdString());
        }
    }

    q.exec(R"(CREATE TABLE IF NOT EXISTS grades (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        student_id INTEGER NOT NULL REFERENCES students(id) ON DELETE CASCADE,
        subject_name TEXT NOT NULL,
        passed INTEGER NOT NULL DEFAULT 0
    ))");

    if (q.lastError().isValid()) {
        throw std::runtime_error("Schema error (grades): " + q.lastError().text().toStdString());
    }
}

}
