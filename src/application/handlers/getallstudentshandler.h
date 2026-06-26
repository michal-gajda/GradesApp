#ifndef APPLICATION_HANDLERS_GETALLSTUDENTSHANDLER_H
#define APPLICATION_HANDLERS_GETALLSTUDENTSHANDLER_H

#include "application/queries/getallstudentsquery.h"
#include "domain/repositories/istudentrepository.h"
#include <QVector>

namespace Application {

class GetAllStudentsHandler {
public:
    explicit GetAllStudentsHandler(Domain::IStudentRepository &sr)
            : m_sr(sr) {}

    QVector<StudentDto> handle(const GetAllStudentsQuery &) const;

private:
    Domain::IStudentRepository &m_sr;
};

}

#endif

