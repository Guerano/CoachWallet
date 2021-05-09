#include "CoachWalletApplication.hpp"
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    CoachWalletApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
