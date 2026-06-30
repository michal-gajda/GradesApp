#ifndef PRESENTATION_PRESENTERS_STUDENTDIALOGPRESENTER_H
#define PRESENTATION_PRESENTERS_STUDENTDIALOGPRESENTER_H

#include <QString>

namespace Presentation {

class IStudentDialogView
{
public:
    virtual ~IStudentDialogView() = default;
    virtual QString albumNumber() const = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;
    virtual void showWarning(const QString &title, const QString &message) = 0;
    virtual void acceptDialog() = 0;
};

class StudentDialogPresenter
{
public:
    explicit StudentDialogPresenter(IStudentDialogView &view)
        : m_view(view)
    {}

    void onOkClicked();

private:
    IStudentDialogView &m_view;
};

}

#endif