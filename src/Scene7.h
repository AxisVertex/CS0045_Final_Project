#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Added for sound
#include <iostream>
#include <vector>
#include <cmath>
#include <array> // Added for sound buffers

#define GLEW_STATIC
#include <GL/glew.h>

// --- Helper Functions (defined in Scene7.cpp) ---
void addThickLine_S7(sf::VertexArray& arr, sf::Vector2f p1, sf::Vector2f p2, float thickness, sf::Color color);
void setupLargeCircle_S7(sf::VertexArray& shape, sf::Vector2f center, float radius, sf::Color color);
void setupStickman_S7(sf::VertexArray& head, sf::VertexArray& body, sf::Color color, float headRadius, float bodyHeight, float limbThickness);
// -------------------------------------------------


class Scene7 : public Scene {
public:
    Scene7(sf::RenderWindow& window);
    ~Scene7() override = default;

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    void setupGraphics();
    void setSubtitle(const std::wstring& text, int charSize = 32);
    void updateCutscene(sf::Time dt);

    // Enum for cutscene parts
    enum class CutscenePart {
        FadeIn,
        WalkToBench,
        Dialogue1_Yaya,
        Dialogue2_Alden,
        Silence,
        Dialogue3_Yaya,
        Dialogue4_Alden,
        ComedyEnding_Kid,
        ComedyEnding_Alden,
        FinalZoomOut,
        FadeOut_FinalQuote,
        CreditsRoll
    };

    CutscenePart m_currentPart;
    sf::Clock m_partClock;
    GameState m_nextState;
    sf::RenderWindow& m_window;

    // Assets
    sf::Font m_font;
    sf::Text m_subtitleText;
    sf::RectangleShape m_subtitleBackground;
    sf::RectangleShape m_fadeRect;
    sf::Text m_creditsText; // For scrolling credits

    // --- Sound Assets ---
    std::array<sf::SoundBuffer, 7> m_soundBuffers;
    sf::Sound m_voiceLine;

    // --- Graphics ---
    sf::RectangleShape m_sky;
    sf::RectangleShape m_grass;
    sf::VertexArray m_benchArray;
    sf::Transform m_benchTransform;

    sf::VertexArray m_aldenHead, m_aldenBody;
    sf::VertexArray m_yayaDubHead, m_yayaDubBody;
    sf::Transform m_aldenTransform, m_yayaDubTransform;
    

};