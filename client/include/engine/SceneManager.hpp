/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-yoan.saint-juste
** File description:
** SceneManagerSystem
*/

#ifndef SCENEMANAGERSYSTEM_HPP_
#define SCENEMANAGERSYSTEM_HPP_

#include "Scene.hpp"

namespace Engine {

    class SceneManager {
        public:
            SceneManager() = default;
            ~SceneManager() = default;

            void setScene(Engine::SCENE newScene) {_actualScene = newScene;};
            Engine::SCENE getScene() {return (_actualScene);};

        private:
            Engine::SCENE _actualScene;
    };

}

#endif /* !SCENEMANAGERSYSTEM_HPP_ */
