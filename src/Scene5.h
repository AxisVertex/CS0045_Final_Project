#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <vector>
#include <cmath>
#include <array> 

#define GLEW_STATIC
#include <GL/glew.h>

class Scene5 : public Scene {
public:
    Scene5(sf::RenderWindow& window);
    ~Scene5() override = default;

    void handleInput(sf::Event& event) override;
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target) override;
    GameState getNextState() override;

private:
    void setupGraphics();
    void setSubtitle(const std::wstring& text);
    void updateCutscene(sf::Time dt);
    
    // Helpers for building Vertex Arrays (defined in .cpp)
    void setupLargeCircle(sf::VertexArray& shape, sf::Vector2f center, float radius, sf::Color color);
    void addThickLine(sf::VertexArray& arr, sf::Vector2f p1, sf::Vector2f p2, float thickness, sf::Color color);
    void setupCircle(sf::VertexArray& shape, float radius, sf::Color color);


    // Enum for cutscene parts based on your storyboard
    enum class CutscenePart {
        FadeIn,
        AldenCollapse,      
        ClapClapClap,       
        ArjoWalksIn,        
        AldenStands,        
        ArjoCloseUp,        
        ArjoMoves,          
        RevealYaya,         
        YayaZoomIn,         
        AldenDetermined,    
        ArjoBlocks,         
        ArjoToss,           
        SipaTossAnim,       
        AldenCatch,         
        AldenLooksAtSipa,   
        ArjoFinalChallenge, 
        AldenAccepts,       
        FaceOff,            
        FadeOut
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

    // --- Sound Assets  ---
    std::array<sf::SoundBuffer, 11> m_soundBuffers;
    sf::Sound m_voiceLine;

    // --- Graphics ---
    // Backgrounds
    sf::RectangleShape m_courtBg; // Faded patintero court
    sf::RectangleShape m_gymBg;   // Brown gym wall
    sf::RectangleShape m_gymFloor;
    sf::RectangleShape m_greyFloor;

    // Letterbox bars
    sf::RectangleShape m_letterboxTop;
    sf::RectangleShape m_letterboxBottom;
    
    // Sipa (for animation)
    sf::VertexArray m_sipaShape;
    sf::Transform m_sipaTransform;
    sf::Vector2f m_sipaStartPos, m_sipaEndPos;
    float m_sipaTossDuration;


    sf::Transform m_arjoMoveTransform;

    // (Alden Collapse)
    sf::VertexArray m_pic1_aldenHead;
    sf::VertexArray m_pic1_aldenLimbs;

    // (Clapping)
    sf::VertexArray m_pic2_arjoHead;
    sf::VertexArray m_pic2_arjoBody;
    sf::Text m_clapText1, m_clapText2, m_clapText3;

    // (Arjo Walks in)
    sf::VertexArray m_pic3_arjoHead;
    sf::VertexArray m_pic3_arjoBody;

    // (Alden Stands)
    sf::VertexArray m_pic4_aldenHead;
    sf::VertexArray m_pic4_aldenBody;

    // (Arjo Grinning / Reveal Yaya)
    sf::VertexArray m_pic5_arjoHead; 
    sf::VertexArray m_pic5_arjoBody;
    sf::VertexArray m_pic6_yayaHead; 
    sf::VertexArray m_pic6_yayaBody;
    sf::VertexArray m_pic6_chair;
    sf::VertexArray m_pic6_ropes;

    // (Yaya ZoomIn)
    sf::VertexArray m_pic7_yayaHead; 
    sf::VertexArray m_pic7_yayaBody;
    sf::VertexArray m_pic7_chair;
    sf::VertexArray m_pic7_ropes;

    // (Alden Determined)
    sf::VertexArray m_pic8_aldenHead;
    sf::VertexArray m_pic8_aldenBody;

    // (Arjo Blocks)
    sf::VertexArray m_pic9_arjoHead;
    sf::VertexArray m_pic9_arjoBody;

    // (Arjo Toss)
    sf::VertexArray m_pic10_arjoHead;
    sf::VertexArray m_pic10_arjoBody;

    // (Alden Catch)
    sf::VertexArray m_pic12_aldenHead; 
    sf::VertexArray m_pic12_aldenBody;
    sf::VertexArray m_pic12_sipa; 

    // (Alden Looks at Sipa)
    sf::VertexArray m_pic13_aldenArm; 
    sf::VertexArray m_pic13_sipa;

    // (Arjo Challenge)
    sf::VertexArray m_pic14_arjoHead;
    sf::VertexArray m_pic14_arjoBody; 

    // (Alden Accepts)
    sf::VertexArray m_pic15_aldenHead; 
    sf::VertexArray m_pic15_aldenBody; 

    // (Face Off)
    sf::VertexArray m_pic16_aldenHead; 
    sf::VertexArray m_pic16_aldenBody;
    sf::VertexArray m_pic16_aldenSipa;
    sf::VertexArray m_pic16_arjoHead; 
    sf::VertexArray m_pic16_arjoBody;
};