#include "Scene3.h"
#include <sstream> 
#include <iomanip>

// A helper for building the circle heads
const float M_PI_S3 = 3.1415926535f;

Scene3::Scene3(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene3_HabolHabulan),
    m_status(GameStatus::Playing),
    m_playerWon(false), 
    m_aldenBaseSpeed(150.f),   // Alden's normal speed (slower)
    m_tayaBaseSpeed(350.f),    // Taya is MUCH FASTER
    m_distanceToTaya(300.f),   // Alden starts 300px ahead
    m_catchDistance(40.f),     // "Hitbox" (Head radius 20 + 20)
    m_gameDuration(30.f),      // 30 second timer
    m_boostLevel(0.f),
    m_boostDecayRate(1.0f),    // Boost level drops by 1.0 per second
    m_maxBoostLevel(2.0f),       // Max boost level
    m_baseBoostPerTap(0.6f),   // Boost added when level is 0
    m_tayaMinScreenX(10.f)       // Taya is clamped 10px from left
{
    std::cout << "Entering Scene 3: Habol-Habulan" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    setupGraphics();
    setupStickman(m_aldenHead, m_aldenBody, sf::Color::Blue);
    setupStickman(m_tayaHead, m_tayaBody, sf::Color::Green);

    m_gameTimer.restart(); // Start the game timer
}

void Scene3::handleInput(sf::Event& event) {
    if (m_status != GameStatus::Playing) return;

    // Press SPACE to boost
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            // --- Balanced Boost Logic ---
            // Tapping adds less boost as your boost level gets higher
            float boostToAdd = m_baseBoostPerTap * (1.0f - (m_boostLevel / m_maxBoostLevel));
            boostToAdd = std::max(boostToAdd, 0.05f); // Always add at least a little
            
            // --- Random Multiplier per tap ---
            float randomMultiplier = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 0.5f;
            boostToAdd *= randomMultiplier;
            // --------------------------------------

            m_boostLevel += boostToAdd;
            m_boostLevel = std::min(m_boostLevel, m_maxBoostLevel); // Cap boost
        }
    }
}

void Scene3::update(sf::Time dt) {
    float elapsed = dt.asSeconds();

    if (m_status == GameStatus::Playing) {
        // --- Handle Timer ---
        float remainingTime = m_gameDuration - m_gameTimer.getElapsedTime().asSeconds();
        
        // Format time string
        std::stringstream ss;
        ss << "TIME: " << std::fixed << std::setprecision(1) << remainingTime;
        m_timerText.setString(ss.str());

        if (remainingTime <= 0.f) {
            m_timerText.setString("TIME: 0.0");
            m_status = GameStatus::Won;
            m_playerWon = true; // <-- ADDED: Remember the win
            m_subtitleText.setString(L"Nakawala si Alden! Sunod na hamon!");
            m_endTimer.restart();
            return; // Exit update loop
        }

        // --- Handle Boosting ---
        // Alden's speed is his base speed + a bonus from the boost level
        // Max speed: 150 + (2.0 * 150) = 450 (Tweaked multiplier)
        float m_aldenSpeed = m_aldenBaseSpeed + (m_boostLevel * 116.f);
        
        // Decay the boost level over time
        m_boostLevel -= m_boostDecayRate * elapsed;
        m_boostLevel = std::max(m_boostLevel, 0.f); // Don't go below 0

        // Update boost text
        if (m_boostLevel > 0.5f) {
            m_boostText.setString("TAP! TAP! TAP!");
        } else {
            m_boostText.setString("Tap SPACE to run faster!");
        }


        // --- Taya AI ---
        // Taya's speed is constant. Alden must tap to be faster.
        m_distanceToTaya += (m_aldenSpeed - m_tayaBaseSpeed) * elapsed;

        // --- NEW: Clamp Taya's position ---
        // Stop the Taya from going off the left edge of the screen
        float w = static_cast<float>(m_window.getSize().x);
        float tayaScreenX = (w * 0.6f) - m_distanceToTaya;
        if (tayaScreenX < m_tayaMinScreenX) {
            m_distanceToTaya = (w * 0.6f) - m_tayaMinScreenX;
        }
        // ---------------------------------

        // --- Update Graphics ---
        // Animate stickmen
        float animTime = m_animationTimer.getElapsedTime().asSeconds();
        animateStickman(m_aldenBody, animTime * (m_aldenSpeed / 100.f));
        animateStickman(m_tayaBody, animTime * (m_tayaBaseSpeed / 100.f)); // Taya animates at his constant speed

        // Move background buildings (parallax)
        for (auto& building : m_buildings) {
            building.move(-m_aldenSpeed * 0.5f * elapsed, 0);
            // If building moves off-screen left, wrap it to the right
            if (building.getPosition().x + building.getSize().x < 0) {
                building.setPosition(m_window.getSize().x + 50.f, building.getPosition().y);
            }
        }
        
        // Set stickman positions on screen
        float h = static_cast<float>(m_window.getSize().y);
        m_aldenTransform = sf::Transform().translate(w * 0.6f, h * 0.8f);
        m_tayaTransform = sf::Transform().translate(w * 0.6f - m_distanceToTaya, h * 0.8f);

        // --- Check Win/Loss Conditions ---
        // Win condition is now timer-based
        
        // Loss condition
        if (m_distanceToTaya <= m_catchDistance) { 
            m_status = GameStatus::Lost;
            m_playerWon = false; 
            m_subtitleText.setString(L"HULI KA! Lagot!");
            m_endTimer.restart();
        }

    } else if (m_status == GameStatus::Won || m_status == GameStatus::Lost) {
        // Wait for 4 seconds
        if (m_endTimer.getElapsedTime().asSeconds() > 2.0f) {
            m_status = GameStatus::Exiting;
            m_endTimer.restart();
        }
    } else if (m_status == GameStatus::Exiting) {
        // Fade to black
        float fadeDuration = 1.5f;
        float fadeElapsed = m_endTimer.getElapsedTime().asSeconds();
        sf::Uint8 alpha = static_cast<sf::Uint8>(std::min(255.f, (fadeElapsed / fadeDuration) * 255.f));
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));

        if (fadeElapsed > fadeDuration) {
            if (m_playerWon) { 
                m_nextState = GameState::Scene4_Patintero; // Go to next level
            } else {
                m_nextState = GameState::GameOver; // Go to game over
            }
        }
    }
}

