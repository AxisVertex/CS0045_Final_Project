// #include "Scene5.h"
// #include <string>
// #include <cmath> 
// #include <algorithm> 

// const float M_PI_S5 = 3.1415926535f;

// // --- HELPER FUNCTIONS ---

// void Scene5::addThickLine(sf::VertexArray& arr, sf::Vector2f p1, sf::Vector2f p2, float thickness, sf::Color color) {
//     sf::Vector2f dir = p2 - p1;
//     if (dir.x == 0 && dir.y == 0) return;
//     float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//     sf::Vector2f unitDir = dir / len;
//     sf::Vector2f unitPerp(-unitDir.y, unitDir.x); 

//     float t = thickness / 2.f;

//     arr.append(sf::Vertex(p1 - unitPerp * t, color));
//     arr.append(sf::Vertex(p1 + unitPerp * t, color));
//     arr.append(sf::Vertex(p2 + unitPerp * t, color));
//     arr.append(sf::Vertex(p2 - unitPerp * t, color));
// }

// void Scene5::setupLargeCircle(sf::VertexArray& shape, sf::Vector2f center, float radius, sf::Color color) {
//     shape.setPrimitiveType(sf::TriangleFan);
//     shape.append(sf::Vertex(center, color)); 
//     int points = 40;
//     for (int i = 0; i <= points; ++i) {
//         float angle = (i / (float)points) * 2.f * M_PI_S5;
//         sf::Vector2f p(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
//         shape.append(sf::Vertex(p, color));
//     }
// }

// // Helper for small sipa
// void Scene5::setupCircle(sf::VertexArray& shape, float radius, sf::Color color) {
//     shape.setPrimitiveType(sf::TriangleFan);
//     shape.append(sf::Vertex(sf::Vector2f(0, 0), color)); // Center
//     int points = 20;
//     for (int i = 0; i <= points; ++i) {
//         float angle = (i / (float)points) * 2.f * M_PI_S5;
//         sf::Vector2f p(cos(angle) * radius, sin(angle) * radius);
//         shape.append(sf::Vertex(p, color));
//     }
// }


// Scene5::Scene5(sf::RenderWindow& window) :
//     m_window(window),
//     m_nextState(GameState::Scene5_Cutscene2),
//     m_currentPart(CutscenePart::FadeIn),
//     m_sipaTossDuration(1.2f)
// {
//     std::cout << "Entering Scene 5: The Final Challenge (FIXED)" << std::endl;

//     if (!m_font.loadFromFile("arial.ttf")) {
//         std::cerr << "Could not load font 'arial.ttf'." << std::endl;
//     }

//     setupGraphics();
//     m_partClock.restart();
// }

// void Scene5::handleInput(sf::Event& event) {
//     if (event.type == sf::Event::MouseButtonPressed) {
//         if (event.mouseButton.button == sf::Mouse::Left) {
//             std::cout << "Cutscene 5 skipped!" << std::endl;
//             m_nextState = GameState::Scene6_SipaShowdown;
//         }
//     }
// }

// void Scene5::update(sf::Time dt) {
//     updateCutscene(dt);
// }

// void Scene5::updateCutscene(sf::Time dt) {
//     float elapsedTime = m_partClock.getElapsedTime().asSeconds();
//     float w = static_cast<float>(m_window.getSize().x);
//     float h = static_cast<float>(m_window.getSize().y);

//     switch (m_currentPart) {
//     case CutscenePart::FadeIn: {
//         if (elapsedTime < 2.0f) {
//             m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 - static_cast<sf::Uint8>(elapsedTime / 2.0f * 255)));
//             setSubtitle(L"");
//         } else if (elapsedTime < 4.5f) {
//             m_fadeRect.setFillColor(sf::Color(0, 0, 0, 0)); 
//             setSubtitle(L"Matapos ang sunod-sunod na hamon sa barangay…");
//         } else {
//             m_currentPart = CutscenePart::AldenCollapse;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::AldenCollapse: { // Pic 1
//         setSubtitle(L"Alden: \"Hah… tatlong laro na… pero… di pa rin kita nakikita, YayaDub…\"");
//         if (elapsedTime > 5.0f) {
//             m_currentPart = CutscenePart::ClapClapClap;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::ClapClapClap: { // Pic 2
//         setSubtitle(L""); 
        
//         float clapTime = 0.8f;
//         m_clapText1.setFillColor(sf::Color::Black);
//         m_clapText2.setFillColor(sf::Color::Black);
//         m_clapText3.setFillColor(sf::Color::Black);

//         if (elapsedTime < clapTime) { // Show first "Clap"
//             m_clapText2.setFillColor(sf::Color(0,0,0,0));
//             m_clapText3.setFillColor(sf::Color(0,0,0,0));
//         } else if (elapsedTime < clapTime * 2) { // Show second "Clap"
//             m_clapText1.setFillColor(sf::Color(0,0,0,0));
//             m_clapText3.setFillColor(sf::Color(0,0,0,0));
//         } else { // Show third "Clap"
//             m_clapText1.setFillColor(sf::Color(0,0,0,0));
//             m_clapText2.setFillColor(sf::Color(0,0,0,0));
//         }

//         if (elapsedTime > 3.0f) {
//             m_currentPart = CutscenePart::ArjoWalksIn;
//             m_partClock.restart();
//         }
//         break;
//     }
        
//     case CutscenePart::ArjoWalksIn: { 
//         setSubtitle(L"Arjo: \"Hindi ko inaasahan, Alden… nakakahanga ka rin pala. Akala ko hanggang Tumbang Preso ka lang.\"");
//         if (elapsedTime > 6.0f) {
//             m_currentPart = CutscenePart::AldenStands;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::AldenStands: { 
//         setSubtitle(L"Alden: \"Arjo! Nasaan si YayaDub!? Anong ginawa mo sa kanya!?\"");
//         if (elapsedTime > 5.0f) {
//             m_currentPart = CutscenePart::ArjoCloseUp;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::ArjoCloseUp: { 
//         setSubtitle(L"Arjo: \"Heh. Gusto mo siyang makita? Sige…\"");
//         m_arjoMoveTransform = sf::Transform::Identity; 
//         if (elapsedTime > 4.0f) {
//             m_currentPart = CutscenePart::ArjoMoves;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::ArjoMoves: { 
//         setSubtitle(L"");
//         float t = std::min(1.0f, elapsedTime / 1.5f); // 1.5 second move
//         float moveX = w * 0.4f * t; // Move RIGHT
//         m_arjoMoveTransform = sf::Transform::Identity;
//         m_arjoMoveTransform.translate(moveX, 0);

