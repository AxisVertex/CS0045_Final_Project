#include "MainMenu.h"
#include <string> 

MainMenu::MainMenu(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::MainMenu) // Start in the MainMenu state
{
    std::cout << "Entering Main Menu." << std::endl;

    // Load font 
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font: arial.ttf. Please ensure it's in the correct directory." << std::endl;
        
    }

    setupGraphics(); // Initialize all shapes and text
}

void MainMenu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            // Check if "START" button was clicked
            if (m_startButtonRect.getGlobalBounds().contains(mousePos)) {
                m_nextState = GameState::Scene1_Intro; // Transition to Scene 1
            }
        }
    }
}

void MainMenu::update(sf::Time dt) {
    // nothing to put here right now
    // static animation first
}

void MainMenu::draw(sf::RenderTarget& target) {
    // Draw background elements
    target.draw(m_sky);
    target.draw(m_grass);

    // Draw bench
    target.draw(m_benchLeg1);
    target.draw(m_benchLeg2);
    target.draw(m_benchSeat);

    // Draw Alden stickman
    target.draw(m_aldenHead);
    target.draw(m_aldenBody);
    target.draw(m_aldenArm1);
    target.draw(m_aldenArm2);
    target.draw(m_aldenLeg1);
    target.draw(m_aldenLeg2);

    // Draw YayaDub stickman
    target.draw(m_yayaDubHead);
    target.draw(m_yayaDubBody);
    target.draw(m_yayaDubArm1);
    target.draw(m_yayaDubArm2);
    target.draw(m_yayaDubLeg1);
    target.draw(m_yayaDubLeg2);

    // Draw UI elements
    target.draw(m_gameTitleText);
    target.draw(m_startText);
}

GameState MainMenu::getNextState() {
    return m_nextState;
}