void Scene3::draw(sf::RenderTarget& target) {
    target.draw(m_sky);
    target.draw(m_road);
    for (const auto& building : m_buildings) {
        target.draw(building);
    }

    // Draw stickmen using their transforms
    target.draw(m_tayaHead, sf::RenderStates(m_tayaTransform));
    target.draw(m_tayaBody, sf::RenderStates(m_tayaTransform));
    target.draw(m_aldenHead, sf::RenderStates(m_aldenTransform));
    target.draw(m_aldenBody, sf::RenderStates(m_aldenTransform));

    // Draw UI
    target.draw(m_subtitleText);
    target.draw(m_boostText);
    target.draw(m_timerText);

    if (m_status == GameStatus::Exiting) {
        target.draw(m_fadeRect);
    }
}

GameState Scene3::getNextState() {
    return m_nextState;
}

void Scene3::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    m_sky.setSize(sf::Vector2f(w, h * 0.7f));
    m_sky.setFillColor(sf::Color(135, 206, 235));
    m_sky.setPosition(0, 0);

    m_road.setSize(sf::Vector2f(w, h * 0.3f));
    m_road.setFillColor(sf::Color(105, 105, 105)); // Dark grey road
    m_road.setPosition(0, h * 0.7f);

    // Create background buildings
    sf::Color buildingColors[] = { sf::Color(220, 100, 100), sf::Color(100, 100, 220), sf::Color(100, 220, 100) };
    for (int i = 0; i < 5; ++i) {
        sf::RectangleShape building;
        float bWidth = 100.f + (rand() % 150);
        float bHeight = 200.f + (rand() % 200);
        building.setSize(sf::Vector2f(bWidth, bHeight));
        building.setFillColor(buildingColors[i % 3]);
        building.setPosition(i * (w / 4.f), h * 0.7f - bHeight);
        m_buildings.push_back(building);
    }

    // Setup UI
    m_subtitleText.setFont(m_font);
    m_subtitleText.setString(L"Takbo Alden! Baka maabutan ka ng taya!");
    m_subtitleText.setCharacterSize(24);
    m_subtitleText.setFillColor(sf::Color::White);
    m_subtitleText.setOutlineColor(sf::Color::Black);
    m_subtitleText.setOutlineThickness(2.f);
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(w / 2.0f, h * 0.1f);

    m_boostText.setFont(m_font);
    m_boostText.setString("Tap SPACE to run faster!");
    m_boostText.setCharacterSize(20);
    m_boostText.setFillColor(sf::Color::Yellow);
    textRect = m_boostText.getLocalBounds();
    m_boostText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_boostText.setPosition(w / 2.0f, h * 0.2f);

    // Setup Timer Text
    m_timerText.setFont(m_font);
    m_timerText.setString("TIME: 30.0");
    m_timerText.setCharacterSize(28);
    m_timerText.setFillColor(sf::Color::White);
    m_timerText.setOutlineColor(sf::Color::Black);
    m_timerText.setOutlineThickness(2.f);
    m_timerText.setPosition(10.f, 10.f); // Top-left corner

    // Setup fade rect
    m_fadeRect.setSize(sf::Vector2f(w, h));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}

