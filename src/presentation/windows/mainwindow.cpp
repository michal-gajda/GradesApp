#include "presentation/windows/mainwindow.h"
#include <QMessageBox>
#include "presentation/dialogs/studentdialog.h"
#include "presentation/dialogs/studenteditdialog.h"
#include "presentation/dialogs/subjectmanagerdialog.h"
#include "ui_MainWindow.h"
#include <QHeaderView>

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
    , m_model(new StudentTableModel(this))
    , m_statusLabel(new QLabel(this))
    , m_presenter(*this,
                  addStudent,
                  removeStudent,
                  editStudent,
                  addSubject,
                  removeSubject,
                  renameSubject,
                  getAllStudents,
                  getAllSubjects)
{
    m_ui->setupUi(this);
    m_ui->statusBar->addWidget(m_statusLabel);

    setupTable();
    connectSignals();
    m_presenter.initialize();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::setupTable()
{
    m_ui->tableView->setModel(m_model);
    m_ui->tableView->setSortingEnabled(true);
    m_ui->tableView->horizontalHeader()->setStretchLastSection(true);
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
    m_presenter.onManageSubjectsClicked();
}

void MainWindow::onAddStudent()
{
    m_presenter.onAddStudentClicked();
}

void MainWindow::onRowDoubleClicked(const QModelIndex &index)
{
    m_presenter.onRowDoubleClicked(index);
}

void MainWindow::onSelectionChanged()
{
    m_presenter.onSelectionChanged();
}

StudentTableModel &MainWindow::tableModel()
{
    return *m_model;
}

QWidget *MainWindow::asWidget()
{
    return this;
}

int MainWindow::selectedRow() const
{
    auto sel = m_ui->tableView->selectionModel()->selectedRows();

    return sel.isEmpty() ? -1 : sel.first().row();
}

int MainWindow::sortSection() const
{
    return m_ui->tableView->horizontalHeader()->sortIndicatorSection();
}

Qt::SortOrder MainWindow::sortOrder() const
{
    return m_ui->tableView->horizontalHeader()->sortIndicatorOrder();
}

void MainWindow::setStatusText(const QString &text)
{
    m_statusLabel->setText(text);
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::critical(this, "Error", message);
}

bool MainWindow::openStudentDialog(StudentFormData &formData)
{
    StudentDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) {
        return false;
    }
    formData = dlg.formData();
    return true;
}

bool MainWindow::openStudentEditDialog(const Application::StudentDto &student,
                                       Application::GetAllSubjectsHandler &getAllSubjects,
                                       StudentEditResult &result)
{
    StudentEditDialog dlg(student, getAllSubjects, this);
    if (dlg.exec() != QDialog::Accepted) {
        return false;
    }
    result = dlg.result();
    return true;
}

void MainWindow::openSubjectManagerDialog(Application::AddSubjectHandler &addSubject,
                                          Application::RemoveSubjectHandler &removeSubject,
                                          Application::RenameSubjectHandler &renameSubject,
                                          Application::GetAllSubjectsHandler &getAllSubjects,
                                          const std::function<void()> &onSubjectsChanged)
{
    SubjectManagerDialog dlg(addSubject, removeSubject, renameSubject, getAllSubjects, this);
    connect(&dlg, &SubjectManagerDialog::subjectsChanged, this, [onSubjectsChanged]() { onSubjectsChanged(); });
    dlg.exec();
}

}
