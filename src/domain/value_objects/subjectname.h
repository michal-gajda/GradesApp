#ifndef DOMAIN_VALUE_OBJECTS_SUBJECTNAME_H
#define DOMAIN_VALUE_OBJECTS_SUBJECTNAME_H

#include <QString>
#include <stdexcept>

namespace Domain {

class SubjectName
{
public:
    explicit SubjectName(const QString &value)
    {
        const QString trimmed = value.trimmed();

        if (trimmed.isEmpty()) {
            throw std::invalid_argument("Subject name cannot be empty.");
        }

        m_value = trimmed;
    }

    const QString &value() const { return m_value; }

    bool operator==(const SubjectName &other) const { return m_value == other.m_value; }
    bool operator!=(const SubjectName &other) const { return !(*this == other); }

private:
    QString m_value;
};

} // namespace Domain

#endif // DOMAIN_VALUE_OBJECTS_SUBJECTNAME_H

