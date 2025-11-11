#include "Scene7.h"
#include <string>
#include <cmath>
#include <algorithm> 
#include <sstream> 

const float M_PI_S7 = 3.1415926535f;

// --- HELPER FUNCTIONS ---
void addThickLine_S7(sf::VertexArray& arr, sf::Vector2f p1, sf::Vector2f p2, float thickness, sf::Color color) {
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

void setupLargeCircle_S7(sf::VertexArray& shape, sf::Vector2f center, float radius, sf::Color color) {
    shape.setPrimitiveType(sf::TriangleFan);
    shape.append(sf::Vertex(center, color));
    int points = 40;
    for (int i = 0; i <= points; ++i) {
        float angle = (i / (float)points) * 2.f * M_PI_S7;
        sf::Vector2f p(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
        shape.append(sf::Vertex(p, color));
    }
}

void setupStickman_S7(sf::VertexArray& head, sf::VertexArray& body, sf::Color color, float headRadius, float bodyHeight, float limbThickness) {
    // Setup head
    setupLargeCircle_S7(head, sf::Vector2f(0, -bodyHeight), headRadius, color);
    // Setup body
    body.setPrimitiveType(sf::Quads);
    addThickLine_S7(body, sf::Vector2f(0, 0), sf::Vector2f(0, -bodyHeight), limbThickness, color); // Body
    addThickLine_S7(body, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(-30, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine_S7(body, sf::Vector2f(0, -bodyHeight*0.8f), sf::Vector2f(30, -bodyHeight*0.6f), limbThickness, color); // Arm
    addThickLine_S7(body, sf::Vector2f(0, 0), sf::Vector2f(-20, 50), limbThickness, color); // Leg
    addThickLine_S7(body, sf::Vector2f(0, 0), sf::Vector2f(20, 50), limbThickness, color); // Leg
}


Scene7::Scene7(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene7_Resolution),
    m_currentPart(CutscenePart::FadeIn)
{
    std::cout << "Entering Scene 7: Resolution" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    // --- LOAD SOUNDS (NEW) ---
    for (int i = 0; i < 7; ++i) {
        std::string path = "Sounds/Scene7/" + std::to_string(i + 1) + ".wav";
        if (!m_soundBuffers[i].loadFromFile(path)) {
            std::cerr << "Could not load sound: " << path << std::endl;
        }
    }
    // --- END NEW ---

    setupGraphics();
    m_partClock.restart();
}

void Scene7::handleInput(sf::Event& event) {
    // Allow user to skip cutscene
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Cutscene 7 skipped!" << std::endl;
            m_voiceLine.stop(); // NEW: Stop sound on skip
            m_nextState = GameState::MainMenu; // Go back to menu
        }
    }
}

void Scene7::update(sf::Time dt) {
    updateCutscene(dt);
}

void Scene7::updateCutscene(sf::Time dt) {
    float elapsedTime = m_partClock.getElapsedTime().asSeconds();
    float w = static_cast<float>(m_window.getSize().x);
    float h = static_cast<float>(m_window.getSize().y);

    switch (m_currentPart) {
    case CutscenePart::FadeIn: {
        setSubtitle(L"");
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 - static_cast<sf::Uint8>(std::min(255.f, elapsedTime / 2.0f * 255))));
        if (elapsedTime > 2.0f) {
            m_currentPart = CutscenePart::WalkToBench;
            m_partClock.restart();
        }
        break;
    }
    case CutscenePart::WalkToBench: {
        setSubtitle(L"");
        float t = std::min(1.f, elapsedTime / 3.0f); // 3-second walk
        float benchX = w * 0.5f;
        float benchY = h * 0.75f;
        
        float aldenStartX = -100.f;
        float aldenEndX = benchX - 30.f;
        float aldenX = aldenStartX + (aldenEndX - aldenStartX) * t;
        m_aldenTransform = sf::Transform().translate(aldenX, benchY);
        
        float yayaStartX = -70.f;
        float yayaEndX = benchX + 30.f;
        float yayaX = yayaStartX + (yayaEndX - yayaStartX) * t;
        m_yayaDubTransform = sf::Transform().translate(yayaX, benchY);

        if (elapsedTime > 3.0f) {
            m_currentPart = CutscenePart::Dialogue1_Yaya;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[0]); // NEW: Play sound 1 (1.wav)
            m_voiceLine.play();
        }
        break;
    }
    case CutscenePart::Dialogue1_Yaya: { // Line 1 (7s)
        setSubtitle(L"YayaDub: “Alden… salamat ha. Akala ko tapos na ‘ko kay Arjo.”");
        if (elapsedTime > 7.0f) { // Updated from 5.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::Dialogue2_Alden;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[1]); // NEW: Play sound 2 (2.wav)
            m_voiceLine.play();
        }
        break;
    }
    case CutscenePart::Dialogue2_Alden: { // Line 2 (9s)
        setSubtitle(L"Alden: “Walang makakapigil sa pag-ibig ko—even si Arjo, pati Tumbang Preso pa yan!”");
        if (elapsedTime > 9.0f) { // Updated from 5.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::Silence;
            m_partClock.restart();
        }
        break;
    }
    case CutscenePart::Silence: {
        setSubtitle(L"");

        if (elapsedTime > 4.0f) { // Kept 4.0s pause
            m_currentPart = CutscenePart::Dialogue3_Yaya;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[2]); // NEW: Play sound 3 (3.wav)
            m_voiceLine.play();
        }
        break;
    }
    case CutscenePart::Dialogue3_Yaya: { // Line 3 (6s)
        setSubtitle(L"YayaDub: “Pero seryoso… ang dami mong dinaanan para lang sa ‘kin.”");
        if (elapsedTime > 6.0f) { // Updated from 4.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::Dialogue4_Alden;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[3]); // NEW: Play sound 4 (4.wav)
            m_voiceLine.play();
        }
        break;
    }
    case CutscenePart::Dialogue4_Alden: { // Line 4 (12s)
        setSubtitle(L"Alden: “Ganyan talaga kapag mahal mo. Parang laro — minsan napapagod, pero mas masaya kapag kasama ka sa dulo.”");
        if (elapsedTime > 12.0f) { // Updated from 6.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::ComedyEnding_Kid;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[4]); // NEW: Play sound 5 (5.wav)
            m_voiceLine.play();
        }
        break;
    }
    case CutscenePart::ComedyEnding_Kid: { // Line 5 (4s)
        setSubtitle(L"Kid (from afar): “Kuya Alden! Rematch sa Sipa!”");
        if (elapsedTime > 4.0f) { // Updated from 3.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::ComedyEnding_Alden;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[5]); // NEW: Play sound 6 (6.wav)
            m_voiceLine.play();
        }
        break;
    }
    case CutscenePart::ComedyEnding_Alden: { // Line 6 (4s)
        setSubtitle(L"Alden: “Next time na, bata! Love muna!”");
        if (elapsedTime > 4.0f) { // Updated from 3.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::FinalZoomOut; 
            m_partClock.restart();
        }
        break;
    }
    case CutscenePart::FinalZoomOut: {
        setSubtitle(L"");
        // if (elapsedTime > 3.0f) { // Kept 3.0s pause
            // m_currentPart = CutscenePart::FadeOut_FinalQuote;
            // m_partClock.restart();
            // m_voiceLine.setBuffer(m_soundBuffers[6]); // NEW: Play sound 7 (7.wav)
            // m_voiceLine.play();
            // setSubtitle(L"Ang Pag-ibig ay parang Palaro… minsan talo, pero laging masaya.", 28);
        // }

        m_currentPart = CutscenePart::FadeOut_FinalQuote;
        m_partClock.restart();
        m_voiceLine.setBuffer(m_soundBuffers[6]); // NEW: Play sound 7 (7.wav)
        m_voiceLine.play();
        setSubtitle(L"Ang Pag-ibig ay parang Palaro… minsan talo, pero laging masaya.", 28);

        break;
    }
    case CutscenePart::FadeOut_FinalQuote: { // Line 7 (7s)
        if (elapsedTime > 7.0f) { // Updated from 5.0 to match 7s duration
            m_fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(std::min(255.f, (elapsedTime / 3.0f * 255)))));
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::CreditsRoll;
            m_creditsText.setPosition(w / 2.f, h + 100.f); // Reset credits position
            m_partClock.restart();
        }
        break;
    }
    case CutscenePart::CreditsRoll: {
        setSubtitle(L"");
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255)); // Keep screen black
        
        // Scroll credits up
        float scrollSpeed = 50.f; // 50 pixels per second
        m_creditsText.move(0, -scrollSpeed * dt.asSeconds());

        // When credits are done scrolling
        float creditsHeight = m_creditsText.getLocalBounds().height;
        if (m_creditsText.getPosition().y < -creditsHeight - 100.f) {
            m_voiceLine.stop(); // NEW: Stop any lingering sound
            m_nextState = GameState::MainMenu; // Back to main menu
        }
        break;
    }
    }
}

