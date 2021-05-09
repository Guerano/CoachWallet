#pragma once

#include "IWorkspaceView.hpp"

#include <QWidget>

namespace Ui { class HomeView; }

class HomeView : public QWidget, public IWorkspaceView
{
    Q_OBJECT

public:
    explicit HomeView(QWidget * parent = nullptr);
    ~HomeView();

    auto viewIdentifier() const -> QString override;

private:
    Ui::HomeView * _ui;
};

