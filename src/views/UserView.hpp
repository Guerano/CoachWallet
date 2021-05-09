#pragma once

// Project includes
#include "IWorkspaceView.hpp"
#include "User.hpp"

namespace Ui { class UserView; }

class UserView : public IWorkspaceView
{
    Q_OBJECT

public:
    explicit UserView(User const & user, QWidget * parent = nullptr);
    ~UserView();

    auto viewIdentifier() const -> QString override;

signals:
    void finished() override;

public:
    static auto createIdentifier(User const & user) -> QString;

private:
    void _setupConnections();

private:
    Ui::UserView * _ui;

    User _user;
};

