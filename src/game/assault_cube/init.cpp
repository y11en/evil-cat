#include <vector>
#include <memory>
#include "init.h"
#include "service/service_interface.h"
#include "service/name_list/name_list.h"
#include "service/health_locker/health_locker.h"
#include "service/aimbot/aimbot.h"
#include "service/esp/esp.h"
#include "service/radar/radar.h"

std::vector<std::unique_ptr<ServiceInterface>> init() {

    std::vector<std::unique_ptr<ServiceInterface>> services;

    // choose your services here
    // easy to understand

    services.emplace_back(std::make_unique<NameList>());
    services.emplace_back(std::make_unique<Aimbot>());
    services.emplace_back(std::make_unique<Esp>());
    services.emplace_back(std::make_unique<Radar>());
    services.emplace_back(std::make_unique<HealthLocker>());

    return services;
}
