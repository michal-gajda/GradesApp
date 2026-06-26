#ifndef APPLICATION_QUERIES_GETALLSTUDENTSQUERY__H
#define APPLICATION_QUERIES_GETALLSTUDENTSQUERY__H

#include <QString>
#include <QVector>

namespace Application {

struct SubjectGradeDto
{
    QString name;
    bool passed;
};

struct StudentDto
{
    QString firstName;
    QString lastName;
    QString albumNumber;
    QVector<SubjectGradeDto> subjects;
};

struct GetAllStudentsQuery {};

}

#endif
