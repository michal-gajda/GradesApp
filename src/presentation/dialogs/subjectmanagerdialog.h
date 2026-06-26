#ifndef PRESENTATION_DIALOGS_SUBJECTMANAGERDIALOG_H
#define PRESENTATION_DIALOGS_SUBJECTMANAGERDIALOG_H

#include "application/handlers/addsubjecthandler.h"
#include "application/handlers/removesubjecthandler.h"
#include "application/handlers/renamesubjecthandler.h"
#include "application/handlers/getallsubjectshandler.h"
#include "presentation/presenters/subjectmanagerdialogpresenter.h"
#include <QDialog>

namespace Ui { class SubjectManagerDialog; }

namespace Presentation {

class SubjectManagerDialog : public QDialog, public ISubjectManagerDialogView
{
    Q_OBJECT

public:
    SubjectManagerDialog(Application::AddSubjectHandler &addHandler,
                        Application::RemoveSubjectHandler &removeHandler,
                        Application::RenameSubjectHandler &renameHandler,
                        Application::GetAllSubjectsHandler &getAllHandler,
                        QWidget *parent = nullptr);
    ~SubjectManagerDialog();

signals:
    void subjectsChanged();

private slots:
    void onAdd();
    void onRemove();
    void onRename();

private:
    Ui::SubjectManagerDialog *m_ui;
    SubjectManagerDialogPresenter m_presenter;

    int currentRow() const override;
    QString currentName() const override;
    QString askText(const QString &title,
                    const QString &label,
                    const QString &defaultValue,
                    bool &ok) override;
    bool confirm(const QString &title, const QString &message) override;
    void showInfo(const QString &title, const QString &message) override;
    void showError(const QString &title, const QString &message) override;
    void setSubjects(const QStringList &names) override;
    void notifySubjectsChanged() override;
};

}

#endif
