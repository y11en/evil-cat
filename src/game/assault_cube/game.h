#ifndef EVIL_CAT_GAME_ASSAULT_CUBE_GAME_H
#define EVIL_CAT_GAME_ASSAULT_CUBE_GAME_H

#include <vector>
#include <memory>
#include "singleton.h"
#include "player.h"

class Game : public Singleton<Game> {
public:
    std::shared_ptr<Player> getLocalPlayer();

    std::vector<std::shared_ptr<Player>> getPlayers();

    glm::mat4 getVPMatrix();

    glm::vec2 getWindowSize();

    glm::vec3 viewAngleToOrientation(glm::vec3 viewAngle);

    glm::vec3 orientationToViewAngle(glm::vec3 orientation);
};

#endif //EVIL_CAT_GAME_ASSAULT_CUBE_GAME_H
