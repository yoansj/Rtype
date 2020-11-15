
#include "Dependancies.hpp"

extern "C" {
    extern const int secret = 0x667;

    extern Entity monsterGenerator(Engine::EntityManager &entities, Engine::SystemManager &systems) {
        Entity frog = entities.create();

        systems.positionSystem.create(frog);
        systems.spriteSystem.create(frog);
        systems.spriteSystem.initSprite(frog, "../client/assets/monster.png", false);
        systems.velocitySystem.create(frog);
        systems.velocitySystem.setVelocity(frog, -10, -10);
        systems.hitboxSystem.create(frog);
        systems.hitboxSystem.setHitbox(frog, 70, 30, Engine::HitboxType::MONSTER);
        systems.statusSystem.create(frog);
        //systems.hitboxSystem;create(frog);
        std::cout << "Frog created bwa !" << std::endl;
        return (frog);
    }
}