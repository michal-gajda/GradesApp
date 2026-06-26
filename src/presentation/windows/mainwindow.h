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
#include "presentation/presenters/mainwindowpresenter.h"
#include <QMainWindow>
#include <QLabel>

namespace Ui { class MainWindow; }

namespace Presentation {

class MainWindow : public QMainWindow, public IMainWindowView
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

    StudentTableModel *m_model;
    QLabel *m_statusLabel;
    MainWindowPresenter m_presenter;

    StudentTableModel &tableModel() override;
    QWidget *asWidget() override;
    int selectedRow() const override;
    int sortSection() const override;
    Qt::SortOrder sortOrder() const override;
    void setStatusText(const QString &text) override;
    void showError(const QString &message) override;
    bool openStudentDialog(StudentFormData &data) override;
    bool openStudentEditDialog(const Application::StudentDto &student,
                               Application::GetAllSubjectsHandler &getAllSubjects,
                               StudentEditResult &result) override;
    void openSubjectManagerDialog(Application::AddSubjectHandler &addSubject,
                                  Application::RemoveSubjectHandler &removeSubject,
                                  Application::RenameSubjectHandler &renameSubject,
                                  Application::GetAllSubjectsHandler &getAllSubjects,
                                  const std::function<void()> &onSubjectsChanged) override;

    void setupTable();
    void connectSignals();
};

} // namespace Presentation

#endif // PRESENTATION_WINDOWS_MAINWINDOW_H

