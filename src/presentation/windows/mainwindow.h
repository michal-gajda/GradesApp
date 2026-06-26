#ifndef PRESENTATION_WINDOWS_MAINWINDOW_H
#define PRESENTATION_WINDOWS_MAINWINDOW_H

#include "application/handlers/addstudenthandler.h"
#include "application/handlers/removestudenthandler.h"
#include "application/handlers/editstudenthandler.h"
#include "application/handlers/addsubjecthandler.h"
#include "application/handlers/removesubjecthandler.h"
#include "application/handlers/renamesubjecthandler.h"
#include "application/handlers/getallstudentshandler.h"
#include "application/handlers/getallsubjectshandler.h"
#include "presentation/models/studenttablemodel.h"
#include <QMainWindow>
#include <QLabel>

namespace Ui { class MainWindow; }

namespace Presentation {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Application::AddStudentHandler &addStudent,
                    Application::RemoveStudentHandler &removeStudent,
                    Application::EditStudentHandler &editStudent,
                    Application::AddSubjectHandler &addSubject,
                    Application::RemoveSubjectHandler &removeSubject,
                    Application::RenameSubjectHandler &renameSubject,
                    Application::GetAllStudentsHandler &getAllStudents,
                    Application::GetAllSubjectsHandler &getAllSubjects,
                    QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStudent();
    void onManageSubjects();
    void onRowDoubleClicked(const QModelIndex &index);
    void onSelectionChanged();

private:
    Ui::MainWindow *m_ui;

    Application::AddStudentHandler &m_addStudent;
    Application::RemoveStudentHandler &m_removeStudent;
    Application::EditStudentHandler &m_editStudent;
    Application::AddSubjectHandler &m_addSubject;
    Application::RemoveSubjectHandler &m_removeSubject;
    Application::RenameSubjectHandler &m_renameSubject;
    Application::GetAllStudentsHandler &m_getAllStudents;
    Application::GetAllSubjectsHandler &m_getAllSubjects;

    StudentTableModel *m_model;
    QLabel *m_statusLabel;

    void setupTable();
    void connectSignals();
    void refreshView();
    void openEditDialog(int row);
    int selectedRow() const;
};

} // namespace Presentation

#endif // PRESENTATION_WINDOWS_MAINWINDOW_H

