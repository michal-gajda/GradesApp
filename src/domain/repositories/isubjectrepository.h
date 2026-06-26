#ifndef DOMAIN_REPOSITORIES_ISUBJECTREPOSITORY__H
#define DOMAIN_REPOSITORIES_ISUBJECTREPOSITORY__H

#include "domain/entities/subject.h"
#include <QVector>

namespace Domain {

class ISubjectRepository
{
public:
    virtual ~ISubjectRepository() = default;
    virtual QVector<Subject> findAll() const = 0;
    virtual void saveAll(const QVector<Subject> &subjects) = 0;
};

} // namespace Domain

#endif // DOMAIN_REPOSITORIES_ISUBJECTREPOSITORY__H
