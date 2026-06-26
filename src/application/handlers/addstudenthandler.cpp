#include "application/handlers/addstudenthandler.h"
namespace Application {
void AddStudentHandler::handle(const AddStudentCommand &cmd) {
    Domain::Student s(cmd.firstName, cmd.lastName, Domain::AlbumNumber(cmd.albumNumber));
    m_sr.save(s);
}
}
