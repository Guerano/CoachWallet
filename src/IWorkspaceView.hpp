#pragma once

// Qt includes
#include <QString>
#include <QWidget>

class IWorkspaceView : public QWidget
{
public:
    IWorkspaceView(QWidget * parent = nullptr)
        : QWidget { parent }
    {}

    virtual auto viewIdentifier() const -> QString = 0;
};
