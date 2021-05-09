#pragma once

#include "utils/ServiceLocator.hpp"

#include <QApplication>

class CoachWalletApplication : public QApplication, public Utility::ServiceLocator
{
public:
    CoachWalletApplication(int argc, char *argv[]);
    ~CoachWalletApplication() override = default;
};

#define sApp static_cast<CoachWalletApplication *>(CoachWalletApplication::instance())