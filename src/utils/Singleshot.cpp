#include "Singleshot.hpp"

Utility::SingleShotGroup::~SingleShotGroup()
{
    removeAllConnection();
}

bool Utility::SingleShotGroup::removeConnection(const QMetaObject::Connection & connection)
{
    const auto itr = std::find_if(connections.cbegin(), connections.cend(),
                                  [connection](const ConnectionPtr & c)
    { return *c == connection; });

    if (itr == connections.end())
        return false;

    QObject::disconnect(*itr->get());
    connections.erase(itr);
    return true;
}

void Utility::SingleShotGroup::removeAllConnection()
{
    std::for_each(connections.cbegin(), connections.cend(),
                  [](const ConnectionPtr & connection)
    { QObject::disconnect(*connection); });

    connections.clear();
}
