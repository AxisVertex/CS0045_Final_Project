#include "Scene6.h"
#include <string>
#include <cmath>
#include <algorithm> 
#include <sstream>
#include <iomanip>

const float M_PI_S6_FNF = 3.1415926535f;


void addThickLine(sf::VertexArray& arr, sf::Vector2f p1, sf::Vector2f p2, float thickness, sf::Color color) {
    sf::Vector2f dir = p2 - p1;
    if (dir.x == 0 && dir.y == 0) return;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unitDir = dir / len;
    sf::Vector2f unitPerp(-unitDir.y, unitDir.x);
    float t = thickness / 2.f;
    arr.append(sf::Vertex(p1 - unitPerp * t, color));
    arr.append(sf::Vertex(p1 + unitPerp * t, color));
    arr.append(sf::Vertex(p2 + unitPerp * t, color));
    arr.append(sf::Vertex(p2 - unitPerp * t, color));
}

void setupLargeCircle(sf::VertexArray& shape, sf::Vector2f center, float radius, sf::Color color) {
    shape.setPrimitiveType(sf::TriangleFan);
    shape.append(sf::Vertex(center, color));
    int points = 40;
    for (int i = 0; i <= points; ++i) {
        float angle = (i / (float)points) * 2.f * M_PI_S6_FNF;
        sf::Vector2f p(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
        shape.append(sf::Vertex(p, color));
    }
}

// Helper for the Sipa icon
void setupSipaNote(sf::VertexArray& sipa, sf::Color color) {
    sipa.setPrimitiveType(sf::Quads);
    sf::Color sipaColor(200, 200, 200);
    // Use the base color (A=Blue, S=Green, D=Red) for the feathers
    
    float r = 10.f; // radius
    
    // Washer
    addThickLine(sipa, sf::Vector2f(-r, 0), sf::Vector2f(r, 0), 6, sipaColor);
    // Feathers
    addThickLine(sipa, sf::Vector2f(0, 0), sf::Vector2f(-r, -r * 2), 4, color);
    addThickLine(sipa, sf::Vector2f(0, 0), sf::Vector2f(0, -r * 2.5f), 4, color);
    addThickLine(sipa, sf::Vector2f(0, 0), sf::Vector2f(r, -r * 2), 4, color);
}

// Helper to add a sipa icon to a pose
void addSipaIconToPose(sf::VertexArray& poseBody, sf::Color color, sf::Transform transform) {
    sf::VertexArray sipaIcon;
    sipaIcon.setPrimitiveType(sf::Quads);
    sf::Color sipaColor(200, 200, 200);
    float r = 10.f;
    
    // Build the sipa icon at (0,0)
    addThickLine(sipaIcon, sf::Vector2f(-r, 0), sf::Vector2f(r, 0), 6, sipaColor);
    addThickLine(sipaIcon, sf::Vector2f(0, 0), sf::Vector2f(-r, -r * 2), 4, color);
    addThickLine(sipaIcon, sf::Vector2f(0, 0), sf::Vector2f(0, -r * 2.5f), 4, color);
    addThickLine(sipaIcon, sf::Vector2f(0, 0), sf::Vector2f(r, -r * 2), 4, color);

    // Apply the transform to each vertex and add it to the poseBody
    for (size_t i = 0; i < sipaIcon.getVertexCount(); ++i) {
        sf::Vertex v = sipaIcon[i];
        v.position = transform.transformPoint(v.position);
        poseBody.append(v);
    }
}

// This builds all 4 poses for one character
void setupCharacterPoses(
    sf::VertexArray& idleBody, sf::VertexArray& idleHead,
    sf::VertexArray& poseABody, sf::VertexArray& poseAHead,
    sf::VertexArray& poseSBody, sf::VertexArray& poseSHead,
    sf::VertexArray& poseDBody, sf::VertexArray& poseDHead,
    sf::Color color, float scale)
{
    float headRadius = 40.f * scale;
    float bodyHeight = 150.f * scale;
    float limbThickness = 12.f * scale;

    // --- Idle Pose ---
    setupLargeCircle(idleHead, sf::Vector2f(0, -bodyHeight), headRadius, color);
    idleBody.setPrimitiveType(sf::Quads);
    addThickLine(idleBody, sf::Vector2f(0, 0), sf::Vector2f(0, -bodyHeight), limbThickness, color); // Body
    addThickLine(idleBody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(-30*scale, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine(idleBody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(30*scale, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine(idleBody, sf::Vector2f(0, 0), sf::Vector2f(-20*scale, 50*scale), limbThickness, color); // Leg
    addThickLine(idleBody, sf::Vector2f(0, 0), sf::Vector2f(20*scale, 50*scale), limbThickness, color); // Leg
    
    // --- Pose A  ---
    setupLargeCircle(poseAHead, sf::Vector2f(0, -bodyHeight), headRadius, color);
    poseABody.setPrimitiveType(sf::Quads);
    addThickLine(poseABody, sf::Vector2f(0, 0), sf::Vector2f(0, -bodyHeight), limbThickness, color); // Body
    addThickLine(poseABody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(-30*scale, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine(poseABody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(30*scale, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine(poseABody, sf::Vector2f(0, 0), sf::Vector2f(20*scale, 50*scale), limbThickness, color); // Leg (straight)
    addThickLine(poseABody, sf::Vector2f(0, 0), sf::Vector2f(-30*scale, 0*scale), limbThickness, color); // Leg (kick)
    sf::Transform sipaTransformA;
    sipaTransformA.translate(-40*scale, -bodyHeight*0.2f); // Position near knee
    addSipaIconToPose(poseABody, sf::Color::Blue, sipaTransformA);
    
    // --- Pose S  ---
    setupLargeCircle(poseSHead, sf::Vector2f(0, -bodyHeight), headRadius, color);
    poseSBody.setPrimitiveType(sf::Quads);
    addThickLine(poseSBody, sf::Vector2f(0, 0), sf::Vector2f(0, -bodyHeight), limbThickness, color); // Body
    addThickLine(poseSBody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(-30*scale, -bodyHeight*0.7f), limbThickness, color); // Arm
    addThickLine(poseSBody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(30*scale, -bodyHeight*0.7f), limbThickness, color); // Arm
    addThickLine(poseSBody, sf::Vector2f(0, 0), sf::Vector2f(-20*scale, 50*scale), limbThickness, color); // Leg
    addThickLine(poseSBody, sf::Vector2f(0, 0), sf::Vector2f(20*scale, 50*scale), limbThickness, color); // Leg
    sf::Transform sipaTransformS;
    sipaTransformS.translate(0, -bodyHeight - headRadius - 20.f); // Position above head
    addSipaIconToPose(poseSBody, sf::Color::Green, sipaTransformS);

    // --- Pose D  ---
    setupLargeCircle(poseDHead, sf::Vector2f(0, -bodyHeight), headRadius, color);
    poseDBody.setPrimitiveType(sf::Quads);
    addThickLine(poseDBody, sf::Vector2f(0, 0), sf::Vector2f(0, -bodyHeight), limbThickness, color); // Body
    addThickLine(poseDBody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(-30*scale, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine(poseDBody, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(30*scale, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine(poseDBody, sf::Vector2f(0, 0), sf::Vector2f(-20*scale, 50*scale), limbThickness, color); // Leg (straight)
    addThickLine(poseDBody, sf::Vector2f(0, 0), sf::Vector2f(30*scale, 0*scale), limbThickness, color); // Leg (kick)
    sf::Transform sipaTransformD;
    sipaTransformD.translate(40*scale, -bodyHeight*0.2f); // Position near knee
    addSipaIconToPose(poseDBody, sf::Color::Red, sipaTransformD);
}

Scene6::Scene6(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene6_SipaShowdown),
    m_status(GameStatus::Starting),
    m_currentTurn(Turn::Alden),
    m_playerWon(false),
    m_targetY(window.getSize().y * 0.75f),
    m_spawnY(window.getSize().y * 0.1f),
    m_noteSpeed(450.f),
    m_hitWindow(50.f), 
    m_beatmapIndex(0),
    m_currentTurnNumber(0),
    m_aldenScore(0),
    m_arjoScore(0)
{
    std::cout << "Entering Scene 6: Sipa Showdown" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    // --- Create the Beatmaps (4 turns for Alden) ---
    // Turn 1
    m_beatmaps.push_back({
        {1.0f, 0}, {1.5f, 1}, {2.0f, 2}, {2.5f, 0}, {3.0f, 1}, {3.5f, 2},
        {4.5f, 0}, {4.75f, 1}, {5.0f, 2}
    });
    // Turn 2
    m_beatmaps.push_back({
        {1.0f, 0}, {1.25f, 0}, {1.75f, 1}, {2.25f, 2}, {2.5f, 2}, {3.0f, 1},
        {3.5f, 0}, {3.75f, 1}, {4.0f, 2}, {4.5f, 1}, {4.75f, 1}, {5.5f, 0}
    });
    // Turn 3
    m_beatmaps.push_back({
        {0.5f, 2}, {1.0f, 1}, {1.5f, 0}, {2.0f, 1}, {2.5f, 2}, {3.0f, 0}, {3.25f, 1},
        {3.5f, 2}, {4.0f, 0}, {4.1f, 0}, {4.2f, 0}, {5.0f, 1}, {5.25f, 2}, {5.5f, 1}
    });
    // Turn 4
    m_beatmaps.push_back({
        {0.5f, 0}, {0.75f, 1}, {1.0f, 2}, {1.25f, 1}, {1.5f, 0}, {1.75f, 2},
        {2.25f, 0}, {2.35f, 1}, {2.45f, 2}, {3.0f, 0}, {3.1f, 0}, {3.5f, 1},
        {3.6f, 1}, {4.0f, 2}, {4.1f, 2}, {4.5f, 0}, {4.75f, 1}, {5.0f, 2}, {5.25f, 0}
    });

    setupGraphics();
    
    // Set initial poses
    setAldenPose(0); // Idle
    setArjoPose(0);  // Idle

    m_startTimer.restart();
    m_turnText.setString("");

    m_subtitleText.setString(L"Stage 4: Sipa Showdown!");

    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y * 0.2f);
    
    textRect = m_subtitleText.getLocalBounds();
    m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height * 1.5f + 20));
    m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
    m_subtitleBackground.setPosition(m_subtitleText.getPosition());
    m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
}

void Scene6::handleInput(sf::Event& event) {
    if (m_status != GameStatus::Playing || m_currentTurn != Turn::Alden) return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            checkHit(0); // Lane 0
        } else if (event.key.code == sf::Keyboard::S) {
            checkHit(1); // Lane 1
        } else if (event.key.code == sf::Keyboard::D) {
            checkHit(2); // Lane 2
        }
    }
}

void Scene6::update(sf::Time dt) {
    float elapsed = dt.asSeconds();

    if (m_status == GameStatus::Starting) {
        if (m_startTimer.getElapsedTime().asSeconds() > 4.0f) {
            m_subtitleText.setString(L""); // Clear subtitle
            m_subtitleBackground.setFillColor(sf::Color::Transparent); // Hide background
        }
        if (m_startTimer.getElapsedTime().asSeconds() > 5.0f) { // 2s after subtitle disappears
            m_status = GameStatus::Playing;
            m_turnText.setString("Alden's Turn");
            m_gameTimer.restart();
            m_turnTimer.restart();
            m_beatmapIndex = 0;
        }
        return;
    }

    if (m_status == GameStatus::Playing) {
        float gameTime = m_gameTimer.getElapsedTime().asSeconds();
        float turnTime = m_turnTimer.getElapsedTime().asSeconds();

        // --- 1. Check for Turn Switch ---
        if (turnTime > 7.0f) {
            m_turnTimer.restart();
            m_currentTurnNumber++;
            m_beatmapIndex = 0; 
            m_notes.clear(); 
            setAldenPose(0); 
            setArjoPose(0); 
            m_feedbackText.setString(""); 

            if (m_currentTurn == Turn::Alden) {
                m_currentTurn = Turn::Arjo;
                m_turnText.setString("Arjo's Turn");
                m_aiTimer.restart(); 
            } else {
                m_currentTurn = Turn::Alden;
                m_turnText.setString("Alden's Turn");
            }
        }

        // --- 2. Check for Game End ---
        if (gameTime > 56.0f) {
            m_status = GameStatus::Ended;
            m_turnText.setString("FINISH!");
            m_playerWon = (m_aldenScore > m_arjoScore);
            setSubtitle(m_playerWon ? L"Panalo ka, Alden! Para kay YayaDub!" : L"Natalo ka! Hindi mo nailigtas si YayaDub...");
            m_endTimer.restart();
            return;
        }

        // --- 3. Update based on current turn ---
        if (m_currentTurn == Turn::Alden) {
            updateNotes(dt); // Move player's notes
            
            // Spawn player's notes from the correct beatmap
            int mapIdx = m_currentTurnNumber / 2; // 0, 1, 2, 3
            if (mapIdx < m_beatmaps.size() && m_beatmapIndex < m_beatmaps[mapIdx].size()) {
                if (turnTime >= m_beatmaps[mapIdx][m_beatmapIndex].spawnTime) {
                    spawnNote(m_beatmaps[mapIdx][m_beatmapIndex].lane);
                    m_beatmapIndex++;
                }
            }

            // Reset pose to idle
            if (m_poseTimer.getElapsedTime().asSeconds() > 0.5f) { // 0.5s hold
                setAldenPose(0);
            }

        } else {
            // Arjo's turn
            updateAI(dt);
        }

        updateUI();

    } else if (m_status == GameStatus::Ended) {
        // Wait 4 seconds
        if (m_endTimer.getElapsedTime().asSeconds() > 4.0f) {
            m_status = GameStatus::Exiting;
            m_endTimer.restart();
        }
    } else if (m_status == GameStatus::Exiting) {
        // Fade out
        float fadeDuration = 1.5f;
        float fadeElapsed = m_endTimer.getElapsedTime().asSeconds();
        sf::Uint8 alpha = static_cast<sf::Uint8>(std::min(255.f, (fadeElapsed / fadeDuration) * 255.f));
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));

        if (fadeElapsed > fadeDuration) {
            if (m_playerWon) {
                m_nextState = GameState::Scene7_Resolution; // <-- CORRECT TRANSITION
            } else {
                m_nextState = GameState::GameOver;
            }
        }
    }
}

void Scene6::updateAI(sf::Time dt) {
    // AI "hits" a note every 0.6 seconds
    if (m_aiTimer.getElapsedTime().asSeconds() > 0.6f) {
        m_aiTimer.restart();

        // 85% chance to hit, 15% chance to miss
        if ((rand() % 100) < 85) {
            m_arjoScore += 100;
            // Randomly pick a pose
            setArjoPose((rand() % 3) + 1); // Pose 1, 2, or 3
            m_poseTimer.restart();
            m_feedbackText.setString("Nice!");
            sf::FloatRect textRect = m_feedbackText.getLocalBounds();
            m_feedbackText.setPosition(m_targetDTransform.transformPoint(0,0).x + 40.f, m_targetY - textRect.height / 2.f);
        } else {
            setArjoPose(0); // Idle
            m_feedbackText.setString("Miss!");
            sf::FloatRect textRect = m_feedbackText.getLocalBounds();
            m_feedbackText.setPosition(m_targetDTransform.transformPoint(0,0).x + 40.f, m_targetY - textRect.height / 2.f);
        }
    }

    // Reset Arjo's pose to idle
    if (m_poseTimer.getElapsedTime().asSeconds() > 0.5f) {
        setArjoPose(0);
        m_feedbackText.setString("");
    }
}

void Scene6::updateNotes(sf::Time dt) {
    bool noteMissed = false;
    for (auto& note : m_notes) {
        if (note.active) {
            note.y_pos += m_noteSpeed * dt.asSeconds();
            float x_pos = 0.f;
            if (note.lane == 0) x_pos = m_targetATransform.transformPoint(0,0).x;
            if (note.lane == 1) x_pos = m_targetSTransform.transformPoint(0,0).x;
            if (note.lane == 2) x_pos = m_targetDTransform.transformPoint(0,0).x;
            
            note.transform = sf::Transform().translate(x_pos, note.y_pos);

            // Check for Miss (note passed the target)
            if (note.y_pos > m_targetY + m_hitWindow && !note.wasHit) {
                note.active = false;
                noteMissed = true;
            }
        }
    }
    if (noteMissed) {
        m_feedbackText.setString("Miss!");
        sf::FloatRect textRect = m_feedbackText.getLocalBounds();
        m_feedbackText.setPosition(m_targetATransform.transformPoint(0,0).x - 40.f - textRect.width, m_targetY - textRect.height / 2.f);
    }
}

void Scene6::updateUI() {
    float w = static_cast<float>(m_window.getSize().x);
    
    // Update score text
    m_aldenScoreText.setString("Score: " + std::to_string(m_aldenScore));
    m_arjoScoreText.setString("Score: " + std::to_string(m_arjoScore));

    // Update top health bar
    float totalScore = (float)m_aldenScore + (float)m_arjoScore;
    if (totalScore == 0) totalScore = 1; // Avoid divide by zero
    float aldenRatio = (float)m_aldenScore / totalScore;
    
    float barWidth = w * 0.6f;
    m_healthBarBlue.setSize(sf::Vector2f(barWidth * aldenRatio, 20.f));
    m_healthBarRed.setSize(sf::Vector2f(barWidth * (1.f - aldenRatio), 20.f));
    m_healthBarRed.setPosition(w * 0.2f + (barWidth * aldenRatio), m_healthBarBlue.getPosition().y);
}


void Scene6::draw(sf::RenderTarget& target) {
    target.draw(m_gymBg);
    target.draw(m_gymFloor);

    // Draw Characters
    target.draw(*m_currentAldenHead, m_aldenTransform);
    target.draw(*m_currentAldenBody, m_aldenTransform);
    target.draw(*m_currentArjoHead, m_arjoTransform);
    target.draw(*m_currentArjoBody, m_arjoTransform);
    
    // Draw Target Bars
    target.draw(m_targetA, m_targetATransform);
    target.draw(m_targetS, m_targetSTransform);
    target.draw(m_targetD, m_targetDTransform);
    target.draw(m_labelA);
    target.draw(m_labelS);
    target.draw(m_labelD);

    // Draw Notes
    for (auto& note : m_notes) {
        if (note.active) {
            target.draw(note.shape, note.transform);
        }
    }

    // Draw UI
    target.draw(m_aldenScoreText);
    target.draw(m_arjoScoreText);
    target.draw(m_turnText);
    target.draw(m_healthBarBlue);
    target.draw(m_healthBarRed);
    target.draw(m_feedbackText);

    if (m_subtitleText.getString() != L"") {
        target.draw(m_subtitleBackground);
        target.draw(m_subtitleText);
    }
    
    if (m_status == GameStatus::Exiting) {
        target.draw(m_fadeRect);
    }
}

GameState Scene6::getNextState() {
    return m_nextState;
}

void Scene6::checkHit(int lane) {
    bool noteHit = false;
    for (auto& note : m_notes) {
        if (note.active && !note.wasHit && note.lane == lane) {
            float dist = std::abs(note.y_pos - m_targetY);
            if (dist < m_hitWindow) {
                note.active = false;
                note.wasHit = true;
                noteHit = true;
                break; // Only hit one note per keypress
            }
        }
    }

    if (noteHit) {
        m_aldenScore += 100;
        setAldenPose(lane + 1); // 1=A, 2=S, 3=D
        m_poseTimer.restart();
        m_feedbackText.setString("Nice!");
        sf::FloatRect textRect = m_feedbackText.getLocalBounds();
        m_feedbackText.setPosition(m_targetATransform.transformPoint(0,0).x - 40.f - textRect.width, m_targetY - textRect.height / 2.f);
    } else {
        // No note in the window, just a "miss"
        m_feedbackText.setString("Miss!");
        sf::FloatRect textRect = m_feedbackText.getLocalBounds();
        m_feedbackText.setPosition(m_targetATransform.transformPoint(0,0).x - 40.f - textRect.width, m_targetY - textRect.height / 2.f);
    }
}

void Scene6::spawnNote(int lane) {
    Note newNote;
    sf::Color color;
    if (lane == 0) color = sf::Color::Blue;
    else if (lane == 1) color = sf::Color::Green;
    else color = sf::Color::Red;
    
    setupSipaNote(newNote.shape, color);
    
    newNote.y_pos = m_spawnY;
    newNote.lane = lane;
    newNote.active = true;
    newNote.wasHit = false;
    
    float x_pos = 0.f;
    if (lane == 0) x_pos = m_targetATransform.transformPoint(0,0).x;
    if (lane == 1) x_pos = m_targetSTransform.transformPoint(0,0).x;
    if (lane == 2) x_pos = m_targetDTransform.transformPoint(0,0).x;
    
    newNote.transform = sf::Transform().translate(x_pos, newNote.y_pos);
    m_notes.push_back(newNote);
}

void Scene6::setAldenPose(int pose) {
    if (pose == 1) { m_currentAldenHead = &m_aldenPoseAHead; m_currentAldenBody = &m_aldenPoseABody; }
    else if (pose == 2) { m_currentAldenHead = &m_aldenPoseSHead; m_currentAldenBody = &m_aldenPoseSBody; }
    else if (pose == 3) { m_currentAldenHead = &m_aldenPoseDHead; m_currentAldenBody = &m_aldenPoseDBody; }
    else { m_currentAldenHead = &m_aldenIdleHead; m_currentAldenBody = &m_aldenIdleBody; }
}
void Scene6::setArjoPose(int pose) {
    if (pose == 1) { m_currentArjoHead = &m_arjoPoseAHead; m_currentArjoBody = &m_arjoPoseABody; }
    else if (pose == 2) { m_currentArjoHead = &m_arjoPoseSHead; m_currentArjoBody = &m_arjoPoseSBody; }
    else if (pose == 3) { m_currentArjoHead = &m_arjoPoseDHead; m_currentArjoBody = &m_arjoPoseDBody; }
    else { m_currentArjoHead = &m_arjoIdleHead; m_currentArjoBody = &m_arjoIdleBody; }
}

void Scene6::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    // --- Backgrounds ---
    m_gymFloor.setSize(sf::Vector2f(w, h * 0.3f));
    m_gymFloor.setPosition(0, h * 0.7f);
    m_gymFloor.setFillColor(sf::Color(120, 120, 120));
    m_gymBg.setSize(sf::Vector2f(w, h)); // Full background
    m_gymBg.setPosition(0, 0);
    m_gymBg.setFillColor(sf::Color(189, 147, 101));

    // --- Characters ---
    setupCharacterPoses(
        m_aldenIdleBody, m_aldenIdleHead,
        m_aldenPoseABody, m_aldenPoseAHead,
        m_aldenPoseSBody, m_aldenPoseSHead,
        m_aldenPoseDBody, m_aldenPoseDHead,
        sf::Color::Blue, 1.0f
    );
    m_aldenTransform.translate(w * 0.2f, h * 0.75f);
    
    // Set up Arjo, mirrored
    setupCharacterPoses(
        m_arjoIdleBody, m_arjoIdleHead,
        m_arjoPoseABody, m_arjoPoseAHead,
        m_arjoPoseSBody, m_arjoPoseSHead,
        m_arjoPoseDBody, m_arjoPoseDHead,
        sf::Color::Red, 1.0f
    );
    m_arjoTransform.translate(w * 0.8f, h * 0.75f);
    m_arjoTransform.scale(-1.f, 1.f); // Flip him horizontally

    // --- UI ---
    m_subtitleText.setFont(m_font);
    m_subtitleText.setCharacterSize(36);
    m_subtitleText.setFillColor(sf::Color::White);
    m_subtitleText.setOutlineColor(sf::Color::Black);
    m_subtitleText.setOutlineThickness(2.f);
 
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(w / 2.0f, h * 0.2f);
    // -------------------------------------
    
    m_turnText.setFont(m_font);
    m_turnText.setString("Alden's Turn");
    m_turnText.setCharacterSize(30);
    m_turnText.setFillColor(sf::Color::White);
    textRect = m_turnText.getLocalBounds();
    m_turnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_turnText.setPosition(w / 2.0f, h * 0.3f);

    m_aldenScoreText.setFont(m_font);
    m_aldenScoreText.setString("Score: 0");
    m_aldenScoreText.setCharacterSize(24);
    m_aldenScoreText.setFillColor(sf::Color::White);
    m_aldenScoreText.setPosition(w * 0.1f, h * 0.15f);

    m_arjoScoreText.setFont(m_font);
    m_arjoScoreText.setString("Score: 0");
    m_arjoScoreText.setCharacterSize(24);
    m_arjoScoreText.setFillColor(sf::Color::White);
    textRect = m_arjoScoreText.getLocalBounds();
    m_arjoScoreText.setPosition(w * 0.9f - textRect.width, h * 0.15f);

    m_feedbackText.setFont(m_font);
    m_feedbackText.setCharacterSize(24);
    m_feedbackText.setFillColor(sf::Color::Yellow);

    m_fadeRect.setSize(sf::Vector2f(w, h));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    // --- Note Targets ---
    float targetBoxSize = 60.f;
    float targetSpacing = 80.f;
    float targetCenterX = w / 2.f;

    m_targetA.setPrimitiveType(sf::Quads);
    addThickLine(m_targetA, sf::Vector2f(-targetBoxSize/2.f, -targetBoxSize/2.f), sf::Vector2f(targetBoxSize/2.f, -targetBoxSize/2.f), 4.f, sf::Color::Blue);
    addThickLine(m_targetA, sf::Vector2f(targetBoxSize/2.f, -targetBoxSize/2.f), sf::Vector2f(targetBoxSize/2.f, targetBoxSize/2.f), 4.f, sf::Color::Blue);
    addThickLine(m_targetA, sf::Vector2f(targetBoxSize/2.f, targetBoxSize/2.f), sf::Vector2f(-targetBoxSize/2.f, targetBoxSize/2.f), 4.f, sf::Color::Blue);
    addThickLine(m_targetA, sf::Vector2f(-targetBoxSize/2.f, targetBoxSize/2.f), sf::Vector2f(-targetBoxSize/2.f, -targetBoxSize/2.f), 4.f, sf::Color::Blue);
    m_targetATransform.translate(targetCenterX - targetSpacing, m_targetY);

    m_targetS.setPrimitiveType(sf::Quads);
    addThickLine(m_targetS, sf::Vector2f(-targetBoxSize/2.f, -targetBoxSize/2.f), sf::Vector2f(targetBoxSize/2.f, -targetBoxSize/2.f), 4.f, sf::Color::Green);
    addThickLine(m_targetS, sf::Vector2f(targetBoxSize/2.f, -targetBoxSize/2.f), sf::Vector2f(targetBoxSize/2.f, targetBoxSize/2.f), 4.f, sf::Color::Green);
    addThickLine(m_targetS, sf::Vector2f(targetBoxSize/2.f, targetBoxSize/2.f), sf::Vector2f(-targetBoxSize/2.f, targetBoxSize/2.f), 4.f, sf::Color::Green);
    addThickLine(m_targetS, sf::Vector2f(-targetBoxSize/2.f, targetBoxSize/2.f), sf::Vector2f(-targetBoxSize/2.f, -targetBoxSize/2.f), 4.f, sf::Color::Green);
    m_targetSTransform.translate(targetCenterX, m_targetY);

    m_targetD.setPrimitiveType(sf::Quads);
    addThickLine(m_targetD, sf::Vector2f(-targetBoxSize/2.f, -targetBoxSize/2.f), sf::Vector2f(targetBoxSize/2.f, -targetBoxSize/2.f), 4.f, sf::Color::Red);
    addThickLine(m_targetD, sf::Vector2f(targetBoxSize/2.f, -targetBoxSize/2.f), sf::Vector2f(targetBoxSize/2.f, targetBoxSize/2.f), 4.f, sf::Color::Red);
    addThickLine(m_targetD, sf::Vector2f(targetBoxSize/2.f, targetBoxSize/2.f), sf::Vector2f(-targetBoxSize/2.f, targetBoxSize/2.f), 4.f, sf::Color::Red);
    addThickLine(m_targetD, sf::Vector2f(-targetBoxSize/2.f, targetBoxSize/2.f), sf::Vector2f(-targetBoxSize/2.f, -targetBoxSize/2.f), 4.f, sf::Color::Red);
    m_targetDTransform.translate(targetCenterX + targetSpacing, m_targetY);

    m_labelA.setFont(m_font); m_labelA.setString("A"); m_labelA.setCharacterSize(24); m_labelA.setPosition(targetCenterX - targetSpacing - 10, m_targetY + 35);
    m_labelS.setFont(m_font); m_labelS.setString("S"); m_labelS.setCharacterSize(24); m_labelS.setPosition(targetCenterX - 10, m_targetY + 35);
    m_labelD.setFont(m_font); m_labelD.setString("D"); m_labelD.setCharacterSize(24); m_labelD.setPosition(targetCenterX + targetSpacing - 10, m_targetY + 35);

    // --- Health Bar ---
    float barWidth = w * 0.6f;
    float barY = h * 0.05f;
    m_healthBarBlue.setSize(sf::Vector2f(barWidth / 2.f, 20.f));
    m_healthBarBlue.setFillColor(sf::Color::Blue);
    m_healthBarBlue.setPosition(w * 0.2f, barY);
    m_healthBarRed.setSize(sf::Vector2f(barWidth / 2.f, 20.f));
    m_healthBarRed.setFillColor(sf::Color::Red);
    m_healthBarRed.setPosition(w * 0.2f + barWidth / 2.f, barY);

    // --- Subtitle Background for Start Text ---
    textRect = m_subtitleText.getLocalBounds();
    m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height * 1.5f + 20));
    m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
    m_subtitleBackground.setPosition(m_subtitleText.getPosition());
    m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
}

 
void Scene6::setSubtitle(const std::wstring& text) {
    m_subtitleText.setString(text);
    
    // Adjust font size for long subtitles
    if (text.length() > 60) {
        m_subtitleText.setCharacterSize(24);
    } else {
        m_subtitleText.setCharacterSize(32);
    }
    
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y * 0.85f);
    
    m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height * 1.5f + 20));
    m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
    m_subtitleBackground.setPosition(m_subtitleText.getPosition());
    m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
}