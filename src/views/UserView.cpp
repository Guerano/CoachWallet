#include "UserView.hpp"
#include "ui_UserView.h"

#include "utils/StringFormatting.hpp"

UserView::UserView(User const & user, QWidget * parent)
    : QWidget { parent           }
    , _ui     { new Ui::UserView }
    , _user   { user             }
{
    _ui->setupUi(this);
}

UserView::~UserView()
{
    delete _ui;
}

auto UserView::viewIdentifier() const
    -> QString
{
    return "UserView_%1_%2"_s % _user.firstName() % _user.lastName();
}
