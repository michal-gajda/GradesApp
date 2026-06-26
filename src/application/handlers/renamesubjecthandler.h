#ifndef APPLICATION_HANDLERS_RENAMESUBJECTHANDLER_H
#define APPLICATION_HANDLERS_RENAMESUBJECTHANDLER_H

#include "application/commands/renamesubjectcommand.h"
#include "domain/repositories/isubjectrepository.h"
#include "domain/repositories/istudentrepository.h"

namespace Application {

class RenameSubjectHandler {
public:
    RenameSubjectHandler(Domain::ISubjectRepository &pr, Domain::IStudentRepository &sr)
            : m_pr(pr), m_sr(sr) {}

    void handle(const RenameSubjectCommand &cmd);

private:
    Domain::ISubjectRepository &m_pr;
    Domain::IStudentRepository &m_sr;
};

} // namespace Application

#endif // APPLICATION_HANDLERS_RENAMESUBJECTHANDLER_H

