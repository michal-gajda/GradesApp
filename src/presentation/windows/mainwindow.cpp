#include "presentation/windows/mainwindow.h"
#include <QMessageBox>
#include "presentation/dialogs/studentdialog.h"
#include "presentation/dialogs/studenteditdialog.h"
#include "presentation/dialogs/subjectmanagerdialog.h"
#include "ui_MainWindow.h"
#include <algorithm>

namespace Presentation {

MainWindow::MainWindow(Application::AddStudentHandler &addStudent,
                        Application::RemoveStudentHandler &removeStudent,
                        Application::EditStudentHandler &editStudent,
                        Application::AddSubjectHandler &addSubject,
                        Application::RemoveSubjectHandler &removeSubject,
                        Application::RenameSubjectHandler &renameSubject,
                        Application::GetAllStudentsHandler &getAllStudents,
                        Application::GetAllSubjectsHandler &getAllSubjects,
                        QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_addStudent(addStudent)
    , m_removeStudent(removeStudent)
    , m_editStudent(editStudent)
    , m_addSubject(addSubject)
    , m_removeSubject(removeSubject)
    , m_renameSubject(renameSubject)
    , m_getAllStudents(getAllStudents)
    , m_getAllSubjects(getAllSubjects)
{
    m_ui->setupUi(this);

    m_model = new StudentTableModel(this);

    m_statusLabel = new QLabel(this);
    m_ui->statusBar->addWidget(m_statusLabel);

    setupTable();
    connectSignals();
    refreshView();
}

MainWindow::~MainWindow() { delete m_ui; }

void MainWindow::setupTable()
{
    m_ui->tableView->setModel(m_model);
    m_ui->tableView->setSortingEnabled(true);
}

void MainWindow::connectSignals()
{
    connect(m_ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(m_ui->actionAddStudent, &QAction::triggered, this, &MainWindow::onAddStudent);
    connect(m_ui->actionManageSubjects, &QAction::triggered, this, &MainWindow::onManageSubjects);

    connect(m_ui->tableView, &QAbstractItemView::doubleClicked,
            this, &MainWindow::onRowDoubleClicked);

    connect(m_ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onSelectionChanged);
}

void MainWindow::onManageSubjects()
{
    SubjectManagerDialog dlg(m_addSubject, m_removeSubject, m_renameSubject, m_getAllSubjects, this);
    connect(&dlg, &SubjectManagerDialog::subjectsChanged, this, &MainWindow::refreshView);
    dlg.exec();
}

void MainWindow::onAddStudent()
{
    StudentDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;

    auto data = dlg.formData();
    try
    {
        m_addStudent.handle({data.firstName, data.lastName, data.albumNumber});
        refreshView();
    }
    catch (const std::exception &e)
    {
            QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onRowDoubleClicked(const QModelIndex &index)
{
    if (index.isValid()) openEditDialog(index.row());
}

void MainWindow::onSelectionChanged()
{
    int row = selectedRow();

    if (row < 0) {
        m_statusLabel->setText(QString("Students: %1").arg(m_model->rowCount()));
        return;
    }

    const auto &s = m_model->studentAt(row);
    double rate = m_model->passRateAt(row);

    if (rate < 0.0){
        m_statusLabel->setText(QString("%1 %2 - no subjects").arg(s.firstName, s.lastName));
    } else {
            int passed = static_cast<int>(std::count_if(
            s.subjects.begin(),
            s.subjects.end(),
            [](const Application::SubjectGradeDto &subject) { return subject.passed; }));
        int pct = static_cast<int>(rate * 100.0);
        m_statusLabel->setText(
            QString("%1 %2 | Passed: %3 / %4 (%5%)")
                .arg(s.firstName, s.lastName,
                    QString::number(passed),
                    QString::number(s.subjects.size()),
                    QString::number(pct)));
    }
}

void MainWindow::openEditDialog(int row)
{
    const auto &dto = m_model->studentAt(row);
    StudentEditDialog dlg(dto, m_getAllSubjects, this);

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    auto res = dlg.result();

    try {
            m_editStudent.handle({dto.albumNumber, res.firstName, res.lastName, res.subjects});

        refreshView();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::refreshView()
{
    auto students = m_getAllStudents.handle({});
    m_model->reset(students);

    auto *hh = m_ui->tableView->horizontalHeader();
    m_model->sort(hh->sortIndicatorSection(), hh->sortIndicatorOrder());

    m_statusLabel->setText(QString("Students: %1").arg(students.size()));
}

int MainWindow::selectedRow() const
{
    auto sel = m_ui->tableView->selectionModel()->selectedRows();

    return sel.isEmpty() ? -1 : sel.first().row();
}

} // namespace Presentation
