#include "HomeView.hpp"
#include "ui_HomeView.h"

HomeView::HomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeView)
{
    ui->setupUi(this);
}

HomeView::~HomeView()
{
    delete ui;
}
