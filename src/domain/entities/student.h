#ifndef DOMAIN_ENTITIES_STUDENT_H
#define DOMAIN_ENTITIES_STUDENT_H

#include "domain/value_objects/albumnumber.h"
#include <QString>
#include <QVector>
#include <stdexcept>

namespace Domain {

class Student
{
public:
    struct SubjectGrade
    {
        QString name;
        bool passed;
    };

    Student(const QString &firstName,
            const QString &lastName,
            const AlbumNumber &albumNumber)
        : m_firstName(firstName.trimmed())
        , m_lastName(lastName.trimmed())
        , m_albumNumber(albumNumber)
    {
        if (m_firstName.isEmpty()) {
            throw std::invalid_argument("First name cannot be empty.");
        }

        if (m_lastName.isEmpty()) {
            throw std::invalid_argument("Last name cannot be empty.");
        }
    }

    const QString &firstName() const { return m_firstName; }
    const QString &lastName() const { return m_lastName; }
    const AlbumNumber &albumNumber() const { return m_albumNumber; }
    const QVector<SubjectGrade> &subjects() const { return m_subjects; }

    void setSubjects(const QVector<SubjectGrade> &subjects)
    {
        m_subjects.clear();
        m_subjects.reserve(subjects.size());

        for (const auto &subject : subjects) {
            const QString trimmed = subject.name.trimmed();

            if (trimmed.isEmpty()) {
                throw std::invalid_argument("Subject name cannot be empty.");
            }

            m_subjects.append({trimmed, subject.passed});
        }
    }

    void addSubject(const QString &name, bool passed = false)
    {
        const QString trimmed = name.trimmed();

        if (trimmed.isEmpty()) {
            throw std::invalid_argument("Subject name cannot be empty.");
        }

        m_subjects.append({trimmed, passed});
    }

    void removeSubjectAt(int i)
    {
        if (i < 0 || i >= m_subjects.size()) {
            throw std::out_of_range("Subject index out of range.");
        }

        m_subjects.removeAt(i);
    }

    void setSubjectPassed(int i, bool passed)
    {
        if (i < 0 || i >= m_subjects.size()) {
            throw std::out_of_range("Subject index out of range.");
        }

        m_subjects[i].passed = passed;
    }

    void rename(const QString &firstName, const QString &lastName)
    {
        const QString f = firstName.trimmed();
        const QString l = lastName.trimmed();

        if (f.isEmpty()) {
            throw std::invalid_argument("First name cannot be empty.");
        }

        if (l.isEmpty()) {
            throw std::invalid_argument("Last name cannot be empty.");
        }

        m_firstName = f;
        m_lastName = l;
    }

private:
    QString m_firstName;
    QString m_lastName;
    AlbumNumber m_albumNumber;
    QVector<SubjectGrade> m_subjects;
};

} // namespace Domain

#endif // DOMAIN_ENTITIES_STUDENT_H
