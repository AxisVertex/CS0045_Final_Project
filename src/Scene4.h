#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath> 

#define GLEW_STATIC
#include <GL/glew.h>

// Define constants for the top-down circles
const float ALDEN_RADIUS = 20.f;
const float BLOCKER_RADIUS = 25.f;

class Scene4 : public Scene {
public:
    Scene4(sf::RenderWindow& window);
    ~Scene4() override = default;

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    void setupTopDownCircle(sf::VertexArray& shape, float radius, sf::Color color);
    void setupGraphics();
    void checkCollisions();

    sf::RenderWindow& m_window;
    GameState m_nextState;

    enum class GameStatus { Playing, Won, Lost, Exiting };
    GameStatus m_status;
    bool m_playerWon;
    sf::Clock m_gameTimer;
    sf::Clock m_endTimer;
    float m_gameDuration;

    // Assets
    sf::Font m_font;
    sf::Text m_subtitleText;
    sf::Text m_timerText;
    sf::RectangleShape m_fadeRect;

    // --- Court Graphics ---
    sf::RectangleShape m_background;
    std::vector<sf::RectangleShape> m_lines;
    sf::VertexArray m_finishLine;
    float m_lineSpacing;
    int m_linesToCross;
    float m_courtWidth;
    float m_courtX_Start;
    float m_courtX_End;
 

    // --- Player Logic ---
    sf::VertexArray m_aldenShape;  
    float m_aldenFixedX;     
    float m_aldenFixedY;     
    float m_aldenDashSpeed;
    int m_currentLine;       
    bool m_isDashing;

    // --- Scrolling Camera Logic ---
    float m_lineScrollOffset;   
    float m_targetScrollOffset; 

    // --- Blocker Logic ---
    struct Blocker {
        sf::VertexArray shape;  
        sf::Transform transform; 
        float speed;
        int direction;
        float minX, maxX;  
        int lineIndex; 
    };
    std::vector<Blocker> m_blockers;
};