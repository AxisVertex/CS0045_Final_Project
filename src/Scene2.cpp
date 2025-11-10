#include "Scene2.h"
#include <cmath>    
#include <cstdlib>   

// We put the constructor code here
Scene2::Scene2(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene2_TumbangPreso),
    m_currentState(SceneState::Playing), // Start in playing state
    m_attemptsLeft(5),
    m_isThrowing(false),
    m_canHit(false),
    m_throwDuration(1.0f)
{
    std::cout << "Entering Scene 2: Tumbang Preso" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    // Set up fade rectangle (covers whole screen, starts transparent)
    m_fadeRect.setSize(sf::Vector2f(m_window.getSize()));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    setupSceneGraphics();
    resetSlipper();
}

void Scene2::handleInput(sf::Event& event) {
    // Only allow input if we are in the 'Playing' state
    if (m_currentState != SceneState::Playing) return;

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (!m_isThrowing && m_attemptsLeft > 0) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                sf::Vector2f target = m_window.mapPixelToCoords(mousePos);
                throwSlipper(target);
            }
        }
    }
}

void Scene2::update(sf::Time dt) {
    // Handle logic based on the internal scene state
    switch (m_currentState) {
    case SceneState::Playing:
        if (m_isThrowing) {
            sf::Time elapsed = m_throwClock.getElapsedTime();
            float t = elapsed.asSeconds() / m_throwDuration;

            if (t >= 1.0f) {
                t = 1.0f;
                m_isThrowing = false;
                
                if (m_slipper.getGlobalBounds().intersects(m_can.getGlobalBounds())) {
                    m_canHit = true;
                    m_can.setRotation(90.0f);
                    m_can.move(15.f, 5.f);
                    m_subtitleText.setString(L"TAMA! Para kay YayaDub!");
                    m_currentState = SceneState::Won; // Change state to Won
                    m_endTimer.restart(); // Start the 4-second timer
                } else {
                    m_attemptsLeft--;
                    m_subtitleText.setString(L"Sayang! Isa pa!");
                    resetSlipper();
                    
                    if (m_attemptsLeft <= 0) {
                        m_subtitleText.setString(L"Naubos na ang tsinelas!");
                        m_currentState = SceneState::Lost; // Change state to Lost
                        m_endTimer.restart(); // Start the 4-second timer
                    }
                }
            }
            
            sf::Vector2f newPos = m_slipperStartPos + (m_targetPosition - m_slipperStartPos) * t;
            m_slipper.setPosition(newPos);

            float newScale = m_slipperStartScale + (0.2f - m_slipperStartScale) * t;
            m_slipper.setScale(newScale, newScale);
            m_slipper.rotate(360.0f * dt.asSeconds());
        }
        m_attemptsText.setString("Tsinelas: " + std::to_string(m_attemptsLeft));
        break;

    case SceneState::Won:
        // Wait for 4 seconds
        if (m_endTimer.getElapsedTime().asSeconds() > 2.0f) {
            m_currentState = SceneState::Exiting; // Start fading out
            m_endTimer.restart();
        }
        break;

    case SceneState::Lost:
        // Wait for 4 seconds
        if (m_endTimer.getElapsedTime().asSeconds() > 4.0f) {
            m_currentState = SceneState::Exiting; // Start fading out
            m_endTimer.restart();
        }
        break;

    case SceneState::Exiting:
        // Fade to black over 1.5 seconds
        float fadeDuration = 1.5f;
        float fadeElapsed = m_endTimer.getElapsedTime().asSeconds();
        sf::Uint8 alpha = static_cast<sf::Uint8>(std::min(255.f, (fadeElapsed / fadeDuration) * 255.f));
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));

        if (fadeElapsed > fadeDuration) {
            // After fading, set the next game state
            if (m_canHit) {
                m_nextState = GameState::Scene3_HabolHabulan; // Go to next level
            } else {
                m_nextState = GameState::GameOver; // Go to game over
            }
        }
        break;
    }
}

void Scene2::draw(sf::RenderTarget& target) {
    target.draw(m_sky);
    target.draw(m_road);
    target.draw(m_building1);
    target.draw(m_building2);
    target.draw(m_treeTrunk);
    target.draw(m_treeLeaves);
    target.draw(m_can);
    target.draw(m_slipper);
    target.draw(m_subtitleText);
    target.draw(m_attemptsText);

    // Draw the fade rectangle on top of everything
    if (m_currentState == SceneState::Exiting) {
        target.draw(m_fadeRect);
    }
}

