#ifndef PRESENTATION_DIALOGS_STUDENTEDITDIALOG_H
#define PRESENTATION_DIALOGS_STUDENTEDITDIALOG_H

#include "application/queries/getallstudentsquery.h"
#include "application/handlers/getallsubjectshandler.h"
#include "presentation/presenters/studenteditdialogpresenter.h"
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

class StudentEditDialog : public QDialog, public IStudentEditDialogView
{
    Q_OBJECT

public:
    StudentEditDialog(const Application::StudentDto &student,
                      Application::GetAllSubjectsHandler &getAllSubjectsHandler,
                      QWidget *parent = nullptr);
    ~StudentEditDialog();

    StudentEditResult result() const;

    void setAlbum(const QString &value) override;
    void setFirstName(const QString &value) override;
    void setLastName(const QString &value) override;
    QString firstName() const override;
    QString lastName() const override;

    void clearSubjectsList() override;
    void addSubjectToList(const QString &name, bool passed) override;
    int selectedSubjectRow() const override;
    QString selectedSubjectName() const override;
    int subjectsCount() const override;
    QString subjectNameAt(int index) const override;
    bool subjectPassedAt(int index) const override;

    void showInfo(const QString &title, const QString &message) override;
    void showWarning(const QString &title, const QString &message) override;
    void showError(const QString &title, const QString &message) override;
    bool confirm(const QString &title, const QString &message) override;
    QString askItem(const QString &title,
                    const QString &label,
                    const QStringList &items,
                    bool &ok) override;
    void acceptDialog() override;

private slots:
    void onAddSubject();
    void onRemoveSubject();
    void onOk();

private:
    Ui::StudentEditDialog *m_ui;
    StudentEditDialogPresenter m_presenter;
};

} // namespace Presentation

#endif // PRESENTATION_DIALOGS_STUDENTEDITDIALOG_H