//         if (elapsedTime > 1.5f) {
//             m_currentPart = CutscenePart::RevealYaya;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::RevealYaya: { 
//         setSubtitle(L""); // No subtitle, just reveal
//         m_arjoMoveTransform = sf::Transform::Identity; 
//         m_arjoMoveTransform.translate(w * 0.4f, 0); // Arjo is on the RIGHT
//         if (elapsedTime > 2.0f) {
//             m_currentPart = CutscenePart::YayaZoomIn; 
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::YayaZoomIn: { 
//         setSubtitle(L"YayaDub: \"Alden! Kaya mo ‘yan!\"");
//         if (elapsedTime > 3.0f) {
//             m_currentPart = CutscenePart::AldenDetermined;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::AldenDetermined: { 
//         setSubtitle(L"Alden: \"YayaDub! Sandali lang, ililigtas kita!\"");
//         if (elapsedTime > 3.0f) {
//             m_currentPart = CutscenePart::ArjoBlocks;
//             m_partClock.restart();
//         }
//         break;
//     }
        
//     case CutscenePart::ArjoBlocks: { 
//         setSubtitle(L"Arjo: \"Tingin mo ganun kadali ‘yun? Kung gusto mo siyang makuha…\"");
//         if (elapsedTime > 4.5f) {
//             setSubtitle(L"Arjo: \"…patunayan mo muna na karapat-dapat ka.\"");
//         }
//         if (elapsedTime > 7.0f) {
//             m_currentPart = CutscenePart::ArjoToss;
//             m_partClock.restart();
//         }
//         break;
//     }
        
//     case CutscenePart::ArjoToss: {
//         setSubtitle(L"");
//         m_sipaTransform.translate(m_sipaStartPos); 
//         if (elapsedTime > 1.0f) {
//             m_currentPart = CutscenePart::SipaTossAnim;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::SipaTossAnim: { 
//         setSubtitle(L"");
//         float t = elapsedTime / m_sipaTossDuration;
//         t = std::min(t, 1.0f);
        
//         // Parabolic arc
//         float tx = t;
//         float ty = 1.0f - (2.f * t - 1.f) * (2.f * t - 1.f); 
        
//         sf::Vector2f newPos = m_sipaStartPos + (m_sipaEndPos - m_sipaStartPos) * tx;
//         newPos.y -= ty * 200.f; // 200px arc height
        
//         m_sipaTransform = sf::Transform().translate(newPos);
        
//         if (elapsedTime > m_sipaTossDuration) {
//             m_currentPart = CutscenePart::AldenCatch; 
//             m_partClock.restart();
//         }
//         break;
//     } 

//     case CutscenePart::AldenCatch: {
//         setSubtitle(L"");
//         if (elapsedTime > 0.5f) { 
//             m_currentPart = CutscenePart::AldenLooksAtSipa; 
//             m_partClock.restart();
//         }
//         break;
//     } 

//     case CutscenePart::AldenLooksAtSipa: { 
//         setSubtitle(L""); 
//         if (elapsedTime > 2.5f) { 
//             m_currentPart = CutscenePart::ArjoFinalChallenge;
//             m_partClock.restart();
//         }
//         break;
//     }
        
//     case CutscenePart::ArjoFinalChallenge: { 
//         setSubtitle(L"Arjo: \"Tapusin mo ‘ko sa huling laro — ang SIPA SHOWDOWN!\"");
//         if (elapsedTime > 5.0f) {
//             m_currentPart = CutscenePart::AldenAccepts;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::AldenAccepts: {
//         setSubtitle(L"Alden: \"Sige Arjo… sa larong ‘to, para ‘to kay YayaDub!\"");
//         if (elapsedTime > 4.0f) {
//             m_currentPart = CutscenePart::FaceOff;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::FaceOff: { 
//         setSubtitle(L"Ang pinakahuling laban ay magsisimula…");
//         if (elapsedTime > 4.0f) {
//             m_currentPart = CutscenePart::FadeOut;
//             m_partClock.restart();
//         }
//         break;
//     }

//     case CutscenePart::FadeOut: {
//         setSubtitle(L"");
//         m_fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(std::min(255.f, (elapsedTime / 1.5f * 255)))));
//         if (elapsedTime > 1.5f) {
//             m_nextState = GameState::Scene6_SipaShowdown;
//         }
//         break;
//     }
//     }
// }

// void Scene5::draw(sf::RenderTarget& target) {
//     // Backgrounds
//     if (m_currentPart < CutscenePart::ArjoWalksIn) {
//         target.draw(m_courtBg); 
//     } else if (m_currentPart == CutscenePart::AldenLooksAtSipa) {
//         target.draw(m_greyFloor); 
//     } else {
//         target.draw(m_gymBg);
//         target.draw(m_gymFloor);
//     }
    
//   //draw
//     switch (m_currentPart) {
//     case CutscenePart::FadeIn:
//     case CutscenePart::AldenCollapse: 
//         target.draw(m_pic1_aldenHead);
//         target.draw(m_pic1_aldenLimbs);
//         break;
    
//     case CutscenePart::ClapClapClap: 
//         target.draw(m_pic2_arjoHead);
//         target.draw(m_pic2_arjoBody);
//         target.draw(m_clapText1);
//         target.draw(m_clapText2);
//         target.draw(m_clapText3);
//         break;
        
//     case CutscenePart::ArjoWalksIn:  
//         target.draw(m_pic3_arjoHead);
//         target.draw(m_pic3_arjoBody);
//         break;

//     case CutscenePart::AldenStands: 
//         target.draw(m_pic4_aldenHead);
//         target.draw(m_pic4_aldenBody);
//         break;

//     case CutscenePart::ArjoCloseUp: 
//         target.draw(m_pic6_chair); // Yaya is behind
//         target.draw(m_pic6_yayaHead);
//         target.draw(m_pic6_yayaBody);
//         target.draw(m_pic6_ropes);
//         target.draw(m_pic5_arjoHead); // Arjo is in front
//         target.draw(m_pic5_arjoBody);
//         break;
    
//     case CutscenePart::ArjoMoves: 
 
//         target.draw(m_pic6_chair);
//         target.draw(m_pic6_yayaHead);
//         target.draw(m_pic6_yayaBody);
//         target.draw(m_pic6_ropes);
 
//         target.draw(m_pic5_arjoHead, m_arjoMoveTransform);
//         target.draw(m_pic5_arjoBody, m_arjoMoveTransform);
//         break;

//     case CutscenePart::RevealYaya: 

//         target.draw(m_pic6_chair);
//         target.draw(m_pic6_yayaHead);
//         target.draw(m_pic6_yayaBody);
//         target.draw(m_pic6_ropes);
    
//         target.draw(m_pic5_arjoHead, m_arjoMoveTransform);
//         target.draw(m_pic5_arjoBody, m_arjoMoveTransform);
//         break;

//     case CutscenePart::YayaZoomIn: 
//         target.draw(m_pic7_chair);
//         target.draw(m_pic7_yayaHead);
//         target.draw(m_pic7_yayaBody);
//         target.draw(m_pic7_ropes);
//         break;

//     case CutscenePart::AldenDetermined: 
//         target.draw(m_pic8_aldenHead);
//         target.draw(m_pic8_aldenBody);
//         break;
        
//     case CutscenePart::ArjoBlocks:
//         target.draw(m_pic9_arjoHead);
//         target.draw(m_pic9_arjoBody);
//         break;
        
//     case CutscenePart::ArjoToss:   
//         target.draw(m_pic10_arjoHead);
//         target.draw(m_pic10_arjoBody);
//         target.draw(m_sipaShape, m_sipaTransform); 
//         break;

//     case CutscenePart::SipaTossAnim: 
//         target.draw(m_sipaShape, m_sipaTransform);
//         break;
        
//     case CutscenePart::AldenCatch:
//         target.draw(m_pic12_aldenHead);
//         target.draw(m_pic12_aldenBody);
//         target.draw(m_pic12_sipa);
//         break; 

//     case CutscenePart::AldenLooksAtSipa: 
//         target.draw(m_pic13_aldenArm);
//         target.draw(m_pic13_sipa);
//         break; 

//     case CutscenePart::ArjoFinalChallenge:
//         target.draw(m_pic14_arjoHead);
//         target.draw(m_pic14_arjoBody);
//         target.draw(m_letterboxTop);
//         target.draw(m_letterboxBottom);
//         break;

//     case CutscenePart::AldenAccepts:
//         target.draw(m_pic15_aldenHead);
//         target.draw(m_pic15_aldenBody);
//         target.draw(m_letterboxTop);
//         target.draw(m_letterboxBottom);
//         break;

//     case CutscenePart::FaceOff: 
//         target.draw(m_pic16_aldenHead);
//         target.draw(m_pic16_aldenBody);
//         target.draw(m_pic16_aldenSipa);
//         target.draw(m_pic16_arjoHead);
//         target.draw(m_pic16_arjoBody);
//         target.draw(m_letterboxTop);
//         target.draw(m_letterboxBottom);
//         break;
    
//     default:
//         break;
//     }

//     // Always draw subtitles and fade rectangle on top
//     if (m_subtitleText.getString() != L"") {
//         target.draw(m_subtitleBackground);
//         target.draw(m_subtitleText);
//     }
    
//     if (m_currentPart == CutscenePart::FadeIn || m_currentPart == CutscenePart::FadeOut) {
//         target.draw(m_fadeRect);
//     }
// }

// GameState Scene5::getNextState() {
//     return m_nextState;
// }

// void Scene5::setSubtitle(const std::wstring& text) {
//     m_subtitleText.setString(text);
    
//     // Adjust font size for long subtitles
//     if (text.length() > 60) {
//         m_subtitleText.setCharacterSize(24);
//     } else {
//         m_subtitleText.setCharacterSize(32);
//     }
    
//     sf::FloatRect textRect = m_subtitleText.getLocalBounds();
//     m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
//     m_subtitleText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y * 0.85f);
    
//     m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 40, textRect.height * 1.5f + 20));
//     m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
//     m_subtitleBackground.setPosition(m_subtitleText.getPosition());
// }

// void Scene5::setupGraphics() {
//     sf::Vector2u windowSize = m_window.getSize();
//     float w = static_cast<float>(windowSize.x); // 1280
//     float h = static_cast<float>(windowSize.y); // 720

//     sf::Color aldenColor = sf::Color::Blue;
//     sf::Color yayaDubColor = sf::Color(255, 192, 203); // Pink
//     sf::Color arjoColor = sf::Color::Red;
//     sf::Color sipaColor = sf::Color(200, 200, 200);
//     sf::Color chairColor = sf::Color(139, 69, 19);
//     sf::Color clapColor = sf::Color::Black;

//     // --- Common ---
//     m_subtitleText.setFont(m_font);
//     m_subtitleText.setFillColor(sf::Color::White);
//     m_subtitleText.setOutlineColor(sf::Color::Black);
//     m_subtitleText.setOutlineThickness(2.f);
//     m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
//     m_fadeRect.setSize(sf::Vector2f(w, h));
//     m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255));
    
//     m_letterboxTop.setSize(sf::Vector2f(w, h * 0.15f));
//     m_letterboxTop.setFillColor(sf::Color::Black);
//     m_letterboxTop.setPosition(0, 0);
//     m_letterboxBottom.setSize(sf::Vector2f(w, h * 0.15f));
//     m_letterboxBottom.setFillColor(sf::Color::Black);
//     m_letterboxBottom.setPosition(0, h * 0.85f);

//     // Backgrounds
//     m_courtBg.setSize(sf::Vector2f(w, h));
//     m_courtBg.setFillColor(sf::Color(105, 105, 105)); // Patintero court
//     m_gymFloor.setSize(sf::Vector2f(w, h * 0.3f));
//     m_gymFloor.setPosition(0, h * 0.7f);
//     m_gymFloor.setFillColor(sf::Color(120, 120, 120)); 
//     m_gymBg.setSize(sf::Vector2f(w, h * 0.7f));
//     m_gymBg.setPosition(0, 0);
//     m_gymBg.setFillColor(sf::Color(189, 147, 101)); 
//     m_greyFloor.setSize(sf::Vector2f(w, h));
//     m_greyFloor.setFillColor(sf::Color(105, 105, 105)); 

//     // Sipa
//     setupCircle(m_sipaShape, 20.f, sipaColor);
    

//     float limbThickness = 30.f;
//     float headRadius_Normal = 80.f; 
//     float headRadius_Alden_Pic4 = 80.f; 
//     float headRadius_Arjo_Pic5 = 150.f; 
//     float headRadius_CloseUp = 180.f; 
 

//     // Alden Collapse
//     setupLargeCircle(m_pic1_aldenHead, sf::Vector2f(w * 0.65f, h * 0.45f), 150.f, aldenColor);
//     m_pic1_aldenLimbs.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.7f, h * 0.75f), limbThickness, aldenColor); // Arm 1
//     addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.5f, h * 0.7f), limbThickness, aldenColor); // Arm 2
//     addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.45f, h * 0.75f), limbThickness, aldenColor); // Leg 1 (thigh)
//     addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.45f, h * 0.75f), sf::Vector2f(w * 0.35f, h * 0.85f), limbThickness, aldenColor); // Leg 1 (shin)
//     addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.5f, h * 0.85f), limbThickness, aldenColor); // Leg 2

//     // Clapping 
//     setupLargeCircle(m_pic2_arjoHead, sf::Vector2f(w * 1.1f, h * 0.35f), 180.f, arjoColor);
//     m_pic2_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic2_arjoBody, sf::Vector2f(w * 1.1f, h * 0.5f), sf::Vector2f(w * 1.1f, h * 0.8f), limbThickness, arjoColor); // Body
//     addThickLine(m_pic2_arjoBody, sf::Vector2f(w * 1.1f, h * 0.55f), sf::Vector2f(w * 0.8f, h * 0.5f), limbThickness, arjoColor); // Arm 1 (STRAIGHT)
//     addThickLine(m_pic2_arjoBody, sf::Vector2f(w * 1.1f, h * 0.6f), sf::Vector2f(w * 0.8f, h * 0.65f), limbThickness, arjoColor); // Arm 2 (STRAIGHT)
//     // Clap Text
//     m_clapText1.setFont(m_font); m_clapText1.setString("Clap"); m_clapText1.setCharacterSize(50); m_clapText1.setFillColor(clapColor); m_clapText1.setPosition(w * 0.4f, h * 0.2f);
//     m_clapText2.setFont(m_font); m_clapText2.setString("Clap"); m_clapText2.setCharacterSize(50); m_clapText2.setFillColor(clapColor); m_clapText2.setPosition(w * 0.4f, h * 0.4f);
//     m_clapText3.setFont(m_font); m_clapText3.setString("Clap"); m_clapText3.setCharacterSize(50); m_clapText3.setFillColor(clapColor); m_clapText3.setPosition(w * 0.4f, h * 0.6f);

//     // Arjo Walks in
//     setupLargeCircle(m_pic3_arjoHead, sf::Vector2f(w * 0.5f, h * 0.4f), headRadius_Normal, arjoColor); // Smaller head, CENTERED
//     m_pic3_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.5f), sf::Vector2f(w * 0.5f, h * 0.7f), limbThickness, arjoColor); // Body
//     addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.55f), sf::Vector2f(w * 0.4f, h * 0.65f), limbThickness, arjoColor); // Arm
//     addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.55f), sf::Vector2f(w * 0.6f, h * 0.65f), limbThickness, arjoColor); // Arm
//     addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.7f), sf::Vector2f(w * 0.45f, h * 0.9f), limbThickness, arjoColor); // Leg
//     addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.7f), sf::Vector2f(w * 0.55f, h * 0.9f), limbThickness, arjoColor); // Leg
    
//     // Alden Stands
//     setupLargeCircle(m_pic4_aldenHead, sf::Vector2f(w * 0.5f, h * 0.47f), headRadius_Alden_Pic4, aldenColor);
//     m_pic4_aldenBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.55f), sf::Vector2f(w * 0.5f, h * 0.8f), limbThickness, aldenColor); // Body
//     addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.75f, h * 0.65f), limbThickness, aldenColor); // Arm (pointing RIGHT)
//     addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.45f, h * 0.75f), limbThickness, aldenColor); // Arm (down)
//     addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.45f, h * 0.95f), limbThickness, aldenColor); // Leg
//     addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.55f, h * 0.95f), limbThickness, aldenColor); // Leg

//     // Arjo Grinning
//     setupLargeCircle(m_pic5_arjoHead, sf::Vector2f(w * 0.5f, h * 0.53f), headRadius_Arjo_Pic5, arjoColor); 
//     m_pic5_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.7), sf::Vector2f(w * 0.5f, h * 1.1f), limbThickness, arjoColor); // Body
//     addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.78f), sf::Vector2f(w * 0.3f, h * 0.8f), limbThickness, arjoColor); // Leg
//     addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.78f), sf::Vector2f(w * 0.55f, h * 0.92f), limbThickness, arjoColor); // Leg
//     // addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.63f), sf::Vector2f(w * 0.4f, h * 0.65f), limbThickness, arjoColor); // Arm
//     // addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.63f), sf::Vector2f(w * 0.6f, h * 0.65f), limbThickness, arjoColor); // Arm

//     // Reveal Yaya
//     float yayaX = w * 0.5f; // Center of screen
//     float yayaY = h * 0.5f; // Higher up
//     float yayaScale = 0.4f; 
//     m_pic6_chair.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic6_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
//     addThickLine(m_pic6_chair, sf::Vector2f(yayaX + 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
//     addThickLine(m_pic6_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
//     setupLargeCircle(m_pic6_yayaHead, sf::Vector2f(yayaX, yayaY - 40*yayaScale), 60.f*yayaScale, yayaDubColor);
//     m_pic6_yayaBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic6_yayaBody, sf::Vector2f(yayaX, yayaY), sf::Vector2f(yayaX, yayaY + 150*yayaScale), limbThickness*yayaScale, yayaDubColor);
//     m_pic6_ropes.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic6_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+20*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+70*yayaScale), limbThickness*0.5f*yayaScale, chairColor);
//     addThickLine(m_pic6_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+70*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+20*yayaScale), limbThickness*0.5f*yayaScale, chairColor);

//     // Yaya ZoomIn
//     yayaX = w * 0.5f;
//     yayaY = h * 0.5f;
//     yayaScale = 1.0f; // Normal size
//     m_pic7_chair.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic7_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
//     addThickLine(m_pic7_chair, sf::Vector2f(yayaX + 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
//     addThickLine(m_pic7_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
//     setupLargeCircle(m_pic7_yayaHead, sf::Vector2f(yayaX, yayaY - 40*yayaScale), 60.f*yayaScale, yayaDubColor);
//     m_pic7_yayaBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic7_yayaBody, sf::Vector2f(yayaX, yayaY), sf::Vector2f(yayaX, yayaY + 150*yayaScale), limbThickness*yayaScale, yayaDubColor);
//     m_pic7_ropes.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic7_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+20*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+70*yayaScale), limbThickness*0.5f*yayaScale, chairColor);
//     addThickLine(m_pic7_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+70*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+20*yayaScale), limbThickness*0.5f*yayaScale, chairColor);

//     // Alden Determined
//     setupLargeCircle(m_pic8_aldenHead, sf::Vector2f(w * 0.5f, h * 0.4f), headRadius_Normal, aldenColor); // Smaller head
//     m_pic8_aldenBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.5f), sf::Vector2f(w * 0.5f, h * 0.8f), limbThickness, aldenColor); // Body
//     addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.75f, h * 0.65f), limbThickness, aldenColor); // Arm (pointing RIGHT)
//     addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.45f, h * 0.75f), limbThickness, aldenColor); // Arm (down)
//     addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.45f, h * 0.95f), limbThickness, aldenColor); // Leg
//     addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.55f, h * 0.95f), limbThickness, aldenColor); // Leg
        
//     // Arjo Blocks
//     setupLargeCircle(m_pic9_arjoHead, sf::Vector2f(w * 0.5f, h * 0.4f), headRadius_Normal, arjoColor); // Smaller head
//     m_pic9_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.5f), sf::Vector2f(w * 0.5f, h * 0.8f), limbThickness, arjoColor); // Body
//     addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.3f, h * 0.65f), limbThickness, arjoColor); // Arm
//     addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.7f, h * 0.65f), limbThickness, arjoColor); // Arm
//     addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.45f, h * 0.95f), limbThickness, arjoColor); // Leg
//     addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.55f, h * 0.95f), limbThickness, arjoColor); // Leg

//     // Arjo Toss
//     setupLargeCircle(m_pic10_arjoHead, sf::Vector2f(w * 0.8f, h * 0.3f), headRadius_CloseUp, arjoColor); // On the RIGHT, Smaller Head
//     m_pic10_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic10_arjoBody, sf::Vector2f(w * 0.8f, h * 0.5f), sf::Vector2f(w * 0.8f, h * 1.0f), limbThickness*1.5f, arjoColor); // Body
//     addThickLine(m_pic10_arjoBody, sf::Vector2f(w * 0.8f, h * 0.6f), sf::Vector2f(w * 0.4f, h * 0.4f), limbThickness*1.5f, arjoColor); // Arm tossing LEFT
    
//     // Sipa Toss Animation positions
//     m_sipaStartPos = sf::Vector2f(w * 1.1f, h * 0.5f); // Off-screen RIGHT
//     m_sipaEndPos = sf::Vector2f(w * -0.1f, h * 0.5f); // Off-screen LEFT
    
//     // Alden Catch
//     setupLargeCircle(m_pic12_aldenHead, sf::Vector2f(w * 0.2f, h * 0.3f), headRadius_CloseUp, aldenColor); // On the LEFT
//     m_pic12_aldenBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic12_aldenBody, sf::Vector2f(w * 0.2f, h * 0.5f), sf::Vector2f(w * 0.2f, h * 1.0f), limbThickness*1.5f, aldenColor); // Body
//     addThickLine(m_pic12_aldenBody, sf::Vector2f(w * 0.2f, h * 0.6f), sf::Vector2f(w * 0.6f, h * 0.4f), limbThickness*1.5f, aldenColor); // Arm from LEFT
//     setupLargeCircle(m_pic12_sipa, sf::Vector2f(w*0.6f, h*0.4f), 30.f, sipaColor); // Sipa on RIGHT-CENTER

//     // Alden Looks at Sipa
//     m_pic13_aldenArm.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic13_aldenArm, sf::Vector2f(w * -0.1f, h * 1.0f), sf::Vector2f(w * 0.4f, h * 0.6f), limbThickness*2.0f, aldenColor); // Arm from LEFT
//     setupLargeCircle(m_pic13_sipa, sf::Vector2f(w*0.4f, h*0.6f), 30.f, sipaColor); // Sipa on LEFT-CENTER

//     // Arjo Challenge
//     setupLargeCircle(m_pic14_arjoHead, sf::Vector2f(w * 0.5f, h * 0.5f), headRadius_CloseUp, arjoColor); // Smaller head, MOVED DOWN
//     m_pic14_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic14_arjoBody, sf::Vector2f(w * 0.5f, h * 0.65f), sf::Vector2f(w * 0.5f, h * 0.85f), limbThickness*2.f, arjoColor); // Body visible

//     // Alden Accepts
//     setupLargeCircle(m_pic15_aldenHead, sf::Vector2f(w * 0.5f, h * 0.5f), headRadius_CloseUp, aldenColor); // Smaller head, MOVED DOWN
//     m_pic15_aldenBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic15_aldenBody, sf::Vector2f(w * 0.5f, h * 0.65f), sf::Vector2f(w * 0.5f, h * 0.85f), limbThickness*2.f, aldenColor); // Body visible
    
//     // FaceOff
//     float floorLineY = h * 0.7f;
//     float bodyHeight = 300.f;
//     float headRadius = 80.f;
//     float bodyY = floorLineY + 50; 
//     float headY = floorLineY - bodyHeight + (headRadius * 0.5f); 
//     limbThickness = 25.f; 
    
//     // Alden
//     setupLargeCircle(m_pic16_aldenHead, sf::Vector2f(w * 0.3f, headY), headRadius, aldenColor);
//     m_pic16_aldenBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, bodyY), sf::Vector2f(w*0.3f, headY), limbThickness, aldenColor); // Body
//     addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, headY+50), sf::Vector2f(w*0.25f, headY+180), limbThickness, aldenColor); // Arm (longer)
//     addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, headY+50), sf::Vector2f(w*0.35f, headY+180), limbThickness, aldenColor); // Arm (longer)
//     addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, bodyY), sf::Vector2f(w*0.25f, bodyY+250), limbThickness, aldenColor); // Leg (longer)
//     addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, bodyY), sf::Vector2f(w*0.35f, bodyY+250), limbThickness, aldenColor); // Leg (longer)
//     setupLargeCircle(m_pic16_aldenSipa, sf::Vector2f(w * 0.25f, headY+180), 20.f, sipaColor);
    
//     // Arjo
//     setupLargeCircle(m_pic16_arjoHead, sf::Vector2f(w * 0.7f, headY), headRadius, arjoColor);
//     m_pic16_arjoBody.setPrimitiveType(sf::Quads);
//     addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, bodyY), sf::Vector2f(w*0.7f, headY), limbThickness, arjoColor); // Body
//     addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, headY+50), sf::Vector2f(w*0.65f, headY+180), limbThickness, arjoColor); // Arm (longer)
//     addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, headY+50), sf::Vector2f(w*0.75f, headY+180), limbThickness, arjoColor); // Arm (longer)
//     addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, bodyY), sf::Vector2f(w*0.65f, bodyY+250), limbThickness, arjoColor); // Leg (longer)
//     addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, bodyY), sf::Vector2f(w*0.75f, bodyY+250), limbThickness, arjoColor); // Leg (longer)
// }

#include "Scene5.h"
#include <string>
#include <cmath> 
#include <algorithm> 

const float M_PI_S5 = 3.1415926535f;

// --- HELPER FUNCTIONS ---

void Scene5::addThickLine(sf::VertexArray& arr, sf::Vector2f p1, sf::Vector2f p2, float thickness, sf::Color color) {
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

void Scene5::setupLargeCircle(sf::VertexArray& shape, sf::Vector2f center, float radius, sf::Color color) {
    shape.setPrimitiveType(sf::TriangleFan);
    shape.append(sf::Vertex(center, color)); 
    int points = 40;
    for (int i = 0; i <= points; ++i) {
        float angle = (i / (float)points) * 2.f * M_PI_S5;
        sf::Vector2f p(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
        shape.append(sf::Vertex(p, color));
    }
}

// Helper for small sipa
void Scene5::setupCircle(sf::VertexArray& shape, float radius, sf::Color color) {
    shape.setPrimitiveType(sf::TriangleFan);
    shape.append(sf::Vertex(sf::Vector2f(0, 0), color)); // Center
    int points = 20;
    for (int i = 0; i <= points; ++i) {
        float angle = (i / (float)points) * 2.f * M_PI_S5;
        sf::Vector2f p(cos(angle) * radius, sin(angle) * radius);
        shape.append(sf::Vertex(p, color));
    }
}


Scene5::Scene5(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene5_Cutscene2),
    m_currentPart(CutscenePart::FadeIn),
    m_sipaTossDuration(1.2f)
{
    std::cout << "Entering Scene 5: The Final Challenge (FIXED)" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    // --- LOAD SOUNDS (NEW) ---
    // Based on your folder structure: Sounds/Scene5/
    for (int i = 0; i < 11; ++i) {
        std::string path = "Sounds/Scene5/" + std::to_string(i + 1) + ".wav";
        if (!m_soundBuffers[i].loadFromFile(path)) {
            std::cerr << "Could not load sound: " << path << std::endl;
        }
    }
    // --- END NEW ---

    setupGraphics();
    m_partClock.restart();
}

void Scene5::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Cutscene 5 skipped!" << std::endl;
            m_voiceLine.stop(); // NEW: Stop sound on skip
            m_nextState = GameState::Scene6_SipaShowdown;
        }
    }
}

