#include "presentation/dialogs/studentdialog.h"
#include "ui_StudentDialog.h"
#include <QMessageBox>

namespace Presentation {

StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::StudentDialog)
    , m_presenter(*this)
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
    return {albumNumber(), firstName(), lastName()};
}

QString StudentDialog::albumNumber() const
{
    return m_ui->lineEditAlbum->text().trimmed();
}

QString StudentDialog::firstName() const
{
    return m_ui->lineEditFirstName->text().trimmed();
}

QString StudentDialog::lastName() const
{
    return m_ui->lineEditLastName->text().trimmed();
}

void StudentDialog::onOk()
{
    m_presenter.onOkClicked();
}

void StudentDialog::showWarning(const QString &title, const QString &message)
{
    QMessageBox::warning(this, title, message);
}

void StudentDialog::acceptDialog()
{
    accept();
}

}
