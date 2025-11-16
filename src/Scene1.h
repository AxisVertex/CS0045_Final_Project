#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <vector>
#include <cmath>

#define GLEW_STATIC
#include <GL/glew.h>

class Scene1 : public Scene {
public:
    Scene1(sf::RenderWindow& window);
    ~Scene1() override = default;

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    void setupGraphics();
    void setSubtitle(const std::wstring& text);
    void updateCutscene(sf::Time dt);

    // --- ADDED FOR AUDIO ---
    std::vector<sf::SoundBuffer> m_voiceBuffers;
    sf::Sound m_voiceSound;
    // -----------------------

    enum class CutscenePart {
        FadeIn,
        Peaceful,
        Dialogue_Yaya,
        Dialogue_Alden,
        YayaDisappears,
        ArjoAppears,
        Dialogue_Alden_Arjo,
        Dialogue_Arjo_Challenge,
        Dialogue_Yaya_Help,
        Dialogue_Arjo_Games,
        Dialogue_Alden_Ano,
        Dialogue_Arjo_TumbangPreso,
        ArjoLeaves,
        AldenDetermined,
        FadeOut
    };

    CutscenePart m_currentPart;
    sf::Clock m_partClock;
    GameState m_nextState;
    sf::RenderWindow& m_window;

    sf::Font m_font;
    sf::Text m_subtitleText;
    sf::RectangleShape m_subtitleBackground;
    sf::RectangleShape m_fadeRect;

    // --- Graphics Variables ---
    sf::RectangleShape m_parkSky, m_parkGrass, m_parkBenchSeat, m_parkBenchLeg1, m_parkBenchLeg2;
    sf::CircleShape m_aldenHead, m_yayaDubHead, m_arjoHead, m_yayaDubKidnappedHead, m_aldenHeadLookingUp, m_aldenCloseupHead;
    sf::RectangleShape m_aldenBody, m_aldenArm1, m_aldenArm2, m_aldenLeg1, m_aldenLeg2;
    sf::RectangleShape m_yayaDubBody, m_yayaDubArm1, m_yayaDubArm2, m_yayaDubLeg1, m_yayaDubLeg2;
    sf::Text m_exclamationMark;
    sf::RectangleShape m_skyBg;
    sf::RectangleShape m_arjoBody, m_arjoArm1, m_arjoArm2, m_arjoLeg1, m_arjoLeg2;
    sf::RectangleShape m_yayaDubKidnappedBody, m_yayaDubKidnappedArm1, m_yayaDubKidnappedArm2, m_yayaDubKidnappedLeg1, m_yayaDubKidnappedLeg2;
    sf::RectangleShape m_closeupBg, m_aldenCloseupBody, m_letterboxTop, m_letterboxBottom;
};