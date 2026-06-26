#ifndef PRESENTATION_DIALOGS_STUDENTDIALOG_H
#define PRESENTATION_DIALOGS_STUDENTDIALOG_H

#include <QDialog>

namespace Ui { class StudentDialog; }

namespace Presentation {

struct StudentFormData
{
    QString albumNumber;
    QString firstName;
    QString lastName;
};

class StudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDialog(QWidget *parent = nullptr);
    ~StudentDialog();

    StudentFormData formData() const;

private slots:
    void onOk();

private:
    Ui::StudentDialog *m_ui;
};

} // namespace Presentation

#endif // PRESENTATION_DIALOGS_STUDENTDIALOG_H

