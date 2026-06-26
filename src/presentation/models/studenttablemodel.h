#ifndef PRESENTATION_MODELS_STUDENTTABLEMODEL_H
#define PRESENTATION_MODELS_STUDENTTABLEMODEL_H

#include "application/queries/getallstudentsquery.h"
#include <QAbstractTableModel>

namespace Presentation {

class StudentTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column { COL_ALBUM=0, COL_LASTNAME=1, COL_FIRSTNAME=2, COL_SUBJECTS=3, COL_COUNT=4 };

    explicit StudentTableModel(QObject *parent = nullptr);

    void reset(const QVector<Application::StudentDto> &students);

    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    const Application::StudentDto &studentAt(int row) const;
    double passRateAt(int row) const;

private:
    QVector<Application::StudentDto> m_students;

    QString subjectsCsv(const Application::StudentDto &s) const;
};

}

#endif

