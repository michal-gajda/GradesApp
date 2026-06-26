#include "application/handlers/removestudenthandler.h"
namespace Application {
void RemoveStudentHandler::handle(const RemoveStudentCommand &cmd) {
    m_sr.remove(Domain::AlbumNumber(cmd.albumNumber));
}
}
