#include "presentation/models/studenttablemodel.h"
#include <algorithm>

namespace Presentation {

StudentTableModel::StudentTableModel(QObject *parent) : QAbstractTableModel(parent) {}

void StudentTableModel::reset(const QVector<Application::StudentDto> &students)
{
    beginResetModel();
    m_students = students;
    endResetModel();
}

int StudentTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_students.size();
}

int StudentTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : COL_COUNT;
}

QVariant StudentTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_students.size()) {
        return {};
    }

    const auto &s = m_students[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column())
        {
        case COL_ALBUM:
            return s.albumNumber;
        case COL_LASTNAME:
            return s.lastName;
        case COL_FIRSTNAME:
            return s.firstName;
        case COL_SUBJECTS:
            return subjectsCsv(s);
        default:
            break;
        }
    }

    if (role == Qt::ToolTipRole && index.column() == COL_SUBJECTS) {
        return subjectsCsv(s);
    }

    return {};
}

QVariant StudentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    switch (section){
    case COL_ALBUM:
        return "Album no.";
    case COL_LASTNAME:
        return "Last name";
    case COL_FIRSTNAME:
        return "First name";
    case COL_SUBJECTS:
        return "Passed subjects";
    default:
        return {};
    }
}

Qt::ItemFlags StudentTableModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : Qt::NoItemFlags;
}

void StudentTableModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();
    std::sort(m_students.begin(), m_students.end(),
        [this, column, order](const Application::StudentDto &a, const Application::StudentDto &b)
        {
            QString va, vb;
            switch (column) {
            case COL_ALBUM:
                va = a.albumNumber;
                vb = b.albumNumber;
                break;
            case COL_LASTNAME:
                va = a.lastName;
                vb = b.lastName;
                break;
            case COL_FIRSTNAME:
                va = a.firstName;
                vb = b.firstName;
                break;
            case COL_SUBJECTS:
                va = subjectsCsv(a);
                vb = subjectsCsv(b);
                break;
            default:
                break;
            }

            return order == Qt::AscendingOrder ? va < vb : va > vb;
        });
    endResetModel();
}

const Application::StudentDto &StudentTableModel::studentAt(int row) const
{
    return m_students[row];
}

double StudentTableModel::passRateAt(int row) const
{
    if (row < 0 || row >= m_students.size()) {
        return -1.0;
    }
    const auto &subjects = m_students[row].subjects;

    if (subjects.isEmpty()) {
        return -1.0;
    }

    int passed = std::count_if(subjects.begin(), subjects.end(), [](const Application::SubjectGradeDto &subject) {
        return subject.passed;
    });

    return static_cast<double>(passed) / subjects.size();
}

QString StudentTableModel::subjectsCsv(const Application::StudentDto &s) const
{
    QStringList passed;
    for (const auto &subject : s.subjects) {
        if (subject.passed) {
            passed.append(subject.name);
        }
    }
    return passed.join(", ");
}

}
