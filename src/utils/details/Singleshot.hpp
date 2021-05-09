#pragma once

#include <QObject>

#include <memory>
#include <functional>

namespace Utility
{
using ConnectionPtr = std::shared_ptr<QMetaObject::Connection>;

namespace Details
{

using Callback = std::function<void (const QMetaObject::Connection &)>;

template<typename... Args> struct Pack {};

template<typename F>
struct FuncTrait
{
    using type  = decltype(&F::operator());
    using TArgs = typename FuncTrait<type>::TArgs;
};

template<typename C, typename R, typename... Args>
struct FuncTrait<R (C::*)(Args...) const>
{
    using TArgs = Pack<Args...>;
};

template<typename C, typename R, typename... Args>
struct FuncTrait<R (C::*)(Args...)>
{
    using TArgs = Pack<Args...>;
};

template<typename R, typename... Args>
struct FuncTrait<R (*)(Args...)>
{
    using TArgs = Pack<Args...>;
};

inline const ConnectionPtr getConnection(const ConnectionPtr c)
{
    return c != nullptr ? c
                        : std::make_shared<QMetaObject::Connection>();
}

// Lambda
template<typename Sender, typename Signal,
         typename Slot,
         typename... Args>
QMetaObject::Connection connect(Sender * sender, Signal sig,
                                Slot slot,
                                Pack<Args...>,
                                const ConnectionPtr dynAllocConnection,
                                Callback cb)
{
    const auto connection = getConnection(dynAllocConnection);

    *connection = QObject::connect(sender, sig, [connection, slot, cb](Args ... args)
    {
        cb(*connection);
        slot(std::forward<Args>(args)...);
    });

    return *connection;
}

// Member-function
template<typename Sender, typename Signal,
         typename Receiver, typename Ret,
         typename... Args>
QMetaObject::Connection connect(Sender * sender, Signal sig,
                                Receiver * receiver, Ret (Receiver::*slot)(Args ...),
                                Pack<Args...>,
                                const ConnectionPtr dynAllocConnection,
                                Callback cb)
{
    const auto connection = getConnection(dynAllocConnection);

    *connection = QObject::connect(sender, sig, receiver, [connection, receiver, slot, cb](Args ... args)
    {
        cb(*connection);
        (receiver->*slot)(std::forward<Args>(args)...);
    });

    return *connection;
}

// Const-member function
template<typename Sender, typename Signal,
         typename Receiver, typename Ret,
         typename... Args>
QMetaObject::Connection connect(Sender * sender, Signal sig,
                                const Receiver * receiver, Ret (Receiver::*slot)(Args ...) const,
                                Pack<Args...>,
                                const ConnectionPtr dynAllocConnection,
                                Callback cb)
{
    const auto connection = getConnection(dynAllocConnection);

    *connection = QObject::connect(sender, sig, receiver, [connection, receiver, slot, cb](Args ... args)
    {
        cb(*connection);
        (receiver->*slot)(std::forward<Args>(args)...);
    });

    return *connection;
}
} // !namespace Details
} // !namespace Utility::Details
