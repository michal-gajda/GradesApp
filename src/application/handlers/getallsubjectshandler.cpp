#include "application/handlers/getallsubjectshandler.h"

namespace Application {
QVector<SubjectDto> GetAllSubjectsHandler::handle(const GetAllSubjectsQuery &) const
{
    QVector<SubjectDto> result;

    for (const auto &s : m_pr.findAll()) {
        result.append({s.name().value()});
    }

    return result;
}
}
