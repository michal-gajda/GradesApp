#ifndef APPLICATION_HANDLERS_REMOVESUBJECTHANDLER_H
#define APPLICATION_HANDLERS_REMOVESUBJECTHANDLER_H

#include "application/commands/removesubjectcommand.h"
#include "domain/repositories/isubjectrepository.h"
#include "domain/repositories/istudentrepository.h"

namespace Application {

class RemoveSubjectHandler {
public:
    RemoveSubjectHandler(Domain::ISubjectRepository &pr, Domain::IStudentRepository &sr)
            : m_pr(pr), m_sr(sr) {}

    void handle(const RemoveSubjectCommand &cmd);

private:
    Domain::ISubjectRepository &m_pr;
    Domain::IStudentRepository &m_sr;
};

} // namespace Application

#endif // APPLICATION_HANDLERS_REMOVESUBJECTHANDLER_H