void Scene7::draw(sf::RenderTarget& target) {
    target.clear(sf::Color::Black);

    if (m_currentPart < CutscenePart::CreditsRoll) {
        // Draw Sunset Park
        target.draw(m_sky);
        target.draw(m_grass);
        target.draw(m_benchArray, m_benchTransform);

        // Draw Characters
        target.draw(m_aldenHead, m_aldenTransform);
        target.draw(m_aldenBody, m_aldenTransform);
        target.draw(m_yayaDubHead, m_yayaDubTransform);
        target.draw(m_yayaDubBody, m_yayaDubTransform);

    } else {
        // Draw Credits
        target.draw(m_creditsText);
    }
    
 
    if (m_subtitleText.getString() != L"") {
        target.draw(m_subtitleBackground);
        target.draw(m_subtitleText);
    }
    
    if (m_currentPart == CutscenePart::FadeIn || m_currentPart == CutscenePart::FadeOut_FinalQuote) {
        target.draw(m_fadeRect);
    }
}

GameState Scene7::getNextState() {
    return m_nextState;
}


void Scene7::setSubtitle(const std::wstring& text, int charSize) {
    m_subtitleText.setString(text);
    m_subtitleText.setCharacterSize(charSize); 

    float maxWidth = m_window.getSize().x * 0.9f; 

    // Auto-shrink text that is too wide
    while (m_subtitleText.getLocalBounds().width > maxWidth && m_subtitleText.getCharacterSize() > 10) {
        m_subtitleText.setCharacterSize(m_subtitleText.getCharacterSize() - 2);
    }
    
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y * 0.85f);
    
    m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height * 1.5f + 20));
    m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
    m_subtitleBackground.setPosition(m_subtitleText.getPosition());

    if (text == L"") {
        m_subtitleBackground.setFillColor(sf::Color::Transparent);
    } else {
        m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
    }
}
// ----------------------------------------

