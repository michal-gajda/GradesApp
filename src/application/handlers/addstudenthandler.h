#ifndef APPLICATION_HANDLERS_ADDSTUDENTHANDLER_H
#define APPLICATION_HANDLERS_ADDSTUDENTHANDLER_H

#include "application/commands/addstudentcommand.h"
#include "domain/repositories/istudentrepository.h"

namespace Application {

class AddStudentHandler {
public:
    explicit AddStudentHandler(Domain::IStudentRepository &sr)
            : m_sr(sr) {}

    void handle(const AddStudentCommand &cmd);

private:
    Domain::IStudentRepository &m_sr;
};

} // namespace Application

#endif // APPLICATION_HANDLERS_ADDSTUDENTHANDLER_H

