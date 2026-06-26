#ifndef INFRASTRUCTURE_REPOSITORIES_SQLITESTUDENTREPOSITORY_H
#define INFRASTRUCTURE_REPOSITORIES_SQLITESTUDENTREPOSITORY_H

#include "domain/repositories/istudentrepository.h"
#include <QString>

namespace Infrastructure {

class SqliteStudentRepository : public Domain::IStudentRepository
{
public:
    explicit SqliteStudentRepository(const QString &connectionName);

    QVector<Domain::Student> findAll() const override;
    std::optional<Domain::Student> findByAlbumNumber(const Domain::AlbumNumber &a) const override;
    void save(const Domain::Student &student) override;
    void remove(const Domain::AlbumNumber &albumNumber) override;
    void saveAll(const QVector<Domain::Student> &students) override;

private:
    QString m_conn;
};

}

#endif