void Scene5::update(sf::Time dt) {
    updateCutscene(dt);
}

void Scene5::updateCutscene(sf::Time dt) {
    float elapsedTime = m_partClock.getElapsedTime().asSeconds();
    float w = static_cast<float>(m_window.getSize().x);
    float h = static_cast<float>(m_window.getSize().y);

    switch (m_currentPart) {
    case CutscenePart::FadeIn: {
        if (elapsedTime < 2.0f) {
            m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 - static_cast<sf::Uint8>(elapsedTime / 2.0f * 255)));
            setSubtitle(L"");
        } else if (elapsedTime < 7.0f) { // 2.0s fade + 5s Line (1)
            m_fadeRect.setFillColor(sf::Color(0, 0, 0, 0)); 
            setSubtitle(L"Matapos ang sunod-sunod na hamon sa barangay…");
            
            // NEW: Play sound 1 if not already playing
            if (m_voiceLine.getStatus() != sf::Sound::Playing) {
                m_voiceLine.setBuffer(m_soundBuffers[0]); // 1.wav
                m_voiceLine.play();
            }
        } else {
            m_voiceLine.stop(); // NEW: Stop sound 1
            m_currentPart = CutscenePart::AldenCollapse;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[1]); // NEW: Play sound 2 (2.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::AldenCollapse: { // Pic 1 / Line 2 (12s)
        setSubtitle(L"Alden: \"Hah… tatlong laro na… pero… di pa rin kita nakikita, YayaDub…\"");
        if (elapsedTime > 12.0f) { // Updated from 5.0
            m_voiceLine.stop(); // NEW: Stop sound 2
            m_currentPart = CutscenePart::ClapClapClap;
            m_partClock.restart();
            // No sound for clapping
        }
        break;
    }

    case CutscenePart::ClapClapClap: { // Pic 2
        setSubtitle(L""); 
        
        float clapTime = 0.8f;
        m_clapText1.setFillColor(sf::Color::Black);
        m_clapText2.setFillColor(sf::Color::Black);
        m_clapText3.setFillColor(sf::Color::Black);

        if (elapsedTime < clapTime) { // Show first "Clap"
            m_clapText2.setFillColor(sf::Color(0,0,0,0));
            m_clapText3.setFillColor(sf::Color(0,0,0,0));
        } else if (elapsedTime < clapTime * 2) { // Show second "Clap"
            m_clapText1.setFillColor(sf::Color(0,0,0,0));
            m_clapText3.setFillColor(sf::Color(0,0,0,0));
        } else { // Show third "Clap"
            m_clapText1.setFillColor(sf::Color(0,0,0,0));
            m_clapText2.setFillColor(sf::Color(0,0,0,0));
        }

        if (elapsedTime > 3.0f) { // Kept original 3.0s duration
            m_currentPart = CutscenePart::ArjoWalksIn;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[2]); // NEW: Play sound 3 (3.wav)
            m_voiceLine.play();
        }
        break;
    }
        
    case CutscenePart::ArjoWalksIn: { // Line 3 (9s)
        setSubtitle(L"Arjo: \"Hindi ko inaasahan, Alden… nakakahanga ka rin pala. Akala ko hanggang Tumbang Preso ka lang.\"");
        if (elapsedTime > 9.0f) { // Updated from 6.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::AldenStands;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[3]); // NEW: Play sound 4 (4.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::AldenStands: { // Line 4 (8s)
        setSubtitle(L"Alden: \"Arjo! Nasaan si YayaDub!? Anong ginawa mo sa kanya!?\"");
        if (elapsedTime > 8.0f) { // Updated from 5.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::ArjoCloseUp;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[4]); // NEW: Play sound 5 (5.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::ArjoCloseUp: { // Line 5 (6s)
        setSubtitle(L"Arjo: \"Heh. Gusto mo siyang makita? Sige…\"");
        m_arjoMoveTransform = sf::Transform::Identity; 
        if (elapsedTime > 6.0f) { // Updated from 4.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::ArjoMoves;
            m_partClock.restart();
            // No sound for movement
        }
        break;
    }

    case CutscenePart::ArjoMoves: { // No dialogue, 1.5s
        setSubtitle(L"");
        float t = std::min(1.0f, elapsedTime / 1.5f); // 1.5 second move
        float moveX = w * 0.4f * t; // Move RIGHT
        m_arjoMoveTransform = sf::Transform::Identity;
        m_arjoMoveTransform.translate(moveX, 0);

        if (elapsedTime > 1.5f) {
            m_currentPart = CutscenePart::RevealYaya;
            m_partClock.restart();
            // No sound
        }
        break;
    }

    case CutscenePart::RevealYaya: { // No dialogue, 2.0s
        setSubtitle(L""); // No subtitle, just reveal
        m_arjoMoveTransform = sf::Transform::Identity; 
        m_arjoMoveTransform.translate(w * 0.4f, 0); // Arjo is on the RIGHT
        if (elapsedTime > 2.0f) {
            m_currentPart = CutscenePart::YayaZoomIn; 
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[5]); // NEW: Play sound 6 (6.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::YayaZoomIn: { // Line 6 (4s)
        setSubtitle(L"YayaDub: \"Alden! Kaya mo ‘yan!\"");
        if (elapsedTime > 4.0f) { // Updated from 3.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::AldenDetermined;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[6]); // NEW: Play sound 7 (7.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::AldenDetermined: { // Line 7 (6s)
        setSubtitle(L"Alden: \"YayaDub! Sandali lang, ililigtas kita!\"");
        if (elapsedTime > 6.0f) { // Updated from 3.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::ArjoBlocks;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[7]); // NEW: Play sound 8 (8.wav)
            m_voiceLine.play();
        }
        break;
    }
        
    case CutscenePart::ArjoBlocks: { // Line 8 (10s)
        setSubtitle(L"Arjo: \"Tingin mo ganun kadali ‘yun? Kung gusto mo siyang makuha…\"");
        if (elapsedTime > 4.5f) { // Kept 4.5s for 2nd part of line
            setSubtitle(L"Arjo: \"…patunayan mo muna na karapat-dapat ka.\"");
        }
        if (elapsedTime > 10.0f) { // Updated from 7.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::ArjoToss;
            m_partClock.restart();
            // No sound
        }
        break;
    }
        
    case CutscenePart::ArjoToss: { // No dialogue, 1.0s
        setSubtitle(L"");
        m_sipaTransform.translate(m_sipaStartPos); 
        if (elapsedTime > 1.0f) {
            m_currentPart = CutscenePart::SipaTossAnim;
            m_partClock.restart();
        }
        break;
    }

    case CutscenePart::SipaTossAnim: { // No dialogue, 1.2s
        setSubtitle(L"");
        float t = elapsedTime / m_sipaTossDuration;
        t = std::min(t, 1.0f);
        
        // Parabolic arc
        float tx = t;
        float ty = 1.0f - (2.f * t - 1.f) * (2.f * t - 1.f); 
        
        sf::Vector2f newPos = m_sipaStartPos + (m_sipaEndPos - m_sipaStartPos) * tx;
        newPos.y -= ty * 200.f; // 200px arc height
        
        m_sipaTransform = sf::Transform().translate(newPos);
        
        if (elapsedTime > m_sipaTossDuration) {
            m_currentPart = CutscenePart::AldenCatch; 
            m_partClock.restart();
        }
        break;
    } 

    case CutscenePart::AldenCatch: { // No dialogue, 0.5s
        setSubtitle(L"");
        if (elapsedTime > 0.5f) { 
            m_currentPart = CutscenePart::AldenLooksAtSipa; 
            m_partClock.restart();
        }
        break;
    } 

    case CutscenePart::AldenLooksAtSipa: { // No dialogue, 2.5s
        setSubtitle(L""); 
        if (elapsedTime > 2.5f) { 
            m_currentPart = CutscenePart::ArjoFinalChallenge;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[8]); // NEW: Play sound 9 (9.wav)
            m_voiceLine.play();
        }
        break;
    }
        
    case CutscenePart::ArjoFinalChallenge: { // Line 9 (6s)
        setSubtitle(L"Arjo: \"Tapusin mo ‘ko sa huling laro — ang SIPA SHOWDOWN!\"");
        if (elapsedTime > 6.0f) { // Updated from 5.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::AldenAccepts;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[9]); // NEW: Play sound 10 (10.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::AldenAccepts: { // Line 10 (8s)
        setSubtitle(L"Alden: \"Sige Arjo… sa larong ‘to, para ‘to kay YayaDub!\"");
        if (elapsedTime > 8.0f) { // Updated from 4.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::FaceOff;
            m_partClock.restart();
            m_voiceLine.setBuffer(m_soundBuffers[10]); // NEW: Play sound 11 (11.wav)
            m_voiceLine.play();
        }
        break;
    }

    case CutscenePart::FaceOff: { // Line 11 (5s)
        setSubtitle(L"Ang pinakahuling laban ay magsisimula…");
        if (elapsedTime > 5.0f) { // Updated from 4.0
            m_voiceLine.stop(); // NEW
            m_currentPart = CutscenePart::FadeOut;
            m_partClock.restart();
        }
        break;
    }

    case CutscenePart::FadeOut: { // No dialogue, 1.5s
        setSubtitle(L"");
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(std::min(255.f, (elapsedTime / 1.5f * 255)))));
        if (elapsedTime > 1.5f) {
            m_voiceLine.stop(); // NEW: Stop sound just in case
            m_nextState = GameState::Scene6_SipaShowdown;
        }
        break;
    }
    }
}

