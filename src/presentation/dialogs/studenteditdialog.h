#ifndef PRESENTATION_DIALOGS_STUDENTEDITDIALOG_H
#define PRESENTATION_DIALOGS_STUDENTEDITDIALOG_H

#include "application/queries/getallstudentsquery.h"
#include "application/handlers/getallsubjectshandler.h"
#include <QDialog>
#include <QVector>

namespace Ui { class StudentEditDialog; }

namespace Presentation {

struct StudentEditResult
{
    QString firstName;
    QString lastName;
    QVector<Application::SubjectGradeDto> subjects;
};

class StudentEditDialog : public QDialog
{
    Q_OBJECT

public:
    StudentEditDialog(const Application::StudentDto &student,
                            Application::GetAllSubjectsHandler &getAllSubjectsHandler,
                            QWidget *parent = nullptr);
    ~StudentEditDialog();

    StudentEditResult result() const;

private slots:
    void onAddSubject();
    void onRemoveSubject();
    void onOk();

private:
    Ui::StudentEditDialog *m_ui;
    Application::GetAllSubjectsHandler &m_getAllSubjects;
    QVector<Application::SubjectGradeDto> m_subjects;

    void rebuildList();
    void syncSubjectsFromList();
};

} // namespace Presentation

#endif // PRESENTATION_DIALOGS_STUDENTEDITDIALOG_H

