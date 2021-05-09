#pragma once

#include <QString>

class IWorkspaceView
{
public:
    virtual auto viewIdentifier() const -> QString = 0;
};
