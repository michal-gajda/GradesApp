#include "application/handlers/removesubjecthandler.h"
#include <stdexcept>
namespace Application {
void RemoveSubjectHandler::handle(const RemoveSubjectCommand &cmd) {
    auto subjects = m_pr.findAll();

    if (cmd.subjectIndex < 0 || cmd.subjectIndex >= subjects.size()) {
        throw std::out_of_range("Subject index out of range.");
    }

    const QString removedName = subjects[cmd.subjectIndex].name().value();
    subjects.remove(cmd.subjectIndex);
    m_pr.saveAll(subjects);

    auto students = m_sr.findAll();

    for (auto &st : students) {
        QVector<Domain::Student::SubjectGrade> filtered;
        for (const auto &subject : st.subjects()) {
            if (subject.name != removedName) {
                filtered.append(subject);
            }
        }
        st.setSubjects(filtered);
    }

    m_sr.saveAll(students);
}
}
