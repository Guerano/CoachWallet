#pragma once

#include "IWorkspaceView.hpp"
#include "User.hpp"

#include <QWidget>

namespace Ui { class UserView; }

class UserView : public QWidget, public IWorkspaceView
{
    Q_OBJECT

public:
    explicit UserView(User const & user, QWidget * parent = nullptr);
    ~UserView();

    auto viewIdentifier() const -> QString override;

private:
    Ui::UserView * _ui;

    User _user;
};

