#include "presentation/dialogs/subjectmanagerdialog.h"
#include "ui_SubjectManagerDialog.h"
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
    , m_presenter(*this, addHandler, removeHandler, renameHandler, getAllHandler)
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

    m_presenter.initialize();
}

SubjectManagerDialog::~SubjectManagerDialog()
{
    delete m_ui;
}

void SubjectManagerDialog::onAdd()
{
    m_presenter.onAddClicked();
}

void SubjectManagerDialog::onRemove()
{
    m_presenter.onRemoveClicked();
}

void SubjectManagerDialog::onRename()
{
    m_presenter.onRenameClicked();
}

int SubjectManagerDialog::currentRow() const
{
    return m_ui->listWidget->currentRow();
}

QString SubjectManagerDialog::currentName() const
{
    auto *item = m_ui->listWidget->currentItem();
    return item ? item->text() : QString();
}

QString SubjectManagerDialog::askText(const QString &title,
                                      const QString &label,
                                      const QString &defaultValue,
                                      bool &ok)
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setTextEchoMode(QLineEdit::Normal);
    dialog.setTextValue(defaultValue);
    dialog.setMinimumWidth(260);
    dialog.adjustSize();

    ok = (dialog.exec() == QDialog::Accepted);
    return ok ? dialog.textValue() : QString();
}

bool SubjectManagerDialog::confirm(const QString &title, const QString &message)
{
    return QMessageBox::question(this, title, message, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

void SubjectManagerDialog::showInfo(const QString &title, const QString &message)
{
    QMessageBox::information(this, title, message);
}

void SubjectManagerDialog::showError(const QString &title, const QString &message)
{
    QMessageBox::critical(this, title, message);
}

void SubjectManagerDialog::setSubjects(const QStringList &names)
{
    m_ui->listWidget->clear();
    for (const auto &name : names) {
        m_ui->listWidget->addItem(name);
    }
}

void SubjectManagerDialog::notifySubjectsChanged()
{
    emit subjectsChanged();
}

}
