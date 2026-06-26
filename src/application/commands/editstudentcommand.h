#ifndef APPLICATION_COMMANDS_EDITSTUDENTCOMMAND__H
#define APPLICATION_COMMANDS_EDITSTUDENTCOMMAND__H

#include "application/queries/getallstudentsquery.h"
#include <QString>
#include <QVector>

namespace Application {

struct EditStudentCommand
{
    QString albumNumber;
    QString newFirstName;
    QString newLastName;
    QVector<SubjectGradeDto> subjects;
};

}

#endif
