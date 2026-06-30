#ifndef APPLICATION_HANDLERS_REMOVESTUDENTHANDLER_H
#define APPLICATION_HANDLERS_REMOVESTUDENTHANDLER_H

#include "application/commands/removestudentcommand.h"
#include "domain/repositories/istudentrepository.h"

namespace Application {

class RemoveStudentHandler {
public:
    explicit RemoveStudentHandler(Domain::IStudentRepository &sr)
        : m_sr(sr)
    {}

    void handle(const RemoveStudentCommand &cmd);

private:
    Domain::IStudentRepository &m_sr;
};

}

#endif

