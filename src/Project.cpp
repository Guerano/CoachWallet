#include "Project.hpp"

Project::Project(QString const & name, QString const & tokenName)
    : _name      { name      }
    , _tokenName { tokenName }
{
}

auto Project::name() const
    -> QString const &
{
    return _name;
}

auto Project::tokenName() const
    -> QString const &
{
    return _tokenName;
}

float Project::price() const
{
    // TODO: return call from an external API
    return 42;
}
