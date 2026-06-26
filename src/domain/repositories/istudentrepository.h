#ifndef DOMAIN_REPOSITORIES_ISTUDENTREPOSITORY_H
#define DOMAIN_REPOSITORIES_ISTUDENTREPOSITORY_H

#include "domain/entities/student.h"
#include "domain/value_objects/albumnumber.h"
#include <QVector>
#include <optional>

namespace Domain {

class IStudentRepository
{
public:
    virtual ~IStudentRepository() = default;
    virtual QVector<Student> findAll() const = 0;
    virtual std::optional<Student> findByAlbumNumber(const AlbumNumber &albumNumber) const = 0;
    virtual void save(const Student &student) = 0;
    virtual void remove(const AlbumNumber &albumNumber) = 0;
    virtual void saveAll(const QVector<Student> &students) = 0;
};

} // namespace Domain

#endif // DOMAIN_REPOSITORIES_ISTUDENTREPOSITORY_H
