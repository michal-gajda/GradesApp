#ifndef APPLICATION_HANDLERS_UPDATEGRADEHANDLER_H
#define APPLICATION_HANDLERS_UPDATEGRADEHANDLER_H

#include "application/commands/updategradecommand.h"
#include "domain/repositories/istudentrepository.h"

namespace Application {

class UpdateGradeHandler {
public:
    explicit UpdateGradeHandler(Domain::IStudentRepository &sr)
            : m_sr(sr) {}

    void handle(const UpdateGradeCommand &cmd);

private:
    Domain::IStudentRepository &m_sr;
};

}

#endif

