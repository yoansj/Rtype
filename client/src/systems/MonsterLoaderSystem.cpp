/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** LibLoaderSystem
*/

#include "MonsterLoaderSystem.hpp"

void Engine::MonsterLoaderSystem::load(std::vector<std::string> libs)
{
    for (int i = 0; i != libs.size(); i++) {
        void *lib = dlopen(libs[i].data(), RTLD_LAZY);

        if (!lib)
            throw MonsterLoaderError(dlerror());

        void *mob = dlsym(lib, "monsterGenerator");

        if (!mob)
            throw MonsterLoaderError("Couldn't load monsterGenerator in lib " + libs[0]);

        const int *secret = reinterpret_cast<int *>(dlsym(lib, "secret"));
        const char *filepath = reinterpret_cast<char *>(dlsym(lib, "filepath"));

        if (!secret || *secret != 0x667)
            throw MonsterLoaderError("Bad secret number in lib" + libs[0]);
        if (!filepath)
            throw MonsterLoaderError("Filepath not found !");

        _monstersFactories.push_back(mob);
        _monstersLib.push_back(mob);
        _monstersFilepath.push_back(filepath);
        std::cout << "Lib loaded ! babinks" << std::endl;
    }
}