#ifndef PRESENTATION_DIALOGS_SUBJECTMANAGERDIALOG_H
#define PRESENTATION_DIALOGS_SUBJECTMANAGERDIALOG_H

#include "application/handlers/addsubjecthandler.h"
#include "application/handlers/removesubjecthandler.h"
#include "application/handlers/renamesubjecthandler.h"
#include "application/handlers/getallsubjectshandler.h"
#include <QDialog>

namespace Ui { class SubjectManagerDialog; }

namespace Presentation {

class SubjectManagerDialog : public QDialog
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
    Application::AddSubjectHandler &m_addHandler;
    Application::RemoveSubjectHandler &m_removeHandler;
    Application::RenameSubjectHandler &m_renameHandler;
    Application::GetAllSubjectsHandler &m_getAllHandler;

    void refreshList();
};

} // namespace Presentation

#endif // PRESENTATION_DIALOGS_SUBJECTMANAGERDIALOG_H
