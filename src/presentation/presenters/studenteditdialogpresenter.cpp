#include "presentation/presenters/studenteditdialogpresenter.h"

namespace Presentation {

StudentEditDialogPresenter::StudentEditDialogPresenter(IStudentEditDialogView &view,
                                                       const Application::StudentDto &student,
                                                       Application::GetAllSubjectsHandler &getAllSubjectsHandler)
    : m_view(view)
    , m_getAllSubjects(getAllSubjectsHandler)
    , m_album(student.albumNumber)
    , m_firstName(student.firstName)
    , m_lastName(student.lastName)
    , m_subjects(student.subjects)
{
}

void StudentEditDialogPresenter::initialize()
{
    m_view.setAlbum(m_album);
    m_view.setFirstName(m_firstName);
    m_view.setLastName(m_lastName);
    rebuildList();
}

void StudentEditDialogPresenter::onAddSubjectClicked()
{
    const auto catalog = m_getAllSubjects.handle({});
    if (catalog.isEmpty()) {
        m_view.showInfo("No subjects", "Subject catalog is empty. Add subjects in Manage subjects first.");
        return;
    }

    QStringList available;
    for (const auto &catalogSubject : catalog) {
        bool alreadyAssigned = false;
        for (const auto &assignedSubject : m_subjects) {
            if (assignedSubject.name.compare(catalogSubject.name, Qt::CaseInsensitive) == 0) {
                alreadyAssigned = true;
                break;
            }
        }
        if (!alreadyAssigned) {
            available.append(catalogSubject.name);
        }
    }

    if (available.isEmpty()) {
        m_view.showInfo("No subjects", "All catalog subjects are already assigned to this student.");
        return;
    }

    bool ok = false;
    QString selected = m_view.askItem("Assign subject", "Subject:", available, ok);
    if (!ok || selected.trimmed().isEmpty()) {
        return;
    }

    syncSubjectsFromList();
    m_subjects.append({selected.trimmed(), false});
    rebuildList();
}

void StudentEditDialogPresenter::onRemoveSubjectClicked()
{
    const int row = m_view.selectedSubjectRow();
    if (row < 0) {
        m_view.showInfo("Remove subject", "Select a subject from the list.");
        return;
    }

    const QString name = m_view.selectedSubjectName().trimmed();
    if (!m_view.confirm("Remove subject", QString("Remove \"%1\" from this student?").arg(name))) {
        return;
    }

    syncSubjectsFromList();
    m_subjects.removeAt(row);
    rebuildList();
}

void StudentEditDialogPresenter::onOkClicked()
{
    if (m_view.firstName().trimmed().isEmpty() || m_view.lastName().trimmed().isEmpty()) {
        m_view.showWarning("Error", "First and last name are required.");
        return;
    }

    syncSubjectsFromList();
    m_view.acceptDialog();
}

void StudentEditDialogPresenter::rebuildList()
{
    m_view.clearSubjectsList();
    for (const auto &subject : m_subjects) {
        m_view.addSubjectToList(subject.name.trimmed(), subject.passed);
    }
}

void StudentEditDialogPresenter::syncSubjectsFromList()
{
    m_subjects.resize(m_view.subjectsCount());
    for (int i = 0; i < m_view.subjectsCount(); ++i) {
        m_subjects[i].name = m_view.subjectNameAt(i).trimmed();
        m_subjects[i].passed = m_view.subjectPassedAt(i);
    }
}

} // namespace Presentation