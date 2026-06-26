#ifndef APPLICATION_COMMANDS_ADDSTUDENTCOMMAND__H
#define APPLICATION_COMMANDS_ADDSTUDENTCOMMAND__H

#include <QString>

namespace Application {

struct AddStudentCommand
{
    QString firstName;
    QString lastName;
    QString albumNumber;
};

}

#endif