void MainMenu::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    // --- Background ---
    m_sky.setSize(sf::Vector2f(w, h * 0.7f));
    m_sky.setFillColor(sf::Color(135, 206, 235)); // Light Blue
    m_sky.setPosition(0, 0);

    m_grass.setSize(sf::Vector2f(w, h * 0.3f));
    m_grass.setFillColor(sf::Color(34, 139, 34)); // Forest Green
    m_grass.setPosition(0, h * 0.7f);

    // --- Bench ---
    float benchWidth = w * 0.4f;
    float benchHeight = h * 0.05f;
    float benchX = (w - benchWidth) / 2.0f;
    float benchY = h * 0.75f;

    m_benchSeat.setSize(sf::Vector2f(benchWidth, benchHeight));
    m_benchSeat.setFillColor(sf::Color(139, 69, 19)); // Brown
    m_benchSeat.setPosition(benchX, benchY);

    float legWidth = w * 0.02f;
    float legHeight = h * 0.1f;

    m_benchLeg1.setSize(sf::Vector2f(legWidth, legHeight));
    m_benchLeg1.setFillColor(sf::Color(101, 33, 0)); // Darker Brown
    m_benchLeg1.setPosition(benchX + benchWidth * 0.1f, benchY + benchHeight);

    m_benchLeg2.setSize(sf::Vector2f(legWidth, legHeight));
    m_benchLeg2.setFillColor(sf::Color(101, 33, 0)); // Darker Brown
    m_benchLeg2.setPosition(benchX + benchWidth * 0.8f, benchY + benchHeight);

    // --- Stickmen ---
    float headRadius = 20.f;
    float bodyHeight = 70.f;
    float limbLength = 40.f;
    float limbThickness = 5.f;

    // Alden (left stickman)
    sf::Vector2f aldenPos(benchX + benchWidth * 0.3f, benchY - bodyHeight - headRadius * 2);

    m_aldenHead.setRadius(headRadius);
    m_aldenHead.setFillColor(sf::Color::Blue); 
    m_aldenHead.setPosition(aldenPos);

    m_aldenBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
    m_aldenBody.setFillColor(sf::Color::Blue);
    m_aldenBody.setPosition(aldenPos.x + headRadius - limbThickness / 2.f, aldenPos.y + headRadius * 2);

    m_aldenArm1.setSize(sf::Vector2f(limbLength, limbThickness));
    m_aldenArm1.setFillColor(sf::Color::Blue); 
    m_aldenArm1.setPosition(m_aldenBody.getPosition().x, m_aldenBody.getPosition().y + bodyHeight * 0.2f);
    m_aldenArm1.setRotation(-20); // Slightly down

    m_aldenArm2.setSize(sf::Vector2f(limbLength, limbThickness));
    m_aldenArm2.setFillColor(sf::Color::Blue); 
    m_aldenArm2.setPosition(m_aldenBody.getPosition().x - (limbLength - limbThickness), m_aldenBody.getPosition().y + bodyHeight * 0.2f);
    m_aldenArm2.setRotation(20); // Slightly down and mirrored

    m_aldenLeg1.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f)); // Shorter for sitting
    m_aldenLeg1.setFillColor(sf::Color::Blue);
    m_aldenLeg1.setPosition(m_aldenBody.getPosition().x, m_aldenBody.getPosition().y + bodyHeight);

    m_aldenLeg2.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
    m_aldenLeg2.setFillColor(sf::Color::Blue); 
    m_aldenLeg2.setPosition(m_aldenBody.getPosition().x + limbThickness, m_aldenBody.getPosition().y + bodyHeight);


    // YayaDub (right stickman)
    sf::Color pink(255, 192, 203); 
    sf::Vector2f yayaDubPos(benchX + benchWidth * 0.7f - headRadius * 2, benchY - bodyHeight - headRadius * 2);

    m_yayaDubHead.setRadius(headRadius);
    m_yayaDubHead.setFillColor(pink); 
    m_yayaDubHead.setPosition(yayaDubPos);

    m_yayaDubBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
    m_yayaDubBody.setFillColor(pink); 
    m_yayaDubBody.setPosition(yayaDubPos.x + headRadius - limbThickness / 2.f, yayaDubPos.y + headRadius * 2);

    m_yayaDubArm1.setSize(sf::Vector2f(limbLength, limbThickness));
    m_yayaDubArm1.setFillColor(pink); 
    m_yayaDubArm1.setPosition(m_yayaDubBody.getPosition().x, m_yayaDubBody.getPosition().y + bodyHeight * 0.2f);
    m_yayaDubArm1.setRotation(-20);

    m_yayaDubArm2.setSize(sf::Vector2f(limbLength, limbThickness));
    m_yayaDubArm2.setFillColor(pink); 
    m_yayaDubArm2.setPosition(m_yayaDubBody.getPosition().x - (limbLength - limbThickness), m_yayaDubBody.getPosition().y + bodyHeight * 0.2f);
    m_yayaDubArm2.setRotation(20);

    m_yayaDubLeg1.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
    m_yayaDubLeg1.setFillColor(pink); 
    m_yayaDubLeg1.setPosition(m_yayaDubBody.getPosition().x, m_yayaDubBody.getPosition().y + bodyHeight);

    m_yayaDubLeg2.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
    m_yayaDubLeg2.setFillColor(pink); 
    m_yayaDubLeg2.setPosition(m_yayaDubBody.getPosition().x + limbThickness, m_yayaDubBody.getPosition().y + bodyHeight);


    // --- UI Elements ---
    m_gameTitleText.setFont(m_font);
    m_gameTitleText.setString("Outdoor Quest: The YayaDub Rescue");
    m_gameTitleText.setCharacterSize(48);
    m_gameTitleText.setFillColor(sf::Color::White);
    m_gameTitleText.setOutlineColor(sf::Color::Black);
    m_gameTitleText.setOutlineThickness(3.f);
    sf::FloatRect titleRect = m_gameTitleText.getLocalBounds();
    m_gameTitleText.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    m_gameTitleText.setPosition(w / 2.0f, h * 0.15f);

    m_startText.setFont(m_font);
    m_startText.setString("START");
    m_startText.setCharacterSize(36);
    m_startText.setFillColor(sf::Color::Yellow);
    m_startText.setOutlineColor(sf::Color::Black);
    m_startText.setOutlineThickness(2.f);
    sf::FloatRect startRect = m_startText.getLocalBounds();
    m_startText.setOrigin(startRect.left + startRect.width / 2.0f, startRect.top + startRect.height / 2.0f);
    m_startText.setPosition(w * 0.8f, h * 0.8f);

    // Invisible rectangle for "START" click detection
    m_startButtonRect.setSize(sf::Vector2f(startRect.width + 20, startRect.height + 20));
    m_startButtonRect.setOrigin(m_startButtonRect.getSize().x / 2.0f, m_startButtonRect.getSize().y / 2.0f);
    m_startButtonRect.setPosition(m_startText.getPosition());
    m_startButtonRect.setFillColor(sf::Color::Transparent); 
}