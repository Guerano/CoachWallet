#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow { parent             }
    , _ui         { new Ui::MainWindow }
{
    _ui->setupUi(this);

    _initView();
    _setupConnections();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::_initView()
{
    setWindowTitle("CoachWallet");

    _ui->splitter->setStretchFactor(1, 1);
    _ui->splitter->setStretchFactor(0, 0);
}

void MainWindow::_setupConnections()
{

}

