#include "presentation/dialogs/studenteditdialog.h"
#include "ui_StudentEditDialog.h"
#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>

namespace Presentation {

StudentEditDialog::StudentEditDialog(const Application::StudentDto &student,
                                     Application::GetAllSubjectsHandler &getAllSubjectsHandler,
                                     QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::StudentEditDialog)
    , m_presenter(*this, student, getAllSubjectsHandler)
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

    m_presenter.initialize();

    connect(m_ui->buttonAddSubject, &QPushButton::clicked, this, &StudentEditDialog::onAddSubject);
    connect(m_ui->buttonRemoveSubject,
            &QPushButton::clicked,
            this,
            &StudentEditDialog::onRemoveSubject);
    connect(m_ui->buttonOk, &QPushButton::clicked, this, &StudentEditDialog::onOk);
}

StudentEditDialog::~StudentEditDialog()
{
    delete m_ui;
}

StudentEditResult StudentEditDialog::result() const
{
    return {firstName().trimmed(),
            lastName().trimmed(),
            m_presenter.subjects()};
}

void StudentEditDialog::onAddSubject()
{
    m_presenter.onAddSubjectClicked();
}

void StudentEditDialog::onRemoveSubject()
{
    m_presenter.onRemoveSubjectClicked();
}

void StudentEditDialog::onOk()
{
    m_presenter.onOkClicked();
}

void StudentEditDialog::setAlbum(const QString &value)
{
    m_ui->lineEditAlbum->setText(value);
}

void StudentEditDialog::setFirstName(const QString &value)
{
    m_ui->lineEditFirstName->setText(value);
}

void StudentEditDialog::setLastName(const QString &value)
{
    m_ui->lineEditLastName->setText(value);
}

QString StudentEditDialog::firstName() const
{
    return m_ui->lineEditFirstName->text();
}

QString StudentEditDialog::lastName() const
{
    return m_ui->lineEditLastName->text();
}

void StudentEditDialog::clearSubjectsList()
{
    m_ui->listSubjects->clear();
}

void StudentEditDialog::addSubjectToList(const QString &name, bool passed)
{
    auto *item = new QListWidgetItem(name.trimmed(), m_ui->listSubjects);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(passed ? Qt::Checked : Qt::Unchecked);
}

int StudentEditDialog::selectedSubjectRow() const
{
    return m_ui->listSubjects->currentRow();
}

QString StudentEditDialog::selectedSubjectName() const
{
    const int row = m_ui->listSubjects->currentRow();
    if (row < 0 || row >= m_ui->listSubjects->count()) {
        return {};
    }
    return m_ui->listSubjects->item(row)->text();
}

int StudentEditDialog::subjectsCount() const
{
    return m_ui->listSubjects->count();
}

QString StudentEditDialog::subjectNameAt(int index) const
{
    if (index < 0 || index >= m_ui->listSubjects->count()) {
        return {};
    }
    return m_ui->listSubjects->item(index)->text();
}

bool StudentEditDialog::subjectPassedAt(int index) const
{
    if (index < 0 || index >= m_ui->listSubjects->count()) {
        return false;
    }
    return m_ui->listSubjects->item(index)->checkState() == Qt::Checked;
}

void StudentEditDialog::showInfo(const QString &title, const QString &message)
{
    QMessageBox::information(this, title, message);
}

void StudentEditDialog::showWarning(const QString &title, const QString &message)
{
    QMessageBox::warning(this, title, message);
}

void StudentEditDialog::showError(const QString &title, const QString &message)
{
    QMessageBox::critical(this, title, message);
}

bool StudentEditDialog::confirm(const QString &title, const QString &message)
{
    return QMessageBox::question(this, title, message, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

QString StudentEditDialog::askItem(const QString &title,
                                   const QString &label,
                                   const QStringList &items,
                                   bool &ok)
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setComboBoxItems(items);
    dialog.setComboBoxEditable(false);
    dialog.setMinimumWidth(260);
    dialog.adjustSize();

    ok = (dialog.exec() == QDialog::Accepted);
    return ok ? dialog.textValue() : QString();
}

void StudentEditDialog::acceptDialog()
{
    accept();
}

}
