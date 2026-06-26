#ifndef APPLICATION_COMMANDS_RENAMESUBJECTCOMMAND__H
#define APPLICATION_COMMANDS_RENAMESUBJECTCOMMAND__H

#include <QString>

namespace Application {

struct RenameSubjectCommand
{
    int subjectIndex;
    QString newName;
};

} // namespace Application

#endif // APPLICATION_COMMANDS_RENAMESUBJECTCOMMAND__H
