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
    , m_getAllSubjects(getAllSubjectsHandler)
    , m_subjects(student.subjects)
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

    m_ui->lineEditAlbum->setText(student.albumNumber);
    m_ui->lineEditFirstName->setText(student.firstName);
    m_ui->lineEditLastName->setText(student.lastName);

    rebuildList();

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
    return {m_ui->lineEditFirstName->text().trimmed(),
            m_ui->lineEditLastName->text().trimmed(),
            m_subjects};
}

void StudentEditDialog::onAddSubject()
{
    const auto catalog = m_getAllSubjects.handle({});
    if (catalog.isEmpty()) {
        QMessageBox::information(this, "No subjects", "Subject catalog is empty. Add subjects in Manage subjects first.");
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
        QMessageBox::information(this, "No subjects", "All catalog subjects are already assigned to this student.");
        return;
    }

    bool ok = false;
    QString selected = QInputDialog::getItem(this,
                                                "Assign subject",
                                                "Subject:",
                                                available,
                                                0,
                                                false,
                                                &ok);
    if (!ok || selected.trimmed().isEmpty()) {
        return;
    }

    syncSubjectsFromList();
    m_subjects.append({selected.trimmed(), false});
    rebuildList();
}

void StudentEditDialog::onRemoveSubject()
{
    int row = m_ui->listSubjects->currentRow();

    if (row < 0) {
        QMessageBox::information(this, "Remove subject", "Select a subject from the list.");

        return;
    }

    QString name = m_ui->listSubjects->item(row)->text().trimmed();
    auto ans = QMessageBox::question(this,
                                        "Remove subject",
                                        QString("Remove \"%1\" from this student?").arg(name),
                                        QMessageBox::Yes | QMessageBox::No);

    if (ans != QMessageBox::Yes) {
        return;
    }

    syncSubjectsFromList();
    m_subjects.removeAt(row);
    rebuildList();
}

void StudentEditDialog::onOk()
{
    if (m_ui->lineEditFirstName->text().trimmed().isEmpty()
        || m_ui->lineEditLastName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "First and last name are required.");

        return;
    }

    syncSubjectsFromList();
    accept();
}

void StudentEditDialog::rebuildList()
{
    m_ui->listSubjects->clear();

    for (int i = 0; i < m_subjects.size(); ++i) {
        auto *item = new QListWidgetItem(m_subjects[i].name.trimmed(), m_ui->listSubjects);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(m_subjects[i].passed ? Qt::Checked : Qt::Unchecked);
    }
}

void StudentEditDialog::syncSubjectsFromList()
{
    m_subjects.resize(m_ui->listSubjects->count());

    for (int i = 0; i < m_ui->listSubjects->count(); ++i) {
        auto *item = m_ui->listSubjects->item(i);
        m_subjects[i].name = item->text().trimmed();
        m_subjects[i].passed = (item->checkState() == Qt::Checked);
    }
}

} // namespace Presentation
