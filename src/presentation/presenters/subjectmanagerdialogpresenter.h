#ifndef PRESENTATION_PRESENTERS_SUBJECTMANAGERDIALOGPRESENTER_H
#define PRESENTATION_PRESENTERS_SUBJECTMANAGERDIALOGPRESENTER_H

#include "application/handlers/addsubjecthandler.h"
#include "application/handlers/getallsubjectshandler.h"
#include "application/handlers/removesubjecthandler.h"
#include "application/handlers/renamesubjecthandler.h"
#include <QString>
#include <QStringList>

namespace Presentation {

class ISubjectManagerDialogView
{
public:
    virtual ~ISubjectManagerDialogView() = default;

    virtual int currentRow() const = 0;
    virtual QString currentName() const = 0;
    virtual QString askText(const QString &title,
                            const QString &label,
                            const QString &defaultValue,
                            bool &ok) = 0;
    virtual bool confirm(const QString &title, const QString &message) = 0;
    virtual void showInfo(const QString &title, const QString &message) = 0;
    virtual void showError(const QString &title, const QString &message) = 0;
    virtual void setSubjects(const QStringList &names) = 0;
    virtual void notifySubjectsChanged() = 0;
};

class SubjectManagerDialogPresenter
{
public:
    SubjectManagerDialogPresenter(ISubjectManagerDialogView &view,
                                  Application::AddSubjectHandler &addHandler,
                                  Application::RemoveSubjectHandler &removeHandler,
                                  Application::RenameSubjectHandler &renameHandler,
                                  Application::GetAllSubjectsHandler &getAllHandler);

    void initialize();
    void onAddClicked();
    void onRemoveClicked();
    void onRenameClicked();

private:
    void refreshList();

    ISubjectManagerDialogView &m_view;
    Application::AddSubjectHandler &m_addHandler;
    Application::RemoveSubjectHandler &m_removeHandler;
    Application::RenameSubjectHandler &m_renameHandler;
    Application::GetAllSubjectsHandler &m_getAllHandler;
};

} // namespace Presentation

#endif // PRESENTATION_PRESENTERS_SUBJECTMANAGERDIALOGPRESENTER_H