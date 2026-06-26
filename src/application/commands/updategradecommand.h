#ifndef APPLICATION_COMMANDS_UPDATEGRADECOMMAND__H
#define APPLICATION_COMMANDS_UPDATEGRADECOMMAND__H

#include <QString>

namespace Application {

struct UpdateGradeCommand
{
    QString albumNumber;
    int subjectIndex;
    bool passed;
};

}

#endif