void Scene5::draw(sf::RenderTarget& target) {
    // Backgrounds
    if (m_currentPart < CutscenePart::ArjoWalksIn) {
        target.draw(m_courtBg); 
    } else if (m_currentPart == CutscenePart::AldenLooksAtSipa) {
        target.draw(m_greyFloor); 
    } else {
        target.draw(m_gymBg);
        target.draw(m_gymFloor);
    }
    
 //draw
    switch (m_currentPart) {
    case CutscenePart::FadeIn:
    case CutscenePart::AldenCollapse: 
        target.draw(m_pic1_aldenHead);
        target.draw(m_pic1_aldenLimbs);
        break;
    
    case CutscenePart::ClapClapClap: 
        target.draw(m_pic2_arjoHead);
        target.draw(m_pic2_arjoBody);
        target.draw(m_clapText1);
        target.draw(m_clapText2);
        target.draw(m_clapText3);
        break;
        
    case CutscenePart::ArjoWalksIn:  
        target.draw(m_pic3_arjoHead);
        target.draw(m_pic3_arjoBody);
        break;

    case CutscenePart::AldenStands: 
        target.draw(m_pic4_aldenHead);
        target.draw(m_pic4_aldenBody);
        break;

    case CutscenePart::ArjoCloseUp: 
        target.draw(m_pic6_chair); // Yaya is behind
        target.draw(m_pic6_yayaHead);
        target.draw(m_pic6_yayaBody);
        target.draw(m_pic6_ropes);
        target.draw(m_pic5_arjoHead); // Arjo is in front
        target.draw(m_pic5_arjoBody);
        break;
    
    case CutscenePart::ArjoMoves: 
   
        target.draw(m_pic6_chair);
        target.draw(m_pic6_yayaHead);
        target.draw(m_pic6_yayaBody);
        target.draw(m_pic6_ropes);
   
        target.draw(m_pic5_arjoHead, m_arjoMoveTransform);
        target.draw(m_pic5_arjoBody, m_arjoMoveTransform);
        break;

    case CutscenePart::RevealYaya: 

        target.draw(m_pic6_chair);
        target.draw(m_pic6_yayaHead);
        target.draw(m_pic6_yayaBody);
        target.draw(m_pic6_ropes);
    
        target.draw(m_pic5_arjoHead, m_arjoMoveTransform);
        target.draw(m_pic5_arjoBody, m_arjoMoveTransform);
        break;

    case CutscenePart::YayaZoomIn: 
        target.draw(m_pic7_chair);
        target.draw(m_pic7_yayaHead);
        target.draw(m_pic7_yayaBody);
        target.draw(m_pic7_ropes);
        break;

    case CutscenePart::AldenDetermined: 
        target.draw(m_pic8_aldenHead);
        target.draw(m_pic8_aldenBody);
        break;
        
    case CutscenePart::ArjoBlocks:
        target.draw(m_pic9_arjoHead);
        target.draw(m_pic9_arjoBody);
        break;
        
    case CutscenePart::ArjoToss:   
        target.draw(m_pic10_arjoHead);
        target.draw(m_pic10_arjoBody);
        target.draw(m_sipaShape, m_sipaTransform); 
        break;

    case CutscenePart::SipaTossAnim: 
        target.draw(m_sipaShape, m_sipaTransform);
        break;
        
    case CutscenePart::AldenCatch:
        target.draw(m_pic12_aldenHead);
        target.draw(m_pic12_aldenBody);
        target.draw(m_pic12_sipa);
        break; 

    case CutscenePart::AldenLooksAtSipa: 
        target.draw(m_pic13_aldenArm);
        target.draw(m_pic13_sipa);
        break; 

    case CutscenePart::ArjoFinalChallenge:
        target.draw(m_pic14_arjoHead);
        target.draw(m_pic14_arjoBody);
        target.draw(m_letterboxTop);
        target.draw(m_letterboxBottom);
        break;

    case CutscenePart::AldenAccepts:
        target.draw(m_pic15_aldenHead);
        target.draw(m_pic15_aldenBody);
        target.draw(m_letterboxTop);
        target.draw(m_letterboxBottom);
        break;

    case CutscenePart::FaceOff: 
        target.draw(m_pic16_aldenHead);
        target.draw(m_pic16_aldenBody);
        target.draw(m_pic16_aldenSipa);
        target.draw(m_pic16_arjoHead);
        target.draw(m_pic16_arjoBody);
        target.draw(m_letterboxTop);
        target.draw(m_letterboxBottom);
        break;
    
    default:
        break;
    }

    // Always draw subtitles and fade rectangle on top
    if (m_subtitleText.getString() != L"") {
        target.draw(m_subtitleBackground);
        target.draw(m_subtitleText);
    }
    
    if (m_currentPart == CutscenePart::FadeIn || m_currentPart == CutscenePart::FadeOut) {
        target.draw(m_fadeRect);
    }
}

