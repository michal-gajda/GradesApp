#ifndef DOMAIN_ENTITIES_SUBJECT__H
#define DOMAIN_ENTITIES_SUBJECT__H

#include "domain/value_objects/subjectname.h"

namespace Domain {

class Subject
{
public:
    explicit Subject(const SubjectName &name) : m_name(name) {}
    const SubjectName &name() const { return m_name; }
    void rename(const SubjectName &n) { m_name = n; }
private:
    SubjectName m_name;
};

} // namespace Domain

#endif // DOMAIN_ENTITIES_SUBJECT__H
