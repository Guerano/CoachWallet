#pragma once

// Project includes
#include "IWorkspaceView.hpp"

namespace Ui { class HomeView; }

class HomeView : public IWorkspaceView
{
    Q_OBJECT

public:
    explicit HomeView(QWidget * parent = nullptr);
    ~HomeView();

    auto viewIdentifier() const -> QString override;

private:
    Ui::HomeView * _ui;
};

