#ifndef APPLICATION_HANDLERS_EDITSTUDENTHANDLER_H
#define APPLICATION_HANDLERS_EDITSTUDENTHANDLER_H

#include "application/commands/editstudentcommand.h"
#include "domain/repositories/istudentrepository.h"

namespace Application {

class EditStudentHandler {
public:
    explicit EditStudentHandler(Domain::IStudentRepository &sr)
            : m_sr(sr) {}

    void handle(const EditStudentCommand &cmd);

private:
    Domain::IStudentRepository &m_sr;
};

} // namespace Application

#endif // APPLICATION_HANDLERS_EDITSTUDENTHANDLER_H

