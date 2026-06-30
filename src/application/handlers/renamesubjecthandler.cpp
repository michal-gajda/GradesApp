#include "application/handlers/renamesubjecthandler.h"
#include <stdexcept>

namespace Application {
void RenameSubjectHandler::handle(const RenameSubjectCommand &cmd)
{
    auto subjects = m_pr.findAll();

    if (cmd.subjectIndex < 0 || cmd.subjectIndex >= subjects.size()) {
        throw std::out_of_range("Subject index out of range.");
    }

    const QString oldName = subjects[cmd.subjectIndex].name().value();
    const QString newName = cmd.newName.trimmed();

    for (int i = 0; i < subjects.size(); ++i) {
        if (i == cmd.subjectIndex) {
            continue;
        }
        if (subjects[i].name().value().compare(newName, Qt::CaseInsensitive) == 0) {
            throw std::runtime_error("Subject already exists.");
        }
    }

    subjects[cmd.subjectIndex].rename(Domain::SubjectName(cmd.newName));
    m_pr.saveAll(subjects);

    auto students = m_sr.findAll();
    for (auto &student : students) {
        QVector<Domain::Student::SubjectGrade> renamed;
        renamed.reserve(student.subjects().size());
        for (const auto &subject : student.subjects()) {
            if (subject.name == oldName) {
                renamed.append({newName, subject.passed});
            } else {
                renamed.append(subject);
            }
        }
        student.setSubjects(renamed);
    }
    m_sr.saveAll(students);
}
}
