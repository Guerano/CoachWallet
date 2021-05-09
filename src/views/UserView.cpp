#include "UserView.hpp"
#include "ui_UserView.h"

// Project includes
#include "utils/StringFormatting.hpp"

// Qt includes
#include <QPushButton>

UserView::UserView(User const & user, QWidget * parent)
    : IWorkspaceView { parent           }
    , _ui            { new Ui::UserView }
    , _user          { user             }
{
    _ui->setupUi(this);

    _setupConnections();
}

UserView::~UserView()
{
    delete _ui;
}

auto UserView::viewIdentifier() const
    -> QString
{
    return createIdentifier(_user);
}

auto UserView::createIdentifier(User const & user)
    -> QString
{
    return "UserView_%1_%2"_s % user.firstName() % user.lastName();
}

void UserView::_setupConnections()
{
    // Ok click
    connect(_ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked,
            this,                                         &UserView::finished);
}
