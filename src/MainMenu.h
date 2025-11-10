#pragma once

#include "Scene.h"      // Base Scene class
#include <SFML/Graphics.hpp>
#include <iostream>     // For console output

#define GLEW_STATIC
#include <GL/glew.h>

class MainMenu : public Scene {
public:
    // Constructor
    MainMenu(sf::RenderWindow& window);
    ~MainMenu() override = default; // Use default destructor for simple scenes

    // Implementations of the pure virtual functions from Scene
    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    // Helper function to set up visual elements
    void setupGraphics();

    // --- Member Variables ---
    sf::RenderWindow& m_window;
    GameState m_nextState; // To signal when to switch to Scene1

    // Assets
    sf::Font m_font;

    // Background/Environment (Placeholder shapes for now)
    sf::RectangleShape m_sky;
    sf::RectangleShape m_grass;
    sf::RectangleShape m_benchSeat;
    sf::RectangleShape m_benchLeg1;
    sf::RectangleShape m_benchLeg2;

    // Stickman Alden
    sf::CircleShape m_aldenHead;
    sf::RectangleShape m_aldenBody;
    sf::RectangleShape m_aldenArm1;
    sf::RectangleShape m_aldenArm2;
    sf::RectangleShape m_aldenLeg1;
    sf::RectangleShape m_aldenLeg2;

    // Stickman YayaDub
    sf::CircleShape m_yayaDubHead;
    sf::RectangleShape m_yayaDubBody;
    sf::RectangleShape m_yayaDubArm1;
    sf::RectangleShape m_yayaDubArm2;
    sf::RectangleShape m_yayaDubLeg1;
    sf::RectangleShape m_yayaDubLeg2;

    // UI Elements
    sf::Text m_gameTitleText;
    sf::Text m_startText;
    sf::RectangleShape m_startButtonRect; // Invisible rectangle for "START" click detection
};