#include "presentation/dialogs/studentdialog.h"
#include "ui_StudentDialog.h"
#include <QMessageBox>

namespace Presentation {

StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::StudentDialog)
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
    connect(m_ui->buttonOk, &QPushButton::clicked, this, &StudentDialog::onOk);
}

StudentDialog::~StudentDialog() { delete m_ui; }

StudentFormData StudentDialog::formData() const
{
    return {m_ui->lineEditAlbum->text().trimmed(),
            m_ui->lineEditFirstName->text().trimmed(),
            m_ui->lineEditLastName->text().trimmed()};
}

void StudentDialog::onOk()
{
    if (m_ui->lineEditAlbum->text().trimmed().isEmpty()
        || m_ui->lineEditFirstName->text().trimmed().isEmpty()
        || m_ui->lineEditLastName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields are required.");

        return;
    }

    accept();
}

} // namespace Presentation
