#ifndef PRESENTATION_PRESENTERS_MAINWINDOWPRESENTER_H
#define PRESENTATION_PRESENTERS_MAINWINDOWPRESENTER_H

#include "application/handlers/addstudenthandler.h"
#include "application/handlers/addsubjecthandler.h"
#include "application/handlers/editstudenthandler.h"
#include "application/handlers/getallstudentshandler.h"
#include "application/handlers/getallsubjectshandler.h"
#include "application/handlers/removestudenthandler.h"
#include "application/handlers/removesubjecthandler.h"
#include "application/handlers/renamesubjecthandler.h"
#include "presentation/dialogs/studentdialog.h"
#include "presentation/dialogs/studenteditdialog.h"
#include <functional>
#include <QModelIndex>
#include <QWidget>

namespace Presentation {

class StudentTableModel;

class IMainWindowView
{
public:
    virtual ~IMainWindowView() = default;

    virtual StudentTableModel &tableModel() = 0;
    virtual QWidget *asWidget() = 0;
    virtual int selectedRow() const = 0;
    virtual int sortSection() const = 0;
    virtual Qt::SortOrder sortOrder() const = 0;
    virtual void setStatusText(const QString &text) = 0;
    virtual void showError(const QString &message) = 0;

    virtual bool openStudentDialog(StudentFormData &data) = 0;
    virtual bool openStudentEditDialog(const Application::StudentDto &student,
                                       Application::GetAllSubjectsHandler &getAllSubjects,
                                       StudentEditResult &result) = 0;
    virtual void openSubjectManagerDialog(Application::AddSubjectHandler &addSubject,
                                          Application::RemoveSubjectHandler &removeSubject,
                                          Application::RenameSubjectHandler &renameSubject,
                                          Application::GetAllSubjectsHandler &getAllSubjects,
                                          const std::function<void()> &onSubjectsChanged) = 0;
};

class MainWindowPresenter
{
public:
    MainWindowPresenter(IMainWindowView &view,
                        Application::AddStudentHandler &addStudent,
                        Application::RemoveStudentHandler &removeStudent,
                        Application::EditStudentHandler &editStudent,
                        Application::AddSubjectHandler &addSubject,
                        Application::RemoveSubjectHandler &removeSubject,
                        Application::RenameSubjectHandler &renameSubject,
                        Application::GetAllStudentsHandler &getAllStudents,
                        Application::GetAllSubjectsHandler &getAllSubjects);

    void initialize();
    void onAddStudentClicked();
    void onManageSubjectsClicked();
    void onRowDoubleClicked(const QModelIndex &index);
    void onSelectionChanged();

private:
    void refreshView();
    void openEditDialog(int row);

    IMainWindowView &m_view;
    Application::AddStudentHandler &m_addStudent;
    Application::RemoveStudentHandler &m_removeStudent;
    Application::EditStudentHandler &m_editStudent;
    Application::AddSubjectHandler &m_addSubject;
    Application::RemoveSubjectHandler &m_removeSubject;
    Application::RenameSubjectHandler &m_renameSubject;
    Application::GetAllStudentsHandler &m_getAllStudents;
    Application::GetAllSubjectsHandler &m_getAllSubjects;
};

}

#endif