#include "application/handlers/updategradehandler.h"
#include <stdexcept>

namespace Application {
void UpdateGradeHandler::handle(const UpdateGradeCommand &cmd)
{
    auto ms = m_sr.findByAlbumNumber(Domain::AlbumNumber(cmd.albumNumber));

    if (!ms) {
        throw std::runtime_error("Student not found.");
    }

    Domain::Student s = *ms;
    s.setSubjectPassed(cmd.subjectIndex, cmd.passed);
    m_sr.save(s);
}
}
