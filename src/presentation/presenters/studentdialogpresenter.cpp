#include "presentation/presenters/studentdialogpresenter.h"

namespace Presentation {

void StudentDialogPresenter::onOkClicked()
{
    if (m_view.albumNumber().trimmed().isEmpty()
        || m_view.firstName().trimmed().isEmpty()
        || m_view.lastName().trimmed().isEmpty()) {
        m_view.showWarning("Error", "All fields are required.");
        return;
    }

    m_view.acceptDialog();
}

}