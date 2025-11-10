#include "Scene4.h"
#include <sstream> 
#include <iomanip> 
#include <string>  

// A helper for building the circle heads
const float M_PI_S4 = 3.1415926535f;

Scene4::Scene4(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene4_Patintero),
    m_status(GameStatus::Playing),
    m_playerWon(false),
    m_gameDuration(60.f),
    m_aldenDashSpeed(2500.f),
    m_lineSpacing(250.f),
    m_linesToCross(9),    
    m_currentLine(0),
    m_isDashing(false),
    m_lineScrollOffset(0.f),
    m_targetScrollOffset(0.f),
    m_aldenFixedX(0.f),
    m_aldenFixedY(0.f),
    m_courtWidth(0.f),
    m_courtX_Start(0.f),
    m_courtX_End(0.f)
{
    std::cout << "Entering Scene 4: Patintero (Scrolling)" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    setupGraphics();
    setupTopDownCircle(m_aldenShape, ALDEN_RADIUS, sf::Color::Blue);

    // Set up blockers
    sf::Color blockerColors[] = {
        sf::Color::Yellow, sf::Color::Cyan, sf::Color(0, 255, 128),
        sf::Color::Magenta, sf::Color::Red, sf::Color(255, 165, 0),
        sf::Color(200, 200, 200), sf::Color(255, 105, 180) // White and Hot Pink
    };
    // ------------------------------------------

    float baseSpeed = 650.f; // <-- Blockers speed

    // This loop now runs from i = 0 to 7 (for m_linesToCross - 1 = 8)
    for (int i = 0; i < (m_linesToCross - 1); ++i) { // 8 blockers
        Blocker blocker;
        setupTopDownCircle(blocker.shape, BLOCKER_RADIUS, blockerColors[i]);

        blocker.speed = baseSpeed + (i * 150.f); // Speed increases per line

        blocker.direction = (i % 2 == 0) ? 1 : -1;

        blocker.minX = m_courtX_Start + BLOCKER_RADIUS;
        blocker.maxX = m_courtX_End - BLOCKER_RADIUS;

        blocker.lineIndex = i + 1; 

        // Position blocker on its line
        float yPos = m_lines[i + 1].getPosition().y;
        float xPos = (float)(rand() % (int)(blocker.maxX - blocker.minX)) + blocker.minX;
        blocker.transform.translate(xPos, yPos);

        m_blockers.push_back(blocker);
    }
}

void Scene4::handleInput(sf::Event& event) {
    if (m_status != GameStatus::Playing) return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            if (!m_isDashing && m_currentLine < m_linesToCross) {
                m_isDashing = true;
                m_currentLine++;

                m_targetScrollOffset = m_lineSpacing * m_currentLine;
            }
        }
    }
}

