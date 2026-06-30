#include "application/handlers/addsubjecthandler.h"
#include "domain/entities/subject.h"
#include <stdexcept>

namespace Application {
void AddSubjectHandler::handle(const AddSubjectCommand &cmd)
{
    auto subjects = m_pr.findAll();

    for (const auto &subject : subjects) {
        if (subject.name().value().compare(cmd.name.trimmed(), Qt::CaseInsensitive) == 0) {
            throw std::runtime_error("Subject already exists.");
        }
    }

    subjects.append(Domain::Subject(Domain::SubjectName(cmd.name)));
    m_pr.saveAll(subjects);
}
}
