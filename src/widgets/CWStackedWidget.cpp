#include "CWStackedWidget.hpp"

// Project includes
#include "views/HomeView.hpp"
#include "views/UserView.hpp"
#include "utils/StringFormatting.hpp"

// Qt includes
#include <QDebug>

CWStackedWidget::CWStackedWidget(QWidget * parent) :
    QStackedWidget { parent }
{
    stack<HomeView>();
    stack<UserView>(User { "Robin", "Rebischung" });
}

void CWStackedWidget::unstack()
{
    if (count() <= 1) // Just the HomeView left, can't be removed
        return;

    auto viewToBeRemoved = widget(count() - 1);
    removeWidget(viewToBeRemoved);

    viewToBeRemoved->deleteLater();
}

int CWStackedWidget::_viewIndex(QString const & identifier) const
{
    for (auto i = 0; i < count(); ++i)
    {
        auto workspaceWidget = dynamic_cast<IWorkspaceView *>(widget(i));
        if (!workspaceWidget)
        {
            qWarning() << "[%1] Could not cast a widget from the stack widget to IWorkspaceView *"_s
                          % Q_FUNC_INFO;
            continue;
        }

        if (workspaceWidget->viewIdentifier() == identifier)
            return i;
    }

    return -1;
}

bool CWStackedWidget::_bringViewOnTop(int viewIndex)
{
    if (viewIndex < 0 || viewIndex >= count())
    {
        qWarning() << "[%1] Trying to bring on top widget at invalid index '%2'/'%3'"_s
                      % Q_FUNC_INFO % viewIndex % count();
        return false;
    }

    auto view = widget(viewIndex);
    removeWidget(view);
    addWidget(view);

    setCurrentIndex(count() - 1);

    return true;
}