GameState Scene2::getNextState() {
    return m_nextState;
}

// --- Private Helper Functions ---

void Scene2::setupSceneGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    m_sky.setSize(sf::Vector2f(w, h * 0.6f));
    m_sky.setFillColor(sf::Color(135, 206, 235));
    m_road.setPointCount(4);
    m_road.setPoint(0, sf::Vector2f(w * 0.1f, h * 0.6f));
    m_road.setPoint(1, sf::Vector2f(w * 0.9f, h * 0.6f));
    m_road.setPoint(2, sf::Vector2f(w, h));
    m_road.setPoint(3, sf::Vector2f(0, h));
    m_road.setFillColor(sf::Color(128, 128, 128));
    m_building1.setSize(sf::Vector2f(w * 0.2f, h * 0.4f));
    m_building1.setPosition(w * 0.05f, h * 0.2f);
    m_building1.setFillColor(sf::Color(100, 100, 255));
    m_building2.setSize(sf::Vector2f(w * 0.2f, h * 0.35f));
    m_building2.setPosition(w * 0.25f, h * 0.25f);
    m_building2.setFillColor(sf::Color(150, 255, 150));
    m_treeTrunk.setSize(sf::Vector2f(w * 0.03f, h * 0.2f));
    m_treeTrunk.setPosition(w * 0.75f, h * 0.4f);
    m_treeTrunk.setFillColor(sf::Color(139, 69, 19));
    m_treeLeaves.setRadius(w * 0.1f);
    m_treeLeaves.setPosition(w * 0.7f, h * 0.25f);
    m_treeLeaves.setFillColor(sf::Color(34, 139, 34));
    
    // Using a simple RectangleShape for the can, as it's just a target
    m_can.setSize(sf::Vector2f(30.f, 50.f));
    m_can.setOrigin(15.f, 25.f);
    m_can.setPosition(w * 0.5f, h * 0.6f);
    m_can.setFillColor(sf::Color(211, 211, 211));
    m_can.setOutlineColor(sf::Color::Black);
    m_can.setOutlineThickness(2.f);

    m_slipper.setPointCount(4);
    m_slipper.setPoint(0, sf::Vector2f(0, 20));
    m_slipper.setPoint(1, sf::Vector2f(40, 20));
    m_slipper.setPoint(2, sf::Vector2f(35, 100));
    m_slipper.setPoint(3, sf::Vector2f(5, 100));
    m_slipper.setFillColor(sf::Color(34, 177, 76));
    m_slipper.setOutlineColor(sf::Color::Black);
    m_slipper.setOutlineThickness(2.f);
    m_slipper.setOrigin(20.f, 90.f);
    m_subtitleText.setFont(m_font);
    m_subtitleText.setString(L"Ang unang hamon! Tumbang Preso ng Bayan!");
    m_subtitleText.setCharacterSize(24);
    m_subtitleText.setFillColor(sf::Color::White);
    m_subtitleText.setOutlineColor(sf::Color::Black);
    m_subtitleText.setOutlineThickness(2.f);
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(w / 2.0f, h * 0.1f);
    m_attemptsText.setFont(m_font);
    m_attemptsText.setCharacterSize(20);
    m_attemptsText.setFillColor(sf::Color::White);
    m_attemptsText.setPosition(10.f, 10.f);
}

void Scene2::resetSlipper() {
    sf::Vector2u windowSize = m_window.getSize();
    m_slipperStartPos = sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 1.1f);
    m_slipperStartScale = 1.0f;
    m_slipper.setPosition(m_slipperStartPos);
    m_slipper.setScale(m_slipperStartScale, m_slipperStartScale);
    m_slipper.setRotation(0.f);
}

void Scene2::throwSlipper(sf::Vector2f target) {
    m_isThrowing = true;
    
    float spread = 100.f;
    float randX = (static_cast<float>(rand()) / RAND_MAX) * spread - (spread / 2.f);
    float randY = (static_cast<float>(rand()) / RAND_MAX) * spread - (spread / 2.f);
    
    m_targetPosition = target + sf::Vector2f(randX, randY);
    
    m_throwClock.restart();
}