#pragma once

#include "details/Singleshot.hpp"

#include <QObject>

#include <vector>
#include <memory>

namespace Utility
{

// Lambda version
/**
 * @brief This function is used to perform a singleshot that delete the
 * connection after that.
 */
template<typename Sender, typename Signal,
         typename Slot>
QMetaObject::Connection singleShot(Sender * sender, Signal sig,
                                   Slot slot,
                                   const ConnectionPtr dynAllocConnection = nullptr);

// Member function version -------------------------------------------------
template<typename Sender, typename Signal,
         typename Receiver, typename Ret, typename... Args>
QMetaObject::Connection singleShot(Sender * sender, Signal sig,
                                   Receiver * receiver, Ret (Receiver::*slot)(Args ...),
                                   const ConnectionPtr dynAllocConnection = nullptr);

// Const member function version -------------------------------------------
template<typename Sender, typename Signal,
         typename Receiver, typename Ret, typename... Args>
QMetaObject::Connection
singleShot(Sender * sender, Signal sig,
           const Receiver * receiver, Ret (Receiver::*slot)(Args ...) const,
           const ConnectionPtr dynAllocConnection = nullptr);

/**
 * @brief Used to create single shot
 */
struct SingleShotGroup final
        : public std::enable_shared_from_this<SingleShotGroup>
{
    ~SingleShotGroup();

    template<typename Sender, typename Signal,
             typename Slot>
    QMetaObject::Connection addConnection(Sender * sender, Signal sig,
                                          Slot slot);

    template<typename Sender, typename Signal,
             typename Receiver, typename Ret, typename... Args>
    QMetaObject::Connection addConnection(Sender * sender, Signal sig,
                                          Receiver * receiver,
                                          Ret (Receiver::*slot)(Args ...));

    template<typename Sender, typename Signal,
             typename Receiver, typename Ret, typename... Args>
    QMetaObject::Connection addConnection(Sender * sender, Signal sig,
                                          const Receiver * receiver,
                                          Ret (Receiver::*slot)(Args ...) const);

    bool removeConnection(const QMetaObject::Connection & connection);
    void removeAllConnection();

public:
    template<typename ... Args>
    static std::shared_ptr<SingleShotGroup> make(Args && ... args);

public:
    std::vector<ConnectionPtr> connections;

private:
    SingleShotGroup() = default;
};

} // !namespace Utility

// Lambda single shot
template<typename Sender, typename Signal,
         typename Slot>
inline QMetaObject::Connection Utility::singleShot(Sender * sender, Signal sig, Slot slot,
                                                   const ConnectionPtr dynAllocConnection)
{
    return Details::connect(sender, sig, slot,
                            typename Details::FuncTrait<Slot>::TArgs {},
                            dynAllocConnection, [](const QMetaObject::Connection & connection)
    { QObject::disconnect(connection); });
}

// Member function single shot
template<typename Sender, typename Signal,
         typename Receiver, typename Ret, typename... Args>
inline QMetaObject::Connection Utility::singleShot(Sender * sender, Signal sig,
                                                   Receiver * receiver,
                                                   Ret (Receiver::*slot)(Args ...),
                                                   const ConnectionPtr dynAllocConnection)
{
    return Details::connect(sender, sig, receiver, slot,
                            Details::Pack<Args ...> {}, dynAllocConnection,
                            [](const QMetaObject::Connection & connection)
    { QObject::disconnect(connection); });
}

// Const-member single shot
template<typename Sender, typename Signal,
         typename Receiver, typename Ret, typename... Args>
inline QMetaObject::Connection Utility::singleShot(Sender * sender, Signal sig,
                                                   const Receiver * receiver,
                                                   Ret (Receiver::*slot)(Args ...) const,
                                                   const ConnectionPtr dynAllocConnection)
{
    return Details::connect(sender, sig, receiver, slot,
                            Details::Pack<Args ...> {}, dynAllocConnection,
                            [](const QMetaObject::Connection & connection)
    { QObject::disconnect(connection); });
}

// Lambda single shot group
template<typename Sender, typename Signal, typename Slot>
inline QMetaObject::Connection Utility::SingleShotGroup::addConnection(Sender * sender, Signal sig,
                                                                       Slot slot)
{
    const auto selfPtr       = shared_from_this();
    const auto connectionPtr = std::make_shared<QMetaObject::Connection>();

    connections.push_back(connectionPtr);

    return Details::connect(sender, sig, slot, typename Details::FuncTrait<Slot>::TArgs {},
                            connectionPtr, [selfPtr](const QMetaObject::Connection &)
    { selfPtr->removeAllConnection(); });
}

// Member function single shot group
template<typename Sender, typename Signal,
         typename Receiver, typename Ret, typename... Args>
inline QMetaObject::Connection
Utility::SingleShotGroup::addConnection(Sender * sender, Signal sig, Receiver * receiver,
                                        Ret (Receiver::*slot)(Args ...))
{
    return addConnection(sender, sig, [receiver, slot](Args ... args)
    { (receiver->*slot)(std::forward<Args>(args)...); });
}

// Const-member function single shot group
template<typename Sender, typename Signal,
         typename Receiver, typename Ret, typename... Args>
inline QMetaObject::Connection
Utility::SingleShotGroup::addConnection(Sender * sender, Signal sig, const Receiver * receiver,
                                        Ret (Receiver::*slot)(Args ...) const)
{
    return addConnection(sender, sig, [receiver, slot](Args ... args)
    { (receiver->*slot)(std::forward<Args>(args)...); });
}

template<typename... Args>
std::shared_ptr<Utility::SingleShotGroup> Utility::SingleShotGroup::make(Args && ... args)
{
    return std::shared_ptr<SingleShotGroup>(new SingleShotGroup(std::forward<Args>(args)...));
}