GameState Scene5::getNextState() {
    return m_nextState;
}

void Scene5::setSubtitle(const std::wstring& text) {
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
}

// (setupGraphics remains exactly the same as your original, so I am omitting it for brevity. 
//  You do not need to change anything in setupGraphics.)

void Scene5::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x); // 1280
    float h = static_cast<float>(windowSize.y); // 720

    sf::Color aldenColor = sf::Color::Blue;
    sf::Color yayaDubColor = sf::Color(255, 192, 203); // Pink
    sf::Color arjoColor = sf::Color::Red;
    sf::Color sipaColor = sf::Color(200, 200, 200);
    sf::Color chairColor = sf::Color(139, 69, 19);
    sf::Color clapColor = sf::Color::Black;

    // --- Common ---
    m_subtitleText.setFont(m_font);
    m_subtitleText.setFillColor(sf::Color::White);
    m_subtitleText.setOutlineColor(sf::Color::Black);
    m_subtitleText.setOutlineThickness(2.f);
    m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
    m_fadeRect.setSize(sf::Vector2f(w, h));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255));
    
    m_letterboxTop.setSize(sf::Vector2f(w, h * 0.15f));
    m_letterboxTop.setFillColor(sf::Color::Black);
    m_letterboxTop.setPosition(0, 0);
    m_letterboxBottom.setSize(sf::Vector2f(w, h * 0.15f));
    m_letterboxBottom.setFillColor(sf::Color::Black);
    m_letterboxBottom.setPosition(0, h * 0.85f);

    // Backgrounds
    m_courtBg.setSize(sf::Vector2f(w, h));
    m_courtBg.setFillColor(sf::Color(105, 105, 105)); // Patintero court
    m_gymFloor.setSize(sf::Vector2f(w, h * 0.3f));
    m_gymFloor.setPosition(0, h * 0.7f);
    m_gymFloor.setFillColor(sf::Color(120, 120, 120)); 
    m_gymBg.setSize(sf::Vector2f(w, h * 0.7f));
    m_gymBg.setPosition(0, 0);
    m_gymBg.setFillColor(sf::Color(189, 147, 101)); 
    m_greyFloor.setSize(sf::Vector2f(w, h));
    m_greyFloor.setFillColor(sf::Color(105, 105, 105)); 

    // Sipa
    setupCircle(m_sipaShape, 20.f, sipaColor);
    

    float limbThickness = 30.f;
    float headRadius_Normal = 80.f; 
    float headRadius_Alden_Pic4 = 80.f; 
    float headRadius_Arjo_Pic5 = 150.f; 
    float headRadius_CloseUp = 180.f; 
   

    // Alden Collapse
    setupLargeCircle(m_pic1_aldenHead, sf::Vector2f(w * 0.65f, h * 0.45f), 150.f, aldenColor);
    m_pic1_aldenLimbs.setPrimitiveType(sf::Quads);
    addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.7f, h * 0.75f), limbThickness, aldenColor); // Arm 1
    addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.5f, h * 0.7f), limbThickness, aldenColor); // Arm 2
    addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.45f, h * 0.75f), limbThickness, aldenColor); // Leg 1 (thigh)
    addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.45f, h * 0.75f), sf::Vector2f(w * 0.35f, h * 0.85f), limbThickness, aldenColor); // Leg 1 (shin)
    addThickLine(m_pic1_aldenLimbs, sf::Vector2f(w * 0.6f, h * 0.55f), sf::Vector2f(w * 0.5f, h * 0.85f), limbThickness, aldenColor); // Leg 2

    // Clapping 
    setupLargeCircle(m_pic2_arjoHead, sf::Vector2f(w * 1.1f, h * 0.35f), 180.f, arjoColor);
    m_pic2_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic2_arjoBody, sf::Vector2f(w * 1.1f, h * 0.5f), sf::Vector2f(w * 1.1f, h * 0.8f), limbThickness, arjoColor); // Body
    addThickLine(m_pic2_arjoBody, sf::Vector2f(w * 1.1f, h * 0.55f), sf::Vector2f(w * 0.8f, h * 0.5f), limbThickness, arjoColor); // Arm 1 (STRAIGHT)
    addThickLine(m_pic2_arjoBody, sf::Vector2f(w * 1.1f, h * 0.6f), sf::Vector2f(w * 0.8f, h * 0.65f), limbThickness, arjoColor); // Arm 2 (STRAIGHT)
    // Clap Text
    m_clapText1.setFont(m_font); m_clapText1.setString("Clap"); m_clapText1.setCharacterSize(50); m_clapText1.setFillColor(clapColor); m_clapText1.setPosition(w * 0.4f, h * 0.2f);
    m_clapText2.setFont(m_font); m_clapText2.setString("Clap"); m_clapText2.setCharacterSize(50); m_clapText2.setFillColor(clapColor); m_clapText2.setPosition(w * 0.4f, h * 0.4f);
    m_clapText3.setFont(m_font); m_clapText3.setString("Clap"); m_clapText3.setCharacterSize(50); m_clapText3.setFillColor(clapColor); m_clapText3.setPosition(w * 0.4f, h * 0.6f);

    // Arjo Walks in
    setupLargeCircle(m_pic3_arjoHead, sf::Vector2f(w * 0.5f, h * 0.4f), headRadius_Normal, arjoColor); // Smaller head, CENTERED
    m_pic3_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.5f), sf::Vector2f(w * 0.5f, h * 0.7f), limbThickness, arjoColor); // Body
    addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.55f), sf::Vector2f(w * 0.4f, h * 0.65f), limbThickness, arjoColor); // Arm
    addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.55f), sf::Vector2f(w * 0.6f, h * 0.65f), limbThickness, arjoColor); // Arm
    addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.7f), sf::Vector2f(w * 0.45f, h * 0.9f), limbThickness, arjoColor); // Leg
    addThickLine(m_pic3_arjoBody, sf::Vector2f(w * 0.5f, h * 0.7f), sf::Vector2f(w * 0.55f, h * 0.9f), limbThickness, arjoColor); // Leg
    
    // Alden Stands
    setupLargeCircle(m_pic4_aldenHead, sf::Vector2f(w * 0.5f, h * 0.47f), headRadius_Alden_Pic4, aldenColor);
    m_pic4_aldenBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.55f), sf::Vector2f(w * 0.5f, h * 0.8f), limbThickness, aldenColor); // Body
    addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.75f, h * 0.65f), limbThickness, aldenColor); // Arm (pointing RIGHT)
    addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.45f, h * 0.75f), limbThickness, aldenColor); // Arm (down)
    addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.45f, h * 0.95f), limbThickness, aldenColor); // Leg
    addThickLine(m_pic4_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.55f, h * 0.95f), limbThickness, aldenColor); // Leg

    // Arjo Grinning
    setupLargeCircle(m_pic5_arjoHead, sf::Vector2f(w * 0.5f, h * 0.53f), headRadius_Arjo_Pic5, arjoColor); 
    m_pic5_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.7), sf::Vector2f(w * 0.5f, h * 1.1f), limbThickness, arjoColor); // Body
    addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.78f), sf::Vector2f(w * 0.3f, h * 0.8f), limbThickness, arjoColor); // Leg
    addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.78f), sf::Vector2f(w * 0.55f, h * 0.92f), limbThickness, arjoColor); // Leg
    // addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.63f), sf::Vector2f(w * 0.4f, h * 0.65f), limbThickness, arjoColor); // Arm
    // addThickLine(m_pic5_arjoBody, sf::Vector2f(w * 0.5f, h * 0.63f), sf::Vector2f(w * 0.6f, h * 0.65f), limbThickness, arjoColor); // Arm

    // Reveal Yaya
    float yayaX = w * 0.5f; // Center of screen
    float yayaY = h * 0.5f; // Higher up
    float yayaScale = 0.4f; 
    m_pic6_chair.setPrimitiveType(sf::Quads);
    addThickLine(m_pic6_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
    addThickLine(m_pic6_chair, sf::Vector2f(yayaX + 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
    addThickLine(m_pic6_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
    setupLargeCircle(m_pic6_yayaHead, sf::Vector2f(yayaX, yayaY - 40*yayaScale), 60.f*yayaScale, yayaDubColor);
    m_pic6_yayaBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic6_yayaBody, sf::Vector2f(yayaX, yayaY), sf::Vector2f(yayaX, yayaY + 150*yayaScale), limbThickness*yayaScale, yayaDubColor);
    m_pic6_ropes.setPrimitiveType(sf::Quads);
    addThickLine(m_pic6_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+20*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+70*yayaScale), limbThickness*0.5f*yayaScale, chairColor);
    addThickLine(m_pic6_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+70*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+20*yayaScale), limbThickness*0.5f*yayaScale, chairColor);

    // Yaya ZoomIn
    yayaX = w * 0.5f;
    yayaY = h * 0.5f;
    yayaScale = 1.0f; // Normal size
    m_pic7_chair.setPrimitiveType(sf::Quads);
    addThickLine(m_pic7_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
    addThickLine(m_pic7_chair, sf::Vector2f(yayaX + 50*yayaScale, yayaY + 200*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
    addThickLine(m_pic7_chair, sf::Vector2f(yayaX - 50*yayaScale, yayaY - 50*yayaScale), sf::Vector2f(yayaX + 50*yayaScale, yayaY - 50*yayaScale), limbThickness*yayaScale, chairColor);
    setupLargeCircle(m_pic7_yayaHead, sf::Vector2f(yayaX, yayaY - 40*yayaScale), 60.f*yayaScale, yayaDubColor);
    m_pic7_yayaBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic7_yayaBody, sf::Vector2f(yayaX, yayaY), sf::Vector2f(yayaX, yayaY + 150*yayaScale), limbThickness*yayaScale, yayaDubColor);
    m_pic7_ropes.setPrimitiveType(sf::Quads);
    addThickLine(m_pic7_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+20*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+70*yayaScale), limbThickness*0.5f*yayaScale, chairColor);
    addThickLine(m_pic7_ropes, sf::Vector2f(yayaX-50*yayaScale, yayaY+70*yayaScale), sf::Vector2f(yayaX+50*yayaScale, yayaY+20*yayaScale), limbThickness*0.5f*yayaScale, chairColor);

    // Alden Determined
    setupLargeCircle(m_pic8_aldenHead, sf::Vector2f(w * 0.5f, h * 0.4f), headRadius_Normal, aldenColor); // Smaller head
    m_pic8_aldenBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.5f), sf::Vector2f(w * 0.5f, h * 0.8f), limbThickness, aldenColor); // Body
    addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.75f, h * 0.65f), limbThickness, aldenColor); // Arm (pointing RIGHT)
    addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.45f, h * 0.75f), limbThickness, aldenColor); // Arm (down)
    addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.45f, h * 0.95f), limbThickness, aldenColor); // Leg
    addThickLine(m_pic8_aldenBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.55f, h * 0.95f), limbThickness, aldenColor); // Leg
        
    // Arjo Blocks
    setupLargeCircle(m_pic9_arjoHead, sf::Vector2f(w * 0.5f, h * 0.4f), headRadius_Normal, arjoColor); // Smaller head
    m_pic9_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.5f), sf::Vector2f(w * 0.5f, h * 0.8f), limbThickness, arjoColor); // Body
    addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.3f, h * 0.65f), limbThickness, arjoColor); // Arm
    addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.6f), sf::Vector2f(w * 0.7f, h * 0.65f), limbThickness, arjoColor); // Arm
    addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.45f, h * 0.95f), limbThickness, arjoColor); // Leg
    addThickLine(m_pic9_arjoBody, sf::Vector2f(w * 0.5f, h * 0.8f), sf::Vector2f(w * 0.55f, h * 0.95f), limbThickness, arjoColor); // Leg

    // Arjo Toss
    setupLargeCircle(m_pic10_arjoHead, sf::Vector2f(w * 0.8f, h * 0.3f), headRadius_CloseUp, arjoColor); // On the RIGHT, Smaller Head
    m_pic10_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic10_arjoBody, sf::Vector2f(w * 0.8f, h * 0.5f), sf::Vector2f(w * 0.8f, h * 1.0f), limbThickness*1.5f, arjoColor); // Body
    addThickLine(m_pic10_arjoBody, sf::Vector2f(w * 0.8f, h * 0.6f), sf::Vector2f(w * 0.4f, h * 0.4f), limbThickness*1.5f, arjoColor); // Arm tossing LEFT
    
    // Sipa Toss Animation positions
    m_sipaStartPos = sf::Vector2f(w * 1.1f, h * 0.5f); // Off-screen RIGHT
    m_sipaEndPos = sf::Vector2f(w * -0.1f, h * 0.5f); // Off-screen LEFT
    
    // Alden Catch
    setupLargeCircle(m_pic12_aldenHead, sf::Vector2f(w * 0.2f, h * 0.3f), headRadius_CloseUp, aldenColor); // On the LEFT
    m_pic12_aldenBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic12_aldenBody, sf::Vector2f(w * 0.2f, h * 0.5f), sf::Vector2f(w * 0.2f, h * 1.0f), limbThickness*1.5f, aldenColor); // Body
    addThickLine(m_pic12_aldenBody, sf::Vector2f(w * 0.2f, h * 0.6f), sf::Vector2f(w * 0.6f, h * 0.4f), limbThickness*1.5f, aldenColor); // Arm from LEFT
    setupLargeCircle(m_pic12_sipa, sf::Vector2f(w*0.6f, h*0.4f), 30.f, sipaColor); // Sipa on RIGHT-CENTER

    // Alden Looks at Sipa
    m_pic13_aldenArm.setPrimitiveType(sf::Quads);
    addThickLine(m_pic13_aldenArm, sf::Vector2f(w * -0.1f, h * 1.0f), sf::Vector2f(w * 0.4f, h * 0.6f), limbThickness*2.0f, aldenColor); // Arm from LEFT
    setupLargeCircle(m_pic13_sipa, sf::Vector2f(w*0.4f, h*0.6f), 30.f, sipaColor); // Sipa on LEFT-CENTER

    // Arjo Challenge
    setupLargeCircle(m_pic14_arjoHead, sf::Vector2f(w * 0.5f, h * 0.5f), headRadius_CloseUp, arjoColor); // Smaller head, MOVED DOWN
    m_pic14_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic14_arjoBody, sf::Vector2f(w * 0.5f, h * 0.65f), sf::Vector2f(w * 0.5f, h * 0.85f), limbThickness*2.f, arjoColor); // Body visible

    // Alden Accepts
    setupLargeCircle(m_pic15_aldenHead, sf::Vector2f(w * 0.5f, h * 0.5f), headRadius_CloseUp, aldenColor); // Smaller head, MOVED DOWN
    m_pic15_aldenBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic15_aldenBody, sf::Vector2f(w * 0.5f, h * 0.65f), sf::Vector2f(w * 0.5f, h * 0.85f), limbThickness*2.f, aldenColor); // Body visible
    
    // FaceOff
    float floorLineY = h * 0.7f;
    float bodyHeight = 300.f;
    float headRadius = 80.f;
    float bodyY = floorLineY + 50; 
    float headY = floorLineY - bodyHeight + (headRadius * 0.5f); 
    limbThickness = 25.f; 
    
    // Alden
    setupLargeCircle(m_pic16_aldenHead, sf::Vector2f(w * 0.3f, headY), headRadius, aldenColor);
    m_pic16_aldenBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, bodyY), sf::Vector2f(w*0.3f, headY), limbThickness, aldenColor); // Body
    addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, headY+50), sf::Vector2f(w*0.25f, headY+180), limbThickness, aldenColor); // Arm (longer)
    addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, headY+50), sf::Vector2f(w*0.35f, headY+180), limbThickness, aldenColor); // Arm (longer)
    addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, bodyY), sf::Vector2f(w*0.25f, bodyY+250), limbThickness, aldenColor); // Leg (longer)
    addThickLine(m_pic16_aldenBody, sf::Vector2f(w*0.3f, bodyY), sf::Vector2f(w*0.35f, bodyY+250), limbThickness, aldenColor); // Leg (longer)
    setupLargeCircle(m_pic16_aldenSipa, sf::Vector2f(w * 0.25f, headY+180), 20.f, sipaColor);
    
    // Arjo
    setupLargeCircle(m_pic16_arjoHead, sf::Vector2f(w * 0.7f, headY), headRadius, arjoColor);
    m_pic16_arjoBody.setPrimitiveType(sf::Quads);
    addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, bodyY), sf::Vector2f(w*0.7f, headY), limbThickness, arjoColor); // Body
    addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, headY+50), sf::Vector2f(w*0.65f, headY+180), limbThickness, arjoColor); // Arm (longer)
    addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, headY+50), sf::Vector2f(w*0.75f, headY+180), limbThickness, arjoColor); // Arm (longer)
    addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, bodyY), sf::Vector2f(w*0.65f, bodyY+250), limbThickness, arjoColor); // Leg (longer)
    addThickLine(m_pic16_arjoBody, sf::Vector2f(w*0.7f, bodyY), sf::Vector2f(w*0.75f, bodyY+250), limbThickness, arjoColor); // Leg (longer)
}