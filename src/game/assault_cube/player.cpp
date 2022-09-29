#include "mem/process_memory_accessor.h"
#include "offset/player.h"
#include "player.h"

Player::Player(gameptr_t address)
        : _this(address) {
}

glm::vec3 Player::getPosition() {
    return ProcessMemoryAccessor<glm::vec3>{ADDRESS(_this, Offset::Player, feet)};
}

float Player::getHeight() {
    glm::vec3 feet = getPosition();
    glm::vec3 head = getCameraPosition();
    return head.z - feet.z;
}

glm::vec3 Player::getCameraPosition() {
    return ProcessMemoryAccessor<glm::vec3>{ADDRESS(_this, Offset::Player, head)};
}

glm::vec3 Player::getViewAngle() {
    return ProcessMemoryAccessor<glm::vec3>{ADDRESS(_this, Offset::Player, viewAngle)};
}

void Player::setViewAngle(glm::vec3 angle) {
    ProcessMemoryAccessor<glm::vec3>{ADDRESS(_this, Offset::Player, viewAngle)} = angle;
}

std::string Player::getName() {
    Offset::Name name =
            ProcessMemoryAccessor<Offset::Name>{ADDRESS(_this, Offset::Player, name)};
    *name.rbegin() = '\0';
    return name.data();
}

int Player::getTeamId() {
    return (int)ProcessMemoryAccessor<uint8_t>{ADDRESS(_this, Offset::Player, team)};
}

float Player::getHealth() {
    return (float)ProcessMemoryAccessor<int>{ADDRESS(_this, Offset::Player, health)};
}

void Player::setHealth(float health) {
    ProcessMemoryAccessor<int>{ADDRESS(_this, Offset::Player, health)} = (int)health;
}

float Player::getArmor() {
    return (float)ProcessMemoryAccessor<int>{ADDRESS(_this, Offset::Player, armor)};
}

void Player::setArmor(float armor) {
    ProcessMemoryAccessor<int>{ADDRESS(_this, Offset::Player, armor)} = (int)armor;
}

bool Player::operator==(const PlayerBasicInterface &other) const {
    return _this == dynamic_cast<const Player&>(other)._this;
}
