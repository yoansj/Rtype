
#include "Dependancies.hpp"

extern "C" {
    extern const int secret = 0x667;

    Entity monsterGenerator(Engine::EntityManager &entities, Engine::SystemManager &systems) {
        Entity frog = entities.create();

        systems.positionSystem.create(frog);
        //systems.spriteSystem.create(frog);
        systems.velocitySystem.create(frog);
        std::cout << "Frog created bwa !" << std::endl;
        return (frog);
    }
}