void Scene3::setupStickman(sf::VertexArray& head, sf::VertexArray& body, sf::Color color) {
    float headRadius = 20.f;
    float bodyHeight = 70.f;

    // Head (TriangleFan)
    head.setPrimitiveType(sf::TriangleFan);
    head.append(sf::Vertex(sf::Vector2f(0.f, -bodyHeight), color)); // Center point
    for (int i = 0; i <= 20; ++i) {
        float angle = (i / 20.f) * 2.f * M_PI_S3;
        sf::Vector2f point(headRadius * cos(angle), headRadius * sin(angle) - bodyHeight);
        head.append(sf::Vertex(point, color));
    }

    body.setPrimitiveType(sf::Lines);
    body.resize(10); 

    // Body
    body[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), color);           // Body bottom
    body[1] = sf::Vertex(sf::Vector2f(0.f, -bodyHeight), color);  // Body top
    // Arm 1 (Back)
    body[2] = sf::Vertex(sf::Vector2f(0.f, -bodyHeight * 0.8f), color);
    body[3] = sf::Vertex(sf::Vector2f(0.f, 0.f), color);
    // Arm 2 (Front)
    body[4] = sf::Vertex(sf::Vector2f(0.f, -bodyHeight * 0.8f), color);
    body[5] = sf::Vertex(sf::Vector2f(0.f, 0.f), color);
    // Leg 1 (Back)
    body[6] = sf::Vertex(sf::Vector2f(0.f, 0.f), color);
    body[7] = sf::Vertex(sf::Vector2f(0.f, 0.f), color); 
    // Leg 2 (Front)
    body[8] = sf::Vertex(sf::Vector2f(0.f, 0.f), color);
    body[9] = sf::Vertex(sf::Vector2f(0.f, 0.f), color); 
}

void Scene3::animateStickman(sf::VertexArray& body, float time) {
    float limbLength = 35.f;
    float bodyHeight = 70.f;

    // Use sin/cos waves for running animation
    float angle = sin(time * 8.f) * 0.8f; 

    // Arm 1 (Back) - Opposite of Leg 1
    float arm1_angle = -angle + M_PI_S3;
    // --- Biased Y-swing for arms ---
    // (cos(angle) + 1) * 0.5 maps -1..1 -> 0..1
    // This makes the arm swing from the socket (0) downwards (+limbLength)
    float arm1_y_swing = limbLength * (cos(arm1_angle) + 1.f) * 0.5f;
    body[3].position = sf::Vector2f(limbLength * sin(arm1_angle), -bodyHeight * 0.8f + arm1_y_swing);

    // Arm 2 (Front) - Opposite of Leg 2
    float arm2_angle = angle + M_PI_S3;
    float arm2_y_swing = limbLength * (cos(arm2_angle) + 1.f) * 0.5f; // Biased downwards
    body[5].position = sf::Vector2f(limbLength * sin(arm2_angle), -bodyHeight * 0.8f + arm2_y_swing);
    // ------------------------------------

    // Leg 1 (Back)
    body[7].position = sf::Vector2f(limbLength * sin(angle), limbLength * cos(angle));
    // Leg 2 (Front)
    body[9].position = sf::Vector2f(limbLength * sin(-angle), limbLength * cos(-angle));
}