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

    /**
     * @brief Manage all the scenes.
     * 
     */
    class SceneManager {
        public:
            /**
             * @brief Construct a new Scene Manager object
             * 
             */
            SceneManager() {_actualScene = Engine::SCENE::TITLE_SCREEN;};
            ~SceneManager() = default;

            /**
             * @brief Set the Scene
             * 
             * @param Engine::SCENE newScene
             */
            void setScene(Engine::SCENE newScene) {_actualScene = newScene;};

            /**
             * @brief Get the Scene object
             * 
             * @return Engine::SCENE 
             */
            Engine::SCENE getScene() {return (_actualScene);};

        private:
            Engine::SCENE _actualScene;
    };

}

#endif /* !SCENEMANAGERSYSTEM_HPP_ */
