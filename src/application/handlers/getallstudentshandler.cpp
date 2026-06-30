#include "application/handlers/getallstudentshandler.h"

namespace Application {
QVector<StudentDto> GetAllStudentsHandler::handle(const GetAllStudentsQuery &) const
{
    QVector<StudentDto> result;

    for (const auto &s : m_sr.findAll()) {
        QVector<SubjectGradeDto> subjects;
        subjects.reserve(s.subjects().size());

        for (const auto &subject : s.subjects()) {
            subjects.append({subject.name, subject.passed});
        }

        result.append({s.firstName(), s.lastName(), s.albumNumber().value(), subjects});
    }

    return result;
}
}
