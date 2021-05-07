#include "UserView.hpp"
#include "ui_UserView.h"

UserView::UserView(QWidget * parent)
    : QWidget { parent           }
    , _ui     { new Ui::UserView }
{
    _ui->setupUi(this);
}

UserView::~UserView()
{
    delete _ui;
}
