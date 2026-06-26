#include "application/handlers/editstudenthandler.h"
#include <stdexcept>
namespace Application {
void EditStudentHandler::handle(const EditStudentCommand &cmd) {
    auto ms = m_sr.findByAlbumNumber(Domain::AlbumNumber(cmd.albumNumber));

    if (!ms) {
        throw std::runtime_error("Student not found.");
    }

    Domain::Student s = *ms;
    s.rename(cmd.newFirstName, cmd.newLastName);

    QVector<Domain::Student::SubjectGrade> subjects;
    subjects.reserve(cmd.subjects.size());
    for (const auto &subject : cmd.subjects) {
        subjects.append({subject.name, subject.passed});
    }
    s.setSubjects(subjects);

    m_sr.save(s);
}
}
