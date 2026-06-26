#include "presentation/dialogs/subjectmanagerdialog.h"
#include "ui_SubjectManagerDialog.h"
#include "application/commands/addsubjectcommand.h"
#include <QInputDialog>
#include <QMessageBox>

namespace Presentation {

SubjectManagerDialog::SubjectManagerDialog(Application::AddSubjectHandler &addHandler,
                                            Application::RemoveSubjectHandler &removeHandler,
                                            Application::RenameSubjectHandler &renameHandler,
                                            Application::GetAllSubjectsHandler &getAllHandler,
                                            QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::SubjectManagerDialog)
    , m_addHandler(addHandler)
    , m_removeHandler(removeHandler)
    , m_renameHandler(renameHandler)
    , m_getAllHandler(getAllHandler)
{
    m_ui->setupUi(this);
    setWindowFlag(Qt::CustomizeWindowHint, true);
    setWindowFlag(Qt::WindowTitleHint, true);
    setWindowFlag(Qt::WindowSystemMenuHint, true);
    setWindowFlag(Qt::WindowCloseButtonHint, true);
    setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
    setFixedSize(size());

    connect(m_ui->buttonAdd, &QPushButton::clicked, this, &SubjectManagerDialog::onAdd);
    connect(m_ui->buttonRemove, &QPushButton::clicked, this, &SubjectManagerDialog::onRemove);
    connect(m_ui->buttonRename, &QPushButton::clicked, this, &SubjectManagerDialog::onRename);

    refreshList();
}

SubjectManagerDialog::~SubjectManagerDialog() { delete m_ui; }

void SubjectManagerDialog::onAdd()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, "Add subject", "Name:", QLineEdit::Normal, {}, &ok);

    if (!ok || name.trimmed().isEmpty()) {
        return;
    }

    try {
        m_addHandler.handle({name.trimmed()});
        refreshList();
        emit subjectsChanged();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void SubjectManagerDialog::onRemove()
{
    int row = m_ui->listWidget->currentRow();

    if (row < 0) {
        QMessageBox::information(this, "Remove", "Select a subject.");
        return;
    }

    QString name = m_ui->listWidget->currentItem()->text();
    auto ans = QMessageBox::question(this,
                                        "Remove subject",
                                        QString(
                                            "Remove \"%1\"? Grades will be removed for all students.")
                                            .arg(name),
                                        QMessageBox::Yes | QMessageBox::No);
    if (ans != QMessageBox::Yes) {
        return;
    }

    try {
        m_removeHandler.handle({row});
        refreshList();
        emit subjectsChanged();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void SubjectManagerDialog::onRename()
{
    int row = m_ui->listWidget->currentRow();

    if (row < 0) {
        QMessageBox::information(this, "Rename", "Select a subject.");
        return;
    }

    bool ok = false;
    QString newName = QInputDialog::getText(this,
                                            "Rename",
                                            "New name:",
                                            QLineEdit::Normal,
                                            m_ui->listWidget->currentItem()->text(),
                                            &ok);
    if (!ok || newName.trimmed().isEmpty()) {
        return;
    }

    try {
        m_renameHandler.handle({row, newName.trimmed()});
        refreshList();
        emit subjectsChanged();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void SubjectManagerDialog::refreshList()
{
    m_ui->listWidget->clear();

    for (const auto &s : m_getAllHandler.handle({})) {
        m_ui->listWidget->addItem(s.name);
    }
}

} // namespace Presentation
