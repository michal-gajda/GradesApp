#ifndef DOMAIN_VALUE_OBJECTS_ALBUMNUMBER_H
#define DOMAIN_VALUE_OBJECTS_ALBUMNUMBER_H

#include <QString>
#include <stdexcept>

namespace Domain {

class AlbumNumber
{
public:
    explicit AlbumNumber(const QString &value)
    {
        const QString trimmed = value.trimmed();

        if (trimmed.isEmpty()) {
            throw std::invalid_argument("Album number cannot be empty.");
        }

        m_value = trimmed;
    }

    const QString &value() const { return m_value; }

    bool operator==(const AlbumNumber &other) const { return m_value == other.m_value; }
    bool operator!=(const AlbumNumber &other) const { return !(*this == other); }

private:
    QString m_value;
};

} // namespace Domain

#endif // DOMAIN_VALUE_OBJECTS_ALBUMNUMBER_H