void Scene7::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    // --- Common ---
    m_subtitleText.setFont(m_font);
    m_subtitleText.setFillColor(sf::Color::White);
    m_subtitleBackground.setFillColor(sf::Color::Transparent);
    m_fadeRect.setSize(sf::Vector2f(w, h));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

    sf::Color aldenColor = sf::Color::Blue;
    sf::Color yayaDubColor = sf::Color(255, 192, 203); // Pink
    
    // --- Sunset Park Scene ---
    m_sky.setSize(sf::Vector2f(w, h * 0.7f));
    m_sky.setFillColor(sf::Color(255, 150, 80)); // Sunset Orange
    m_grass.setSize(sf::Vector2f(w, h * 0.3f));
    m_grass.setFillColor(sf::Color(20, 100, 20)); // Darker Green
    m_grass.setPosition(0, h * 0.7f);

    // --- Bench (Copied from MainMenu) ---
    m_benchArray.setPrimitiveType(sf::Quads);
    sf::Color benchColor(139, 69, 19);
    sf::Color benchLegColor(101, 33, 0);
    float benchWidth = w * 0.4f;
    float benchHeight = h * 0.05f;
    float legWidth = w * 0.02f;
    float legHeight = h * 0.1f;
    float bw_half = benchWidth / 2.f;

    m_benchArray.append(sf::Vertex(sf::Vector2f(-bw_half, 0.f), benchColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(bw_half, 0.f), benchColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(bw_half, benchHeight), benchColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(-bw_half, benchHeight), benchColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(-bw_half * 0.8f, benchHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(-bw_half * 0.8f + legWidth, benchHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(-bw_half * 0.8f + legWidth, benchHeight + legHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(-bw_half * 0.8f, benchHeight + legHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(bw_half * 0.8f, benchHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(bw_half * 0.8f + legWidth, benchHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(bw_half * 0.8f + legWidth, benchHeight + legHeight), benchLegColor));
    m_benchArray.append(sf::Vertex(sf::Vector2f(bw_half * 0.8f, benchHeight + legHeight), benchLegColor));
    
    float benchX = w * 0.5f;
    float benchY = h * 0.75f;
    m_benchTransform.translate(benchX, benchY);

    // --- Characters ---
    setupStickman_S7(m_aldenHead, m_aldenBody, aldenColor, 20.f, 70.f, 5.f);
    setupStickman_S7(m_yayaDubHead, m_yayaDubBody, yayaDubColor, 20.f, 70.f, 5.f);
    
    // Start them off-screen
    m_aldenTransform.translate(-100.f, benchY);
    m_yayaDubTransform.translate(-70.f, benchY);


    // --- Credits ---
    std::wstringstream ss;
    ss << L"Outdoor Quest: The YayaDub Rescue\n\n\n"
        << L"Developed by Group 7:\n"
        << L"Ralph Derrick Abaya\nPatrick Gengania\nMikhael Edman Gomez\nJames Emmanuel Dolfo\n\n"
        << L"Course:\n"
        << L"BS Computer Science – Computer Graphics Finals\n\n\n"
        << L"Tools Used:\n"
        << L"SFML 2.6.2\n"
        << L"GLEW 2.1.0\n"
        << L"C++17\n\n\n\n"
        << L"Salamat sa Paglaro!";

    m_creditsText.setFont(m_font);
    m_creditsText.setString(ss.str());
    m_creditsText.setCharacterSize(36);
    m_creditsText.setFillColor(sf::Color::White);
    // Center the text
    sf::FloatRect textRect = m_creditsText.getLocalBounds();
    m_creditsText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top); // Origin at top-center
    m_creditsText.setPosition(w / 2.0f, h + 100.f); // Start below the screen
}