#pragma once

#include <QWidget>

namespace Ui { class UserView; }

class UserView : public QWidget
{
    Q_OBJECT

public:
    explicit UserView(QWidget * parent = nullptr);
    ~UserView();

private:
    Ui::UserView * _ui;
};

