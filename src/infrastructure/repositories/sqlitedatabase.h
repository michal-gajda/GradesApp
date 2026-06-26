#ifndef INFRASTRUCTURE_REPOSITORIES_SQLITEDATABASE_H
#define INFRASTRUCTURE_REPOSITORIES_SQLITEDATABASE_H

#include <QString>

namespace Infrastructure {

class SqliteDatabase
{
public:
    SqliteDatabase(const QString &dbPath, const QString &connectionName);
    ~SqliteDatabase();

    const QString &connectionName() const { return m_connectionName; }

private:
    void createSchema();
    QString m_connectionName;
};

}

#endif

