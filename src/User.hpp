#pragma once

#include <QString>

class User
{
public:
    User(QString const & firstName, QString const & lastName, QString const & email = {});

    auto firstName() const -> QString const &;
    auto lastName()  const -> QString const &;
    auto email()     const -> QString;

private:
    QString const _firstName;
    QString const _lastName;
    QString       _email;
};

