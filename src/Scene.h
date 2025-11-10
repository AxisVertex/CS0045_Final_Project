#pragma once 

#include <SFML/Graphics.hpp>

// GameState enum
// All scenes need to know about this to signal transitions.
enum class GameState {
    MainMenu,
    Scene1_Intro,
    Scene2_TumbangPreso,
    Scene3_HabolHabulan,
    Scene4_Patintero,
    Scene5_Cutscene2,
    Scene6_SipaShowdown,
    Scene7_Resolution,
    GameOver,
    Exit
};

// Abstract Scene class
// This is the "contract" or "blueprint" for all other scenes.
class Scene {
public:
    virtual ~Scene() {} // Virtual destructor

    virtual void handleInput(sf::Event& event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual GameState getNextState() = 0;
};