#pragma once

#include <QTreeWidget>

class NavigatorTree : public QTreeWidget
{
    Q_OBJECT

public:
    enum Error
    {
        NoError,
    };

    enum Type
    {
        Users,
        Projects,
        Trading,
        Portfolios,
    };
    Q_ENUM(Type);

public:
    NavigatorTree(QWidget * parent = nullptr);

    auto addUser() -> Error;

private:
    void _initView();
    void _setupConnections();

    auto _getTypeMetaEnum() -> QMetaEnum;
};

