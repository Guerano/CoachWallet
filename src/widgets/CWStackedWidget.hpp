#pragma once

// Project includes
#include "IWorkspaceView.hpp"

// Qt includes
#include <QStackedWidget>

// C++ includes
#include <set>

class CWStackedWidget : public QStackedWidget
{
    Q_OBJECT

    using ViewList = std::vector<IWorkspaceView *>;

public:
    CWStackedWidget(QWidget * parent = nullptr);

    template <typename T, typename... Args>
    auto stack(Args... args) -> T *;
    void unstack();

private:
    /// Returns the index of the view in _views, or -1 if not found
    int  _viewIndex(QString const & identifier) const;
    bool _bringViewOnTop(int viewIndex);

private:
    ViewList _views;
};

// ================== Templated Implementations ================== //

template <typename T, typename... Args>
auto CWStackedWidget::stack(Args... args)
    -> T *
{
    static_assert (std::is_base_of_v<IWorkspaceView, T>,
            "Trying to stack a view that does not inherit from IWorkspaceView");

    auto identifier = T::createIdentifier(args...);

    if (auto const index = _viewIndex(identifier); index != -1) // Already present
    {
        _bringViewOnTop(index);
        return dynamic_cast<T *>(widget(count() - 1));
    }
    else
    {
        auto newView = new T(args..., this);
        addWidget(newView);
        setCurrentIndex(count() - 1);

        connect(newView, &T::finished, this, &CWStackedWidget::unstack);

        return newView;
    }
}
