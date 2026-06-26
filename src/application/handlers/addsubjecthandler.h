#ifndef APPLICATION_HANDLERS_ADDSUBJECTHANDLER_H
#define APPLICATION_HANDLERS_ADDSUBJECTHANDLER_H

#include "application/commands/addsubjectcommand.h"
#include "domain/repositories/isubjectrepository.h"

namespace Application {

class AddSubjectHandler {
public:
    explicit AddSubjectHandler(Domain::ISubjectRepository &pr)
            : m_pr(pr) {}

    void handle(const AddSubjectCommand &cmd);

private:
    Domain::ISubjectRepository &m_pr;
};

} // namespace Application

#endif // APPLICATION_HANDLERS_ADDSUBJECTHANDLER_H

