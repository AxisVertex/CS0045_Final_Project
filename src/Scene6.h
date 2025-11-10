#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>

class Scene6 : public Scene {
public:
    Scene6(sf::RenderWindow& window);
    ~Scene6() override = default;

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    // --- Helper Functions (Declarations removed, they are now global in .cpp) ---
    void setupGraphics(); // This one is still a member
    void spawnNote(int lane); 
    void setSubtitle(const std::wstring& text);
    void checkHit(int lane);
    void updateNotes(sf::Time dt);
    void updateAI(sf::Time dt);
    void updateUI();
    void setAldenPose(int pose); // 0=Idle, 1=A, 2=S, 3=D
    void setArjoPose(int pose);  // 0=Idle, 1=A, 2=S, 3=D

    // --- Core Game State ---
    sf::RenderWindow& m_window;

    GameState m_nextState;
    enum class GameStatus { Starting, Playing, Ended, Exiting };
    GameStatus m_status;
    enum class Turn { Alden, Arjo };
    Turn m_currentTurn;
    bool m_playerWon;
    sf::Clock m_gameTimer;    // 56 second master timer
    sf::Clock m_turnTimer;    // 7 second turn timer
    sf::Clock m_aiTimer;      // For Arjo's randomized hits
    sf::Clock m_poseTimer;    // To reset pose to idle
    sf::Clock m_startTimer;   // For "Stage 4: Sipa Showdown!" subtitle
    sf::Clock m_endTimer;     

    // --- Assets ---
    sf::Font m_font;
    sf::Text m_subtitleText;
    sf::Text m_turnText;
    sf::Text m_aldenScoreText;
    sf::Text m_arjoScoreText;
    sf::Text m_feedbackText; // "Nice!" or "Miss!"

    // --- Graphics ---
    sf::RectangleShape m_gymBg;
    sf::RectangleShape m_gymFloor;
    sf::RectangleShape m_fadeRect;
    sf::RectangleShape m_subtitleBackground; 

    // --- Poses ---
    sf::VertexArray m_aldenIdleHead, m_aldenIdleBody;
    sf::VertexArray m_aldenPoseAHead, m_aldenPoseABody;
    sf::VertexArray m_aldenPoseSHead, m_aldenPoseSBody;
    sf::VertexArray m_aldenPoseDHead, m_aldenPoseDBody;
    sf::VertexArray m_arjoIdleHead, m_arjoIdleBody;
    sf::VertexArray m_arjoPoseAHead, m_arjoPoseABody;
    sf::VertexArray m_arjoPoseSHead, m_arjoPoseSBody;
    sf::VertexArray m_arjoPoseDHead, m_arjoPoseDBody;

    // Pointers to the current active pose for drawing
    sf::VertexArray* m_currentAldenHead;
    sf::VertexArray* m_currentAldenBody;
    sf::VertexArray* m_currentArjoHead;
    sf::VertexArray* m_currentArjoBody;
    sf::Transform m_aldenTransform, m_arjoTransform;
    
    sf::VertexArray m_targetA, m_targetS, m_targetD;
    sf::Text m_labelA, m_labelS, m_labelD;
    sf::Transform m_targetATransform, m_targetSTransform, m_targetDTransform;
    
    struct Note {
        sf::VertexArray shape;
        sf::Transform transform;
        int lane; // 0=A, 1=S, 2=D
        float y_pos;
        bool active;
        bool wasHit;
    };
    std::vector<Note> m_notes;
    float m_targetY;
    float m_spawnY;
    float m_noteSpeed;
    float m_hitWindow; // Px above/below target

    // --- Beatmap ---
    struct BeatmapEntry {
        float spawnTime; // Time *within a 7-second turn*
        int lane;
    };
    // 4 separate beatmaps for Alden's 4 turns
    std::vector<std::vector<BeatmapEntry>> m_beatmaps;
    int m_beatmapIndex;
    int m_currentTurnNumber;

    // --- Health/Score ---
    int m_aldenScore;
    int m_arjoScore;
    sf::RectangleShape m_healthBarBlue;
    sf::RectangleShape m_healthBarRed;
};