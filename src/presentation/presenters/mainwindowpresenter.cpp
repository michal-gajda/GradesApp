#include "presentation/presenters/mainwindowpresenter.h"
#include "presentation/models/studenttablemodel.h"
#include <algorithm>

namespace Presentation {

MainWindowPresenter::MainWindowPresenter(IMainWindowView &view,
                                         Application::AddStudentHandler &addStudent,
                                         Application::RemoveStudentHandler &removeStudent,
                                         Application::EditStudentHandler &editStudent,
                                         Application::AddSubjectHandler &addSubject,
                                         Application::RemoveSubjectHandler &removeSubject,
                                         Application::RenameSubjectHandler &renameSubject,
                                         Application::GetAllStudentsHandler &getAllStudents,
                                         Application::GetAllSubjectsHandler &getAllSubjects)
    : m_view(view)
    , m_addStudent(addStudent)
    , m_removeStudent(removeStudent)
    , m_editStudent(editStudent)
    , m_addSubject(addSubject)
    , m_removeSubject(removeSubject)
    , m_renameSubject(renameSubject)
    , m_getAllStudents(getAllStudents)
    , m_getAllSubjects(getAllSubjects)
{
}

void MainWindowPresenter::initialize()
{
    refreshView();
}

void MainWindowPresenter::onAddStudentClicked()
{
    StudentFormData formData;
    if (!m_view.openStudentDialog(formData)) {
        return;
    }

    try {
        m_addStudent.handle({formData.firstName, formData.lastName, formData.albumNumber});
        refreshView();
    } catch (const std::exception &e) {
        m_view.showError(QString::fromStdString(e.what()));
    }
}

void MainWindowPresenter::onManageSubjectsClicked()
{
    m_view.openSubjectManagerDialog(m_addSubject,
                                    m_removeSubject,
                                    m_renameSubject,
                                    m_getAllSubjects,
                                    [this]() { refreshView(); });
}

void MainWindowPresenter::onRowDoubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        openEditDialog(index.row());
    }
}

void MainWindowPresenter::onSelectionChanged()
{
    const int row = m_view.selectedRow();
    auto &model = m_view.tableModel();

    if (row < 0) {
        m_view.setStatusText(QString("Students: %1").arg(model.rowCount()));
        return;
    }

    const auto &student = model.studentAt(row);
    const double rate = model.passRateAt(row);
    if (rate < 0.0) {
        m_view.setStatusText(QString("%1 %2 - no subjects").arg(student.firstName, student.lastName));
        return;
    }

    const int passed = static_cast<int>(std::count_if(
        student.subjects.begin(),
        student.subjects.end(),
        [](const Application::SubjectGradeDto &subject) { return subject.passed; }));
    const int pct = static_cast<int>(rate * 100.0);

    m_view.setStatusText(
        QString("%1 %2 | Passed: %3 / %4 (%5%)")
            .arg(student.firstName,
                 student.lastName,
                 QString::number(passed),
                 QString::number(student.subjects.size()),
                 QString::number(pct)));
}

void MainWindowPresenter::refreshView()
{
    auto students = m_getAllStudents.handle({});
    auto &model = m_view.tableModel();
    model.reset(students);
    model.sort(m_view.sortSection(), m_view.sortOrder());
    m_view.setStatusText(QString("Students: %1").arg(students.size()));
}

void MainWindowPresenter::openEditDialog(int row)
{
    auto &model = m_view.tableModel();
    const auto &dto = model.studentAt(row);

    StudentEditResult result;
    if (!m_view.openStudentEditDialog(dto, m_getAllSubjects, result)) {
        return;
    }

    try {
        m_editStudent.handle({dto.albumNumber, result.firstName, result.lastName, result.subjects});
        refreshView();
    } catch (const std::exception &e) {
        m_view.showError(QString::fromStdString(e.what()));
    }
}

}