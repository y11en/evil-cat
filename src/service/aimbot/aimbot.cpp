#include <vector>
#include <functional>
#include <optional>
#include <glm/glm.hpp>
#include <windows.h>
#include "game.h"
#include "game/interface/player_basic_interface.h"
#include "aimbot_helper.h"
#include "aimbot.h"

namespace Settings::Aimbot {
    bool on = true;
    float maxAngle = glm::radians(10.f);
    Strategy strategy = Strategy::autoFollowSmooth;
}

// TODO: add bone aimbot and traceline collision detection aimbot policy

Aimbot &Aimbot::getInstance() {
    static Aimbot instance;
    return instance;
}

void Aimbot::callback() {

    if (!Settings::Aimbot::on) {
        return;
    }

    // get a strategy
    AimbotHelper::Strategy strategy;
    switch (Settings::Aimbot::strategy) {
        case Settings::Aimbot::Strategy::rightButtonPrecise:
            strategy = AimbotHelper::rightButtonPrecise;
            break;
        case Settings::Aimbot::Strategy::rightButtonSmooth:
            strategy = AimbotHelper::rightButtonSmooth;
            break;
        case Settings::Aimbot::Strategy::autoFollowPrecise:
            strategy = AimbotHelper::autoFollowPrecise;
            break;
        case Settings::Aimbot::Strategy::autoFollowSmooth:
            strategy = AimbotHelper::autoFollowSmooth;
            break;
    }

    // if not triggered, clear target
    if (!strategy.trigger()) {
        aimbotTarget = std::nullopt;
        return;
    }

    std::shared_ptr<PlayerBasicInterface> localPlayer =
            Game::getInstance().getLocalPlayer();

    std::vector<std::shared_ptr<PlayerBasicInterface>> players =
            Game::getInstance().getPlayers();

    if (players.empty()) {
        return;
    }

    // if there's no aimbot target, find one and aim to it
    std::optional<std::shared_ptr<PlayerBasicInterface>> enemy;
    if (aimbotTarget && (*aimbotTarget)->getHealth() > 0) {
        enemy = aimbotTarget;
    } else {
        enemy = strategy.targetPicker(localPlayer, players);
        aimbotTarget = enemy;
    }

    // aim to it
    if (enemy) {
        strategy.aimer(localPlayer, *enemy);
    }
}
