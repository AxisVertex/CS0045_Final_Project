#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath> 

#define GLEW_STATIC
#include <GL/glew.h>

class Scene2 : public Scene {
public:
    // Constructor
    Scene2(sf::RenderWindow& window);

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    // Helper functions
    void setupSceneGraphics();
    void resetSlipper();
    void throwSlipper(sf::Vector2f target);
    void createCanArray(); // Helper for vertex array

    // --- Member Variables ---
    sf::RenderWindow& m_window;
    GameState m_nextState;

     
    enum class SceneState {
        Playing,
        Won,
        Lost,
        Exiting // For fade transition
    };
    SceneState m_currentState;
    // ---------------------------------

    // Assets
    sf::Font m_font;

    // Graphics
    sf::RectangleShape m_sky, m_building1, m_building2, m_treeTrunk;
    sf::ConvexShape m_road;
    sf::CircleShape m_treeLeaves;
    sf::RectangleShape m_can; // Using a simple shape for this, as it's the target
    sf::ConvexShape m_slipper;

    // UI
    sf::Text m_subtitleText;
    sf::Text m_attemptsText;
    sf::RectangleShape m_fadeRect; // For transitions

    // Game Logic
    int m_attemptsLeft;
    bool m_isThrowing;
    bool m_canHit;
    sf::Clock m_endTimer;  

    // Slipper Animation
    sf::Vector2f m_slipperStartPos;
    float m_slipperStartScale;
    sf::Vector2f m_targetPosition;
    float m_throwDuration;
    sf::Clock m_throwClock;
};