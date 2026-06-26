#ifndef INFRASTRUCTURE_REPOSITORIES_SQLITESUBJECTREPOSITORY_H
#define INFRASTRUCTURE_REPOSITORIES_SQLITESUBJECTREPOSITORY_H

#include "domain/repositories/isubjectrepository.h"
#include <QString>

namespace Infrastructure {

class SqliteSubjectRepository : public Domain::ISubjectRepository
{
public:
    explicit SqliteSubjectRepository(const QString &connectionName);

    QVector<Domain::Subject> findAll() const override;
    void saveAll(const QVector<Domain::Subject> &subjects) override;

private:
    QString m_conn;
};

} // namespace Infrastructure

#endif // INFRASTRUCTURE_REPOSITORIES_SQLITESUBJECTREPOSITORY_H

