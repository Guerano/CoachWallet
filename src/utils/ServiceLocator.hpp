#pragma once

// Project includes
#include "Service.hpp"

// C++ includes
#include <memory>
#include <unordered_map>

// Qt includes
#include <QString>

namespace Utility { class ServiceLocator; }

/**
 * @brief Manage all services
 */
class Utility::ServiceLocator
{
private:
    using ServicePtr = std::unique_ptr<Utility::Service>;
    std::unordered_map<std::string, ServicePtr> _services;

public:
    virtual ~ServiceLocator() = default;

public:
    template<typename T, typename... Args>
    auto addService(const std::string & name, Args &&... args) -> T &;

    bool delService(const std::string & name);

    bool hasService(const std::string & name) const;

    template<typename T>
    auto service(const std::string & name) -> T &;

    void clear();
};

template<typename T, typename... Args>
auto Utility::ServiceLocator::addService(const std::string & name, Args &&... args) -> T &
{
    static_assert(std::is_base_of<Service, T>::value,
            "T must be a descendant of Utility::Service");

    ServicePtr service { new T { std::forward<Args>(args)... } };
    auto & s = _services.emplace(name, std::move(service)).first->second;
    return static_cast<T &>(*s);
}

inline bool Utility::ServiceLocator::delService(const std::string & name) {
    return _services.erase(name) != 0;
}

inline bool Utility::ServiceLocator::hasService(const std::string & name) const {
    return _services.count(name) != 0;
}

template<typename T>
inline auto Utility::ServiceLocator::service(const std::string & name) -> T &
{
    static_assert(std::is_base_of<Service, T>::value,
            "T must be a descendant of Utility::Service");

#ifdef QT_NO_DEBUG
    return static_cast<T &>(*_services.at(name));
#else
    auto itr = _services.find(name);
    if (Q_UNLIKELY(itr == _services.end()))
        Q_ASSERT_X(false, __FUNCTION__,
                   qPrintable(QString("Service '%1' not found")
                              .arg(typeid(T).name())));
    return static_cast<T &>(*itr->second);
#endif
}

inline void Utility::ServiceLocator::clear() {
    _services.clear();
}
