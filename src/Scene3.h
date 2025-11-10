#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath> // For M_PI

// Define GLEW_STATIC again
#define GLEW_STATIC
#include <GL/glew.h>

class Scene3 : public Scene {
public:
    Scene3(sf::RenderWindow& window);
    ~Scene3() override = default;

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    void setupGraphics();
    void setupStickman(sf::VertexArray& head, sf::VertexArray& body, sf::Color color);
    void animateStickman(sf::VertexArray& body, float time);

    sf::RenderWindow& m_window;
    GameState m_nextState;

    enum class GameStatus { Playing, Won, Lost, Exiting };
    GameStatus m_status;
    sf::Clock m_endTimer;
    sf::RectangleShape m_fadeRect;

    // Assets
    sf::Font m_font;
    sf::Text m_subtitleText;
    sf::Text m_boostText;
    sf::Text m_timerText;  

    // Graphics
    sf::RectangleShape m_sky;
    sf::RectangleShape m_road;
    std::vector<sf::RectangleShape> m_buildings;

    // --- Vertex Array Stickmen ---
    sf::VertexArray m_aldenHead, m_aldenBody;
    sf::VertexArray m_tayaHead, m_tayaBody;

    // --- Transforms ---
    sf::Transform m_aldenTransform;
    sf::Transform m_tayaTransform;

    // Game Logic
    bool m_playerWon; 
    float m_aldenBaseSpeed;  
    float m_tayaBaseSpeed;
    
    float m_distanceToTaya;
    float m_catchDistance;     
     

    // --- Timer and Boost Mechanics ---
    sf::Clock m_gameTimer;
    float m_gameDuration;
    float m_boostLevel;
    float m_boostDecayRate;
    float m_baseBoostPerTap;  
    float m_maxBoostLevel; 
    float m_tayaMinScreenX; 

    sf::Clock m_animationTimer;
};