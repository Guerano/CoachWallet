#pragma once

namespace Utility
{
/**
 * @brief Base of all service
 */
struct Service
{
    Service() = default;
    virtual ~Service() = default;

    // Can't copy a service
    Service(Service const &) = delete;
    Service & operator=(Service const &) = delete;

    // Can't move a service
    Service(Service &&) = delete;
    Service & operator=(Service &&) = delete;
};
}

#define SERVICE(className) \
    public: static constexpr auto const serviceName = #className; private:

#define SERVICE_INSTANCE(className) \
    qApp->service<className>(className::serviceName)

#define ADD_SERVICE(className, ...) \
    qApp->addService<className>(className::serviceName, ##__VA_ARGS__)
