#ifndef PRESENTATION_DIALOGS_STUDENTDIALOG_H
#define PRESENTATION_DIALOGS_STUDENTDIALOG_H

#include "presentation/presenters/studentdialogpresenter.h"
#include <QDialog>

namespace Ui { class StudentDialog; }

namespace Presentation {

struct StudentFormData
{
    QString albumNumber;
    QString firstName;
    QString lastName;
};

class StudentDialog : public QDialog, public IStudentDialogView
{
    Q_OBJECT

public:
    explicit StudentDialog(QWidget *parent = nullptr);
    ~StudentDialog();

    StudentFormData formData() const;
    QString albumNumber() const override;
    QString firstName() const override;
    QString lastName() const override;
    void showWarning(const QString &title, const QString &message) override;
    void acceptDialog() override;

private slots:
    void onOk();

private:
    Ui::StudentDialog *m_ui;
    StudentDialogPresenter m_presenter;
};

} // namespace Presentation

#endif // PRESENTATION_DIALOGS_STUDENTDIALOG_H

