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
    ~IWorkspaceView() override = default;

    virtual auto viewIdentifier() const -> QString = 0;

/*signals:*/
    virtual void finished() = 0;
};
