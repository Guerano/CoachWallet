#include "HomeView.hpp"
#include "ui_HomeView.h"

HomeView::HomeView(QWidget * parent)
    : QWidget { parent           }
    , _ui     { new Ui::HomeView }
{
    _ui->setupUi(this);
}

HomeView::~HomeView()
{
    delete _ui;
}

auto HomeView::viewIdentifier() const
    -> QString
{
    return "HomeView";
}
