#include "Dependancies.hpp"

extern "C" {
    extern const int secret = 0x667;

    extern const char filepath[120] = "../client/assets/dog.png";

    extern Entity monsterGenerator(Engine::EntityManager &entities, Engine::PositionSystem &positionSystem,
    Engine::VelocitySystem &velocitySystem, Engine::HitboxSystem &hitboxSystem, Engine::StatusSystem &statusSystem) {
        Entity frog = entities.create();

        positionSystem.create(frog);
        velocitySystem.create(frog);
        velocitySystem.setVelocity(frog, -40, -70);
        hitboxSystem.create(frog);
        hitboxSystem.setHitbox(frog, 70, 30, Engine::HitboxType::MONSTER);
        statusSystem.create(frog);
        statusSystem.setStatus(frog, Engine::ALIVE);
        std::cout << "Dog created bwa !" << std::endl;
        return (frog);
    }
}