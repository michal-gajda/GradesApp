#include "presentation/presenters/subjectmanagerdialogpresenter.h"

namespace Presentation {

SubjectManagerDialogPresenter::SubjectManagerDialogPresenter(ISubjectManagerDialogView &view,
                                                             Application::AddSubjectHandler &addHandler,
                                                             Application::RemoveSubjectHandler &removeHandler,
                                                             Application::RenameSubjectHandler &renameHandler,
                                                             Application::GetAllSubjectsHandler &getAllHandler)
    : m_view(view)
    , m_addHandler(addHandler)
    , m_removeHandler(removeHandler)
    , m_renameHandler(renameHandler)
    , m_getAllHandler(getAllHandler)
{
}

void SubjectManagerDialogPresenter::initialize()
{
    refreshList();
}

void SubjectManagerDialogPresenter::onAddClicked()
{
    bool ok = false;
    const QString name = m_view.askText("Add subject", "Name:", QString(), ok);
    if (!ok || name.trimmed().isEmpty()) {
        return;
    }

    try {
        m_addHandler.handle({name.trimmed()});
        refreshList();
        m_view.notifySubjectsChanged();
    } catch (const std::exception &e) {
        m_view.showError("Error", QString::fromStdString(e.what()));
    }
}

void SubjectManagerDialogPresenter::onRemoveClicked()
{
    const int row = m_view.currentRow();
    if (row < 0) {
        m_view.showInfo("Remove", "Select a subject.");
        return;
    }

    const QString name = m_view.currentName();
    if (!m_view.confirm("Remove subject",
                        QString("Remove \"%1\"? Grades will be removed for all students.").arg(name))) {
        return;
    }

    try {
        m_removeHandler.handle({row});
        refreshList();
        m_view.notifySubjectsChanged();
    } catch (const std::exception &e) {
        m_view.showError("Error", QString::fromStdString(e.what()));
    }
}

void SubjectManagerDialogPresenter::onRenameClicked()
{
    const int row = m_view.currentRow();
    if (row < 0) {
        m_view.showInfo("Rename", "Select a subject.");
        return;
    }

    bool ok = false;
    const QString newName = m_view.askText("Rename", "New name:", m_view.currentName(), ok);
    if (!ok || newName.trimmed().isEmpty()) {
        return;
    }

    try {
        m_renameHandler.handle({row, newName.trimmed()});
        refreshList();
        m_view.notifySubjectsChanged();
    } catch (const std::exception &e) {
        m_view.showError("Error", QString::fromStdString(e.what()));
    }
}

void SubjectManagerDialogPresenter::refreshList()
{
    QStringList names;
    for (const auto &subject : m_getAllHandler.handle({})) {
        names.append(subject.name);
    }
    m_view.setSubjects(names);
}

} // namespace Presentation