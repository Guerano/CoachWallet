#include "User.hpp"

User::User(const QString &firstName, const QString &lastName, const QString &email)
    : _firstName { firstName }
    , _lastName  { lastName  }
    , _email     { email     }
{
}

auto User::firstName() const
    -> QString const &
{
    return _firstName;
}

auto User::lastName() const
    -> QString const &
{
    return _lastName;
}

auto User::email() const
    -> QString
{
    return _email;
}

