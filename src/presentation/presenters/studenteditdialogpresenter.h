#ifndef PRESENTATION_PRESENTERS_STUDENTEDITDIALOGPRESENTER_H
#define PRESENTATION_PRESENTERS_STUDENTEDITDIALOGPRESENTER_H

#include "application/handlers/getallsubjectshandler.h"
#include "application/queries/getallstudentsquery.h"
#include <QString>
#include <QStringList>
#include <QVector>

namespace Presentation {

class IStudentEditDialogView
{
public:
    virtual ~IStudentEditDialogView() = default;

    virtual void setAlbum(const QString &value) = 0;
    virtual void setFirstName(const QString &value) = 0;
    virtual void setLastName(const QString &value) = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;

    virtual void clearSubjectsList() = 0;
    virtual void addSubjectToList(const QString &name, bool passed) = 0;
    virtual int selectedSubjectRow() const = 0;
    virtual QString selectedSubjectName() const = 0;
    virtual int subjectsCount() const = 0;
    virtual QString subjectNameAt(int index) const = 0;
    virtual bool subjectPassedAt(int index) const = 0;

    virtual void showInfo(const QString &title, const QString &message) = 0;
    virtual void showWarning(const QString &title, const QString &message) = 0;
    virtual void showError(const QString &title, const QString &message) = 0;
    virtual bool confirm(const QString &title, const QString &message) = 0;
    virtual QString askItem(const QString &title,
                            const QString &label,
                            const QStringList &items,
                            bool &ok) = 0;
    virtual void acceptDialog() = 0;
};

class StudentEditDialogPresenter
{
public:
    StudentEditDialogPresenter(IStudentEditDialogView &view,
                               const Application::StudentDto &student,
                               Application::GetAllSubjectsHandler &getAllSubjectsHandler);

    void initialize();
    void onAddSubjectClicked();
    void onRemoveSubjectClicked();
    void onOkClicked();

    QVector<Application::SubjectGradeDto> subjects() const { return m_subjects; }

private:
    void rebuildList();
    void syncSubjectsFromList();

    IStudentEditDialogView &m_view;
    Application::GetAllSubjectsHandler &m_getAllSubjects;
    QString m_album;
    QString m_firstName;
    QString m_lastName;
    QVector<Application::SubjectGradeDto> m_subjects;
};

}

#endif