void Scene4::update(sf::Time dt) {
    float elapsed = dt.asSeconds();

    if (m_status == GameStatus::Playing) {
        // --- Update Timer ---
        float remainingTime = m_gameDuration - m_gameTimer.getElapsedTime().asSeconds();
        if (remainingTime <= 0.f) {
            remainingTime = 0.f;
            m_status = GameStatus::Lost;
            m_playerWon = false;
            m_subtitleText.setString(L"Oras na! Natalo ka!");
            m_endTimer.restart();
        }
        std::stringstream ss;
        ss << "TIME: " << std::fixed << std::setprecision(1) << remainingTime;
        m_timerText.setString(ss.str());

        if (m_currentLine < m_linesToCross) {
            m_subtitleText.setString(L"Line " + std::to_wstring(m_currentLine) + L" of 8... Ingat!");
        } else {
            m_subtitleText.setString(L"Nakalusot ka! Ang galing!");
        }


        // --- Scroll Court (Dash) ---
        if (m_isDashing) {
            if (m_lineScrollOffset < m_targetScrollOffset) {
                m_lineScrollOffset += m_aldenDashSpeed * elapsed;

                if (m_lineScrollOffset >= m_targetScrollOffset) {
                    m_lineScrollOffset = m_targetScrollOffset;
                    m_isDashing = false;

                    if (m_currentLine == m_linesToCross) {
                        m_status = GameStatus::Won;
                        m_playerWon = true;
                        m_subtitleText.setString(L"Nakalusot ka! Ang galing!");
                        m_endTimer.restart();
                    }
                }
            }
        }

        // --- Move Blockers ---
        for (auto& blocker : m_blockers) {
            sf::Transform t = blocker.transform;
            sf::Vector2f pos = t.transformPoint(0, 0);

            pos.x += blocker.speed * blocker.direction * elapsed;

            if (pos.x > blocker.maxX) {
                pos.x = blocker.maxX;
                blocker.direction = -1;
            } else if (pos.x < blocker.minX) {
                pos.x = blocker.minX;
                blocker.direction = 1;
            }

            blocker.transform = sf::Transform().translate(pos.x, m_lines[blocker.lineIndex].getPosition().y);
        }

        // --- Check Collisions (only if dashing) ---
        if (m_isDashing) {
            checkCollisions();
        }

    } else if (m_status == GameStatus::Won || m_status == GameStatus::Lost) {
        if (m_endTimer.getElapsedTime().asSeconds() > 4.0f) {
            m_status = GameStatus::Exiting;
            m_endTimer.restart();
        }
    } else if (m_status == GameStatus::Exiting) {
        float fadeDuration = 1.5f;
        float fadeElapsed = m_endTimer.getElapsedTime().asSeconds();
        sf::Uint8 alpha = static_cast<sf::Uint8>(std::min(255.f, (fadeElapsed / fadeDuration) * 255.f));
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));

        if (fadeElapsed > fadeDuration) {
            if (m_playerWon) {
                m_nextState = GameState::Scene5_Cutscene2; // <-- Correct transition
            } else {
                m_nextState = GameState::GameOver;
            }
        }
    }
}

void Scene4::draw(sf::RenderTarget& target) {
    target.draw(m_background);

    sf::Transform courtTransform;
    courtTransform.translate(0, m_lineScrollOffset);
    // -------------------------------------
    sf::RenderStates courtStates(courtTransform);

    // Draw all lines using the main court transform
    for (const auto& line : m_lines) {
        target.draw(line, courtStates);
    }
    target.draw(m_finishLine, courtStates);

    for (const auto& blocker : m_blockers) {
        // Combine the court's scroll with the blocker's movement
        sf::Transform combinedTransform = courtTransform * blocker.transform;
        target.draw(blocker.shape, combinedTransform);
    }
    // ----------------------------------

    // Alden is drawn WITHOUT the courtStates, so he stays fixed on the screen
    sf::Transform aldenTransform;
    aldenTransform.translate(m_aldenFixedX, m_aldenFixedY);
    target.draw(m_aldenShape, aldenTransform);

    // Draw UI
    target.draw(m_subtitleText);
    target.draw(m_timerText);

    if (m_status == GameStatus::Exiting) {
        target.draw(m_fadeRect);
    }
}

GameState Scene4::getNextState() {
    return m_nextState;
}

void Scene4::setupTopDownCircle(sf::VertexArray& shape, float radius, sf::Color color) {
    shape.setPrimitiveType(sf::TriangleFan);
    shape.append(sf::Vertex(sf::Vector2f(0, 0), color)); // Center point
    int points = 20; // 20-sided circle
    for (int i = 0; i <= points; ++i) {
        float angle = (i / (float)points) * 2.f * M_PI_S4;
        sf::Vector2f p(cos(angle) * radius, sin(angle) * radius);
        shape.append(sf::Vertex(p, color));
    }
}

void Scene4::checkCollisions() {
    // Check collision only with the line Alden is currently dashing *to*
    // m_currentLine goes from 1 to 8 for blockers
    if (m_currentLine > 0 && m_currentLine <= (m_linesToCross - 1)) {
        Blocker& blocker = m_blockers[m_currentLine - 1]; // Array index is 0-7

        // Get blocker's current screen position
        sf::Vector2f blockerLocalPos = blocker.transform.transformPoint(0, 0);
        
        sf::Vector2f blockerScreenPos = sf::Vector2f(blockerLocalPos.x, blockerLocalPos.y + m_lineScrollOffset);

        sf::Vector2f aldenScreenPos(m_aldenFixedX, m_aldenFixedY);

        float dx = aldenScreenPos.x - blockerScreenPos.x;
        float dy = aldenScreenPos.y - blockerScreenPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < ALDEN_RADIUS + BLOCKER_RADIUS) {
            m_status = GameStatus::Lost;
            m_playerWon = false;
            m_subtitleText.setString(L"HULI! Na-taya ka!");
            m_endTimer.restart();
            m_isDashing = false;
        }
    }
}

void Scene4::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    // --- Court Dimensions ---
    m_courtX_Start = w * 0.15f;
    m_courtWidth = w * 0.70f;
    m_courtX_End = m_courtX_Start + m_courtWidth;

    m_aldenFixedX = w / 2.f;
    m_aldenFixedY = h * 0.8f; // Alden stays at 80% down the screen

    m_background.setSize(sf::Vector2f(w, h));
    m_background.setFillColor(sf::Color(105, 105, 105)); // Grey "court"

    float lineThickness = 4.f;

    // --- Line Setup (Stops in safe zone) ---
    // Line 0 (Start Line)
    sf::RectangleShape startLine;
    startLine.setSize(sf::Vector2f(m_courtWidth, lineThickness));
    startLine.setFillColor(sf::Color::Green);
    startLine.setOrigin(m_courtWidth / 2.f, lineThickness / 2.f);
    startLine.setPosition(w / 2.f, m_aldenFixedY + (m_lineSpacing * 0.5f));
    m_lines.push_back(startLine);

    // Lines 1-8 (Blocker Lines)
    for (int i = 1; i < m_linesToCross; ++i) {
        // Position each line in front of Alden, in the *middle* of a "safe zone"
        float yPos = m_aldenFixedY - (m_lineSpacing * (i - 0.5f));
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(m_courtWidth, lineThickness));
        line.setFillColor(sf::Color::White);
        line.setOrigin(m_courtWidth / 2.f, lineThickness / 2.f);
        line.setPosition(w / 2.f, yPos);
        m_lines.push_back(line);
    }

    // Finish Line (Line 9)
    // Position the finish line in the middle of the final "safe zone"
    float finishY = m_aldenFixedY - (m_lineSpacing * (m_linesToCross - 0.5f));
    // ------------------------------------------

    m_finishLine.setPrimitiveType(sf::Quads);
    float checkerSize = m_courtWidth / 20.f; // 20 checkers
    for (int j = 0; j < 20; ++j) {
        sf::Color color = (j % 2 == 0) ? sf::Color::Black : sf::Color::White;
        float left = m_courtX_Start + (j * checkerSize);
        float right = left + checkerSize;
        m_finishLine.append(sf::Vertex(sf::Vector2f(left, finishY - checkerSize / 2.f), color));
        m_finishLine.append(sf::Vertex(sf::Vector2f(right, finishY - checkerSize / 2.f), color));
        m_finishLine.append(sf::Vertex(sf::Vector2f(right, finishY + checkerSize / 2.f), color));
        m_finishLine.append(sf::Vertex(sf::Vector2f(left, finishY + checkerSize / 2.f), color));
    }

    // --- Setup UI ---
    m_subtitleText.setFont(m_font);
    m_subtitleText.setString(L"Handa ka na? Pindutin ang SPACE para tumawid!");
    m_subtitleText.setCharacterSize(24);
    m_subtitleText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(w / 2.0f, h * 0.12f);
    // ---------------------------------

    m_timerText.setFont(m_font);
    m_timerText.setString("TIME: 60.0");
    m_timerText.setCharacterSize(28);
    m_timerText.setFillColor(sf::Color::White);
    m_timerText.setPosition(10.f, 10.f);

    m_fadeRect.setSize(sf::Vector2f(w, h));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}