#ifndef APPLICATION_HANDLERS_GETALLSUBJECTSHANDLER_H
#define APPLICATION_HANDLERS_GETALLSUBJECTSHANDLER_H

#include "application/queries/getallsubjectsquery.h"
#include "domain/repositories/isubjectrepository.h"
#include <QVector>

namespace Application {

class GetAllSubjectsHandler {
public:
    explicit GetAllSubjectsHandler(Domain::ISubjectRepository &pr)
            : m_pr(pr) {}

    QVector<SubjectDto> handle(const GetAllSubjectsQuery &) const;

private:
    Domain::ISubjectRepository &m_pr;
};

}

#endif

