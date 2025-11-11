// #include "Scene1.h"
// #include <string> 

// Scene1::Scene1(sf::RenderWindow& window) :
//     m_window(window),
//     m_nextState(GameState::Scene1_Intro),
//     m_currentPart(CutscenePart::FadeIn)
// {
//     std::cout << "Entering Scene 1: The Kidnapping" << std::endl;

//     if (!m_font.loadFromFile("arial.ttf")) {
//         std::cerr << "Could not load font 'arial.ttf'." << std::endl;
//     }

//     setupGraphics();
//     m_partClock.restart();
// }

// void Scene1::handleInput(sf::Event& event) {
//     // Allow user to skip cutscene with a mouse click
//     if (event.type == sf::Event::MouseButtonPressed) {
//         if (event.mouseButton.button == sf::Mouse::Left) {
//             std::cout << "Cutscene skipped!" << std::endl;
//             m_nextState = GameState::Scene2_TumbangPreso;
//         }
//     }
// }

// void Scene1::update(sf::Time dt) {
//     // The main update function just calls the cutscene logic
//     updateCutscene(dt);
// }


// void Scene1::updateCutscene(sf::Time dt) {
//     float elapsedTime = m_partClock.getElapsedTime().asSeconds();

//     switch (m_currentPart) {
//     case CutscenePart::FadeIn:
//         setSubtitle(L"Isang tahimik na hapon sa Barangay Park…");
//         m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 - (sf::Uint8)(elapsedTime / 1.5f * 255)));
//         if (elapsedTime > 1.5f) {
//             m_currentPart = CutscenePart::Peaceful;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Peaceful:
//         // Just quiet for 2 seconds
//         if (elapsedTime > 2.0f) {
//             m_currentPart = CutscenePart::Dialogue_Yaya;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Yaya:
//         setSubtitle(L"YayaDub: \"Alden, ang peaceful dito, ‘no?\""); // <-- REVERTED
//         if (elapsedTime > 3.0f) {
//             m_currentPart = CutscenePart::Dialogue_Alden;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Alden:
//         setSubtitle(L"Alden: \"Oo… parang gusto ko nang tumigil ang oras kapag kasama ka.\"");
//         if (elapsedTime > 4.0f) {
//             m_currentPart = CutscenePart::YayaDisappears;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::YayaDisappears:
//         setSubtitle(L""); // No subtitle
//         if (elapsedTime > 0.5f) { // Quick delay
//             m_currentPart = CutscenePart::ArjoAppears;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::ArjoAppears:
//         setSubtitle(L"Arjo: \"Hindi puwedeng ganyan lang kadali, Alden!\""); 
//         if (elapsedTime > 3.0f) {
//             m_currentPart = CutscenePart::Dialogue_Alden_Arjo;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Alden_Arjo:
//         setSubtitle(L"Alden: \"ARJO!? Anong ginagawa mo dito!?\""); 
//         if (elapsedTime > 3.0f) {
//             m_currentPart = CutscenePart::Dialogue_Arjo_Challenge;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Arjo_Challenge:
//         setSubtitle(L"Arjo: \"Gusto mong makasama si YayaDub? Patunayan mo muna!\""); 
//         if (elapsedTime > 3.5f) {
//             m_currentPart = CutscenePart::Dialogue_Yaya_Help;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Yaya_Help:
//         setSubtitle(L"YayaDub: \"Alden! Tulungan mo ‘ko!\"");
//         if (elapsedTime > 2.5f) {
//             m_currentPart = CutscenePart::Dialogue_Arjo_Games;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Arjo_Games:
//         setSubtitle(L"Arjo: \"Kung tunay kang lalaki, tapusin mo ang mga laro ng barangay!\""); 
//         if (elapsedTime > 4.0f) {
//             m_currentPart = CutscenePart::Dialogue_Alden_Ano;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Alden_Ano:
//         setSubtitle(L"Alden: \"Ano!?\""); 
//         if (elapsedTime > 1.5f) {
//             m_currentPart = CutscenePart::Dialogue_Arjo_TumbangPreso;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::Dialogue_Arjo_TumbangPreso:
//         setSubtitle(L"Arjo: \"Simulan mo sa… TUMBANG PRESO!\""); 
//         if (elapsedTime > 3.5f) {
//             m_currentPart = CutscenePart::ArjoLeaves;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::ArjoLeaves:
//         setSubtitle(L"");
//         // Animate Arjo flying away
//         m_arjoHead.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_arjoBody.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_arjoArm1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_arjoArm2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_arjoLeg1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_arjoLeg2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
//         m_yayaDubKidnappedHead.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_yayaDubKidnappedBody.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         m_yayaDubKidnappedArm1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
//         m_yayaDubKidnappedArm2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
//         m_yayaDubKidnappedLeg1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
//         m_yayaDubKidnappedLeg2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
//         if (elapsedTime > 2.0f) {
//             m_currentPart = CutscenePart::AldenDetermined;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::AldenDetermined:
//         setSubtitle(L"Alden: \"Tumbang Preso pala ha… sige! Para kay YayaDub, lalaban ako!\""); 
//         if (elapsedTime > 5.0f) {
//             m_currentPart = CutscenePart::FadeOut;
//             m_partClock.restart();
//         }
//         break;

//     case CutscenePart::FadeOut:
//         setSubtitle(L"");
//         m_fadeRect.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)(elapsedTime / 1.5f * 255))); // Fade to White
//         if (elapsedTime > 1.5f) {
//             m_nextState = GameState::Scene2_TumbangPreso;
//         }
//         break;
//     }
// }

// void Scene1::draw(sf::RenderTarget& target) {
//     // Clear the screen
//     target.clear(sf::Color::Black);

//     // Draw elements based on the current part
//     if (m_currentPart < CutscenePart::ArjoAppears) {
//         // --- Draw Shot 1: Park Scene ---
//         target.draw(m_parkSky);
//         target.draw(m_parkGrass);
//         target.draw(m_parkBenchLeg1);
//         target.draw(m_parkBenchLeg2);
//         target.draw(m_parkBenchSeat);
        
//         // Alden
//         target.draw(m_aldenHead);
//         target.draw(m_aldenBody);
//         target.draw(m_aldenArm1); 
//         target.draw(m_aldenArm2); 
//         target.draw(m_aldenLeg1);
//         target.draw(m_aldenLeg2);

//         if (m_currentPart < CutscenePart::YayaDisappears) {
//             // YayaDub
//             target.draw(m_yayaDubHead);
 
//             target.draw(m_yayaDubBody);
    
//             target.draw(m_yayaDubArm1); 
//             target.draw(m_yayaDubArm2); 
//             target.draw(m_yayaDubLeg1);
//             target.draw(m_yayaDubLeg2);
//         } else {
//             // Exclamation mark!
//             target.draw(m_exclamationMark);
//         }
//     } else if (m_currentPart < CutscenePart::AldenDetermined) {
//         // --- Draw Shot 2: Arjo Floating Scene ---
//         target.draw(m_skyBg);
//         target.draw(m_aldenHeadLookingUp); // Alden's head at the bottom
        
//         // Arjo
//         target.draw(m_arjoHead);
//         target.draw(m_arjoBody);
//         target.draw(m_arjoArm1);
//         target.draw(m_arjoArm2);
//         target.draw(m_arjoLeg1); 
//         target.draw(m_arjoLeg2);

//         // YayaDub (Held by Arjo)
//         target.draw(m_yayaDubKidnappedHead);
//         target.draw(m_yayaDubKidnappedBody);
//         target.draw(m_yayaDubKidnappedArm1); 
//         target.draw(m_yayaDubKidnappedArm2); 
//         target.draw(m_yayaDubKidnappedLeg1); 
//         target.draw(m_yayaDubKidnappedLeg2); 
//     } else {
//         // --- Draw Shot 3: Alden Close-up ---
//         target.draw(m_closeupBg);
//         target.draw(m_aldenCloseupHead);
//         target.draw(m_aldenCloseupBody);
//         target.draw(m_letterboxTop);
//         target.draw(m_letterboxBottom);
//     }

//     // Always draw subtitles and fade rectangle on top
//     if (m_subtitleText.getString() != "") {
//         target.draw(m_subtitleBackground);
//         target.draw(m_subtitleText);
//     }
    
//     if (m_currentPart == CutscenePart::FadeIn || m_currentPart == CutscenePart::FadeOut) {
//         target.draw(m_fadeRect);
//     }
// }

// GameState Scene1::getNextState() {
//     return m_nextState;
// }

// void Scene1::setSubtitle(const std::wstring& text) {
//     m_subtitleText.setString(text);
    
//     // Adjust background for text
//     sf::FloatRect textRect = m_subtitleText.getLocalBounds();
//     m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
//     m_subtitleText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y * 0.85f);
    
//     m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 20, textRect.height + 20));
//     m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
//     m_subtitleBackground.setPosition(m_subtitleText.getPosition());
// }

// void Scene1::setupGraphics() {
//     sf::Vector2u windowSize = m_window.getSize();
//     float w = static_cast<float>(windowSize.x);
//     float h = static_cast<float>(windowSize.y);

//     // --- Common ---
//     m_subtitleText.setFont(m_font);
//     m_subtitleText.setCharacterSize(24);
//     m_subtitleText.setFillColor(sf::Color::White);
    
//     m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
    
//     m_fadeRect.setSize(sf::Vector2f(w, h));
//     m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

//     sf::Color aldenColor = sf::Color::Blue;
//     sf::Color yayaDubColor = sf::Color(255, 192, 203); // Pink
//     sf::Color arjoColor = sf::Color::Red;
    
//     // --- Shot 1: Park Scene (Copied from MainMenu) ---
//     m_parkSky.setSize(sf::Vector2f(w, h * 0.7f));
//     m_parkSky.setFillColor(sf::Color(135, 206, 235));
//     m_parkGrass.setSize(sf::Vector2f(w, h * 0.3f));
//     m_parkGrass.setFillColor(sf::Color(34, 139, 34));
//     m_parkGrass.setPosition(0, h * 0.7f);

//     float benchWidth = w * 0.4f;
//     float benchHeight = h * 0.05f;
//     float benchX = (w - benchWidth) / 2.0f;
//     float benchY = h * 0.75f;
//     m_parkBenchSeat.setSize(sf::Vector2f(benchWidth, benchHeight));
//     m_parkBenchSeat.setFillColor(sf::Color(139, 69, 19));
//     m_parkBenchSeat.setPosition(benchX, benchY);
//     m_parkBenchLeg1.setSize(sf::Vector2f(w * 0.02f, h * 0.1f));
//     m_parkBenchLeg1.setFillColor(sf::Color(101, 33, 0));
//     m_parkBenchLeg1.setPosition(benchX + benchWidth * 0.1f, benchY + benchHeight);
//     m_parkBenchLeg2.setSize(sf::Vector2f(w * 0.02f, h * 0.1f));
//     m_parkBenchLeg2.setFillColor(sf::Color(101, 33, 0));
//     m_parkBenchLeg2.setPosition(benchX + benchWidth * 0.8f, benchY + benchHeight);

//     float headRadius = 20.f;
//     float bodyHeight = 70.f;
//     float limbLength = 40.f; 
//     float limbThickness = 5.f;
//     sf::Vector2f aldenPos(benchX + benchWidth * 0.3f, benchY - bodyHeight - headRadius * 2);
//     m_aldenHead.setRadius(headRadius);
//     m_aldenHead.setFillColor(aldenColor);
//     m_aldenHead.setPosition(aldenPos);
//     m_aldenBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
//     m_aldenBody.setFillColor(aldenColor);
//     m_aldenBody.setPosition(aldenPos.x + headRadius - limbThickness / 2.f, aldenPos.y + headRadius * 2);

//     // --- Alden's Arms (Copied from MainMenu.cpp) ---
//     m_aldenArm1.setSize(sf::Vector2f(limbLength, limbThickness));
//     m_aldenArm1.setFillColor(aldenColor);
//     m_aldenArm1.setPosition(m_aldenBody.getPosition().x, m_aldenBody.getPosition().y + bodyHeight * 0.2f);
//     m_aldenArm1.setRotation(-20); // Slightly down

//     m_aldenArm2.setSize(sf::Vector2f(limbLength, limbThickness));
//     m_aldenArm2.setFillColor(aldenColor);
//     m_aldenArm2.setPosition(m_aldenBody.getPosition().x - (limbLength - limbThickness), m_aldenBody.getPosition().y + bodyHeight * 0.2f);
//     m_aldenArm2.setRotation(20); // Slightly down and mirrored
//     // --------------------------------------------------

//     m_aldenLeg1.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
//     m_aldenLeg1.setFillColor(aldenColor);
//     m_aldenLeg1.setPosition(m_aldenBody.getPosition().x, m_aldenBody.getPosition().y + bodyHeight);
//     m_aldenLeg2.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
//     m_aldenLeg2.setFillColor(aldenColor);
//     m_aldenLeg2.setPosition(m_aldenBody.getPosition().x + limbThickness, m_aldenBody.getPosition().y + bodyHeight);

//     sf::Vector2f yayaDubPos(benchX + benchWidth * 0.7f - headRadius * 2, benchY - bodyHeight - headRadius * 2);
//     m_yayaDubHead.setRadius(headRadius);
//     m_yayaDubHead.setFillColor(yayaDubColor);
//     m_yayaDubHead.setPosition(yayaDubPos);
//     m_yayaDubBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
//     m_yayaDubBody.setFillColor(yayaDubColor);
//     m_yayaDubBody.setPosition(yayaDubPos.x + headRadius - limbThickness / 2.f, yayaDubPos.y + headRadius * 2);

//     // --- YayaDub's Arms (Copied from MainMenu.cpp) ---
//     m_yayaDubArm1.setSize(sf::Vector2f(limbLength, limbThickness));
//     m_yayaDubArm1.setFillColor(yayaDubColor);
//     m_yayaDubArm1.setPosition(m_yayaDubBody.getPosition().x, m_yayaDubBody.getPosition().y + bodyHeight * 0.2f);
//     m_yayaDubArm1.setRotation(-20);

//     m_yayaDubArm2.setSize(sf::Vector2f(limbLength, limbThickness));
//     m_yayaDubArm2.setFillColor(yayaDubColor);
//     m_yayaDubArm2.setPosition(m_yayaDubBody.getPosition().x - (limbLength - limbThickness), m_yayaDubBody.getPosition().y + bodyHeight * 0.2f);
//     m_yayaDubArm2.setRotation(20);
//     // --------------------------------------------------
    
//     m_yayaDubLeg1.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
//     m_yayaDubLeg1.setFillColor(yayaDubColor);
//     m_yayaDubLeg1.setPosition(m_yayaDubBody.getPosition().x, m_yayaDubBody.getPosition().y + bodyHeight);
//     m_yayaDubLeg2.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
//     m_yayaDubLeg2.setFillColor(yayaDubColor);
//     m_yayaDubLeg2.setPosition(m_yayaDubBody.getPosition().x + limbThickness, m_yayaDubBody.getPosition().y + bodyHeight);

//     m_exclamationMark.setFont(m_font);
//     m_exclamationMark.setString("!");
//     m_exclamationMark.setCharacterSize(48);
//     m_exclamationMark.setFillColor(sf::Color::Black);
//     m_exclamationMark.setPosition(aldenPos.x + headRadius, aldenPos.y - 50);

//     // --- Shot 2: Arjo Floating Scene ---
//     m_skyBg.setSize(sf::Vector2f(w, h));
//     m_skyBg.setFillColor(sf::Color(135, 206, 235));

//     m_aldenHeadLookingUp.setRadius(headRadius * 1.5f);
//     m_aldenHeadLookingUp.setFillColor(aldenColor);
//     m_aldenHeadLookingUp.setPosition(w * 0.2f, h * 0.7f);

//     // --- Alden's head looking up (Big version for Shot 2) ---
//     m_aldenHeadLookingUp.setRadius(w * 0.3f); 
//     m_aldenHeadLookingUp.setFillColor(aldenColor);
//     m_aldenHeadLookingUp.setPosition(-w * 0.1f, h * 0.4f); 

//     sf::Vector2f arjoPos(w * 0.6f, h * 0.3f);
//     m_arjoHead.setRadius(headRadius * 1.2f);
//     m_arjoHead.setFillColor(arjoColor);
//     m_arjoHead.setPosition(arjoPos);
//     m_arjoBody.setSize(sf::Vector2f(limbThickness * 1.5f, bodyHeight * 1.2f));
//     m_arjoBody.setFillColor(arjoColor);
//     m_arjoBody.setPosition(arjoPos.x + headRadius * 1.2f - limbThickness * 1.5f / 2.f, arjoPos.y + headRadius * 2.4f);
//     m_arjoArm1.setSize(sf::Vector2f(bodyHeight * 0.6f, limbThickness * 1.5f));
//     m_arjoArm1.setFillColor(arjoColor);
//     m_arjoArm1.setPosition(m_arjoBody.getPosition());
//     m_arjoArm2.setSize(sf::Vector2f(bodyHeight * 0.6f, limbThickness * 1.5f));
//     m_arjoArm2.setFillColor(arjoColor);
//     m_arjoArm2.setPosition(m_arjoBody.getPosition().x, m_arjoBody.getPosition().y + 10.f);

//     // --- Arjo's Legs ---
//     m_arjoLeg1.setSize(sf::Vector2f(limbThickness * 1.5f, bodyHeight * 0.8f));
//     m_arjoLeg1.setFillColor(arjoColor);
//     m_arjoLeg1.setPosition(m_arjoBody.getPosition().x, m_arjoBody.getPosition().y + bodyHeight * 1.2f);
//     m_arjoLeg1.setRotation(-10.f);
//     m_arjoLeg2.setSize(sf::Vector2f(limbThickness * 1.5f, bodyHeight * 0.8f));
//     m_arjoLeg2.setFillColor(arjoColor);
//     m_arjoLeg2.setPosition(m_arjoBody.getPosition().x + limbThickness, m_arjoBody.getPosition().y + bodyHeight * 1.2f);
//     m_arjoLeg2.setRotation(10.f);
//     // ---------------------

//     m_yayaDubKidnappedHead.setRadius(headRadius);
//     m_yayaDubKidnappedHead.setFillColor(yayaDubColor);
//     m_yayaDubKidnappedHead.setPosition(arjoPos.x + 50.f, arjoPos.y + 20.f);
//     m_yayaDubKidnappedBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
//     m_yayaDubKidnappedBody.setFillColor(yayaDubColor);
//     m_yayaDubKidnappedBody.setPosition(m_yayaDubKidnappedHead.getPosition().x + headRadius - limbThickness / 2.f, m_yayaDubKidnappedHead.getPosition().y + headRadius * 2);
 

//     // --- YayaDub's Kidnapped Limbs ---
//     m_yayaDubKidnappedArm1.setSize(sf::Vector2f(limbLength * 0.8f, limbThickness));
//     m_yayaDubKidnappedArm1.setFillColor(yayaDubColor);
//     m_yayaDubKidnappedArm1.setPosition(m_yayaDubKidnappedBody.getPosition().x, m_yayaDubKidnappedBody.getPosition().y + 5.f);
//     m_yayaDubKidnappedArm1.setRotation(20.f); // Dangling
//     m_yayaDubKidnappedArm2.setSize(sf::Vector2f(limbLength * 0.8f, limbThickness));
//     m_yayaDubKidnappedArm2.setFillColor(yayaDubColor);
//     m_yayaDubKidnappedArm2.setPosition(m_yayaDubKidnappedBody.getPosition().x, m_yayaDubKidnappedBody.getPosition().y + 10.f);
//     m_yayaDubKidnappedArm2.setRotation(10.f); // Dangling

//     m_yayaDubKidnappedLeg1.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
//     m_yayaDubKidnappedLeg1.setFillColor(yayaDubColor);
//     m_yayaDubKidnappedLeg1.setPosition(m_yayaDubKidnappedBody.getPosition().x, m_yayaDubKidnappedBody.getPosition().y + bodyHeight);
//     m_yayaDubKidnappedLeg1.setRotation(-5.f); // Dangling
//     m_yayaDubKidnappedLeg2.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
//     m_yayaDubKidnappedLeg2.setFillColor(yayaDubColor);
//     m_yayaDubKidnappedLeg2.setPosition(m_yayaDubKidnappedBody.getPosition().x + limbThickness, m_yayaDubKidnappedBody.getPosition().y + bodyHeight);
//     m_yayaDubKidnappedLeg2.setRotation(5.f); // Dangling
//     // ---------------------------------

//     // --- Shot 3: Alden Close-up ---
//     m_closeupBg.setSize(sf::Vector2f(w, h));
//     m_closeupBg.setFillColor(sf::Color(135, 206, 235));
    
//     m_aldenCloseupHead.setRadius(w * 0.2f);
//     m_aldenCloseupHead.setFillColor(aldenColor);
//     m_aldenCloseupHead.setPosition(w / 2.f - m_aldenCloseupHead.getRadius(), h / 2.f - m_aldenCloseupHead.getRadius());
    
//     m_aldenCloseupBody.setSize(sf::Vector2f(limbThickness * 10.f, h * 0.5f));
//     m_aldenCloseupBody.setFillColor(aldenColor);
//     m_aldenCloseupBody.setPosition(w / 2.f - limbThickness * 5.f, m_aldenCloseupHead.getPosition().y + m_aldenCloseupHead.getRadius() * 2.f);

//     m_letterboxTop.setSize(sf::Vector2f(w, h * 0.1f));
//     m_letterboxTop.setFillColor(sf::Color::Black);
//     m_letterboxTop.setPosition(0, 0);

//     m_letterboxBottom.setSize(sf::Vector2f(w, h * 0.1f));
//     m_letterboxBottom.setFillColor(sf::Color::Black);
//     m_letterboxBottom.setPosition(0, h * 0.9f);
// }

#include "Scene1.h"
#include <string> 
#include <SFML/Audio.hpp> 

Scene1::Scene1(sf::RenderWindow& window) :
    m_window(window),
    m_nextState(GameState::Scene1_Intro),
    m_currentPart(CutscenePart::FadeIn)
{
    std::cout << "Entering Scene 1: The Kidnapping" << std::endl;

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font 'arial.ttf'." << std::endl;
    }

    // --- ADDED: Load all sounds ---
    std::cout << "Loading Scene 1 sounds..." << std::endl;
    std::vector<std::string> soundFiles = {
        "Sounds/Scene1/1.wav", "Sounds/Scene1/2.wav", "Sounds/Scene1/3.wav",
        "Sounds/Scene1/4.wav", "Sounds/Scene1/5.wav", "Sounds/Scene1/6.wav",
        "Sounds/Scene1/7.wav", "Sounds/Scene1/8.wav", "Sounds/Scene1/9.wav",
        "Sounds/Scene1/10.wav", "Sounds/Scene1/11.wav"
    };

    m_voiceBuffers.resize(soundFiles.size());
    for (size_t i = 0; i < soundFiles.size(); ++i) {
        if (!m_voiceBuffers[i].loadFromFile(soundFiles[i])) {
            std::cerr << "Error loading sound file: " << soundFiles[i] << std::endl;
        }
    }
    std::cout << "Scene 1 sounds loaded." << std::endl;
    // ----------------------------

    setupGraphics();
    m_partClock.restart();
}

void Scene1::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Cutscene skipped!" << std::endl;
            m_voiceSound.stop(); 
            m_nextState = GameState::Scene2_TumbangPreso;
        }
    }
}

void Scene1::update(sf::Time dt) {
    updateCutscene(dt);
}


void Scene1::updateCutscene(sf::Time dt) {
    float elapsedTime = m_partClock.getElapsedTime().asSeconds();

    switch (m_currentPart) {
    case CutscenePart::FadeIn:
        setSubtitle(L"Isang tahimik na hapon sa Barangay Park…");
        if (elapsedTime > 0.1f && m_voiceSound.getStatus() != sf::Sound::Playing) {
             m_voiceSound.setBuffer(m_voiceBuffers[0]);
             m_voiceSound.play();
        }
        
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 - (sf::Uint8)(elapsedTime / 1.5f * 255)));
        if (elapsedTime > 1.5f) { 
            m_currentPart = CutscenePart::Peaceful;
            m_partClock.restart();
        }
        break;

    case CutscenePart::Peaceful:
        // This is the 6-second pause for the Narrator's line
        if (elapsedTime > 6.0f) { 
            m_currentPart = CutscenePart::Dialogue_Yaya;
            m_voiceSound.setBuffer(m_voiceBuffers[1]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Yaya:
        setSubtitle(L"YayaDub: \"Alden, ang peaceful dito, ‘no?\""); 
        // --- FIX: Changed 3.0f to 6.0f ---
        if (elapsedTime > 6.0f) { 
            m_currentPart = CutscenePart::Dialogue_Alden;
            m_voiceSound.setBuffer(m_voiceBuffers[2]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Alden:
        setSubtitle(L"Alden: \"Oo… parang gusto ko nang tumigil ang oras kapag kasama ka.\"");
        // --- FIX: Changed 4.0f to 7.0f ---
        if (elapsedTime > 7.0f) { 
            m_currentPart = CutscenePart::YayaDisappears;
            m_partClock.restart();
        }
        break;

    case CutscenePart::YayaDisappears:
        setSubtitle(L""); 
        if (elapsedTime > 0.5f) { 
            m_currentPart = CutscenePart::ArjoAppears;
            m_voiceSound.setBuffer(m_voiceBuffers[3]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::ArjoAppears:
        setSubtitle(L"Arjo: \"Hindi puwedeng ganyan lang kadali, Alden!\""); 
        // --- FIX: Changed 3.0f to 6.0f ---
        if (elapsedTime > 6.0f) { 
            m_currentPart = CutscenePart::Dialogue_Alden_Arjo;
            m_voiceSound.setBuffer(m_voiceBuffers[4]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Alden_Arjo:
        setSubtitle(L"Alden: \"ARJO!? Anong ginagawa mo dito!?\""); 
        // --- FIX: Changed 3.0f to 6.0f ---
        if (elapsedTime > 6.0f) { 
            m_currentPart = CutscenePart::Dialogue_Arjo_Challenge;
            m_voiceSound.setBuffer(m_voiceBuffers[5]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Arjo_Challenge:
        setSubtitle(L"Arjo: \"Gusto mong makasama si YayaDub? Patunayan mo muna!\""); 
        // --- FIX: Changed 3.5f to 6.0f ---
        if (elapsedTime > 6.0f) { 
            m_currentPart = CutscenePart::Dialogue_Yaya_Help;
            m_voiceSound.setBuffer(m_voiceBuffers[6]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Yaya_Help:
        setSubtitle(L"YayaDub: \"Alden! Tulungan mo ‘ko!\"");
        // --- FIX: Changed 2.5f to 5.0f ---
        if (elapsedTime > 5.0f) { 
            m_currentPart = CutscenePart::Dialogue_Arjo_Games;
            m_voiceSound.setBuffer(m_voiceBuffers[7]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Arjo_Games:
        setSubtitle(L"Arjo: \"Kung tunay kang lalaki, tapusin mo ang mga laro ng barangay!\""); 
        // --- FIX: Changed 4.0f to 6.0f ---
        if (elapsedTime > 6.0f) { 
            m_currentPart = CutscenePart::Dialogue_Alden_Ano;
            m_voiceSound.setBuffer(m_voiceBuffers[8]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Alden_Ano:
        setSubtitle(L"Alden: \"Ano!?\""); 
        // --- FIX: Changed 1.5f to 4.0f ---
        if (elapsedTime > 4.0f) { 
            m_currentPart = CutscenePart::Dialogue_Arjo_TumbangPreso;
            m_voiceSound.setBuffer(m_voiceBuffers[9]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::Dialogue_Arjo_TumbangPreso:
        setSubtitle(L"Arjo: \"Simulan mo sa… TUMBANG PRESO!\""); 
        // --- FIX: Changed 3.5f to 7.0f ---
        if (elapsedTime > 7.0f) { 
            m_currentPart = CutscenePart::ArjoLeaves;
            m_partClock.restart();
        }
        break;

    case CutscenePart::ArjoLeaves:
        setSubtitle(L"");
        m_arjoHead.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        m_arjoBody.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        m_arjoArm1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        m_arjoArm2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        m_arjoLeg1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
        m_arjoLeg2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
        m_yayaDubKidnappedHead.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        m_yayaDubKidnappedBody.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        m_yayaDubKidnappedArm1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
        m_yayaDubKidnappedArm2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
        m_yayaDubKidnappedLeg1.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds()); 
        m_yayaDubKidnappedLeg2.move(150.f * dt.asSeconds(), -150.f * dt.asSeconds());
        if (elapsedTime > 2.0f) {
            m_currentPart = CutscenePart::AldenDetermined;
            // --- ADDED: Play sound 11 ---
            m_voiceSound.setBuffer(m_voiceBuffers[10]);
            m_voiceSound.play();
            m_partClock.restart();
        }
        break;

    case CutscenePart::AldenDetermined:
        setSubtitle(L"Alden: \"Tumbang Preso pala ha… sige! Para kay YayaDub, lalaban ako!\""); 
        // --- FIX: Changed 5.0f to 9.0f ---
        if (elapsedTime > 9.0f) { 
            m_currentPart = CutscenePart::FadeOut;
            m_partClock.restart();
        }
        break;

    case CutscenePart::FadeOut:
        setSubtitle(L"");
        m_fadeRect.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)(elapsedTime / 1.5f * 255))); // Fade to White
        if (elapsedTime > 1.5f) {
            m_nextState = GameState::Scene2_TumbangPreso;
        }
        break;
    }
}

void Scene1::draw(sf::RenderTarget& target) {
    target.clear(sf::Color::Black);

    if (m_currentPart < CutscenePart::ArjoAppears) {
        target.draw(m_parkSky);
        target.draw(m_parkGrass);
        target.draw(m_parkBenchLeg1);
        target.draw(m_parkBenchLeg2);
        target.draw(m_parkBenchSeat);
        
        target.draw(m_aldenHead);
        target.draw(m_aldenBody);
        target.draw(m_aldenArm1); 
        target.draw(m_aldenArm2); 
        target.draw(m_aldenLeg1);
        target.draw(m_aldenLeg2);

        if (m_currentPart < CutscenePart::YayaDisappears) {
            target.draw(m_yayaDubHead);
            target.draw(m_yayaDubBody);
            target.draw(m_yayaDubArm1); 
            target.draw(m_yayaDubArm2); 
            target.draw(m_yayaDubLeg1);
            target.draw(m_yayaDubLeg2);
        } else {
            target.draw(m_exclamationMark);
        }
    } else if (m_currentPart < CutscenePart::AldenDetermined) {
        target.draw(m_skyBg);
        target.draw(m_aldenHeadLookingUp); 
        
        target.draw(m_arjoHead);
        target.draw(m_arjoBody);
        target.draw(m_arjoArm1);
        target.draw(m_arjoArm2);
        target.draw(m_arjoLeg1); 
        target.draw(m_arjoLeg2);

        target.draw(m_yayaDubKidnappedHead);
        target.draw(m_yayaDubKidnappedBody);
        target.draw(m_yayaDubKidnappedArm1); 
        target.draw(m_yayaDubKidnappedArm2); 
        target.draw(m_yayaDubKidnappedLeg1); 
        target.draw(m_yayaDubKidnappedLeg2); 
    } else {
        target.draw(m_closeupBg);
        target.draw(m_aldenCloseupHead);
        target.draw(m_aldenCloseupBody);
        target.draw(m_letterboxTop);
        target.draw(m_letterboxBottom);
    }

    if (m_subtitleText.getString() != "") {
        target.draw(m_subtitleBackground);
        target.draw(m_subtitleText);
    }
    
    if (m_currentPart == CutscenePart::FadeIn || m_currentPart == CutscenePart::FadeOut) {
        target.draw(m_fadeRect);
    }
}

GameState Scene1::getNextState() {
    return m_nextState;
}

void Scene1::setSubtitle(const std::wstring& text) {
    m_subtitleText.setString(text);
    
    sf::FloatRect textRect = m_subtitleText.getLocalBounds();
    m_subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_subtitleText.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y * 0.85f);
    
    m_subtitleBackground.setSize(sf::Vector2f(textRect.width + 20, textRect.height + 20));
    m_subtitleBackground.setOrigin(m_subtitleBackground.getSize().x / 2.f, m_subtitleBackground.getSize().y / 2.f);
    m_subtitleBackground.setPosition(m_subtitleText.getPosition());
}

void Scene1::setupGraphics() {
    sf::Vector2u windowSize = m_window.getSize();
    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);

    m_subtitleText.setFont(m_font);
    m_subtitleText.setCharacterSize(24);
    m_subtitleText.setFillColor(sf::Color::White);
    
    m_subtitleBackground.setFillColor(sf::Color(0, 0, 0, 150)); 
    
    m_fadeRect.setSize(sf::Vector2f(w, h));
    m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

    sf::Color aldenColor = sf::Color::Blue;
    sf::Color yayaDubColor = sf::Color(255, 192, 203); 
    sf::Color arjoColor = sf::Color::Red;
    
    m_parkSky.setSize(sf::Vector2f(w, h * 0.7f));
    m_parkSky.setFillColor(sf::Color(135, 206, 235));
    m_parkGrass.setSize(sf::Vector2f(w, h * 0.3f));
    m_parkGrass.setFillColor(sf::Color(34, 139, 34));
    m_parkGrass.setPosition(0, h * 0.7f);

    float benchWidth = w * 0.4f;
    float benchHeight = h * 0.05f;
    float benchX = (w - benchWidth) / 2.0f;
    float benchY = h * 0.75f;
    m_parkBenchSeat.setSize(sf::Vector2f(benchWidth, benchHeight));
    m_parkBenchSeat.setFillColor(sf::Color(139, 69, 19));
    m_parkBenchSeat.setPosition(benchX, benchY);
    m_parkBenchLeg1.setSize(sf::Vector2f(w * 0.02f, h * 0.1f));
    m_parkBenchLeg1.setFillColor(sf::Color(101, 33, 0));
    m_parkBenchLeg1.setPosition(benchX + benchWidth * 0.1f, benchY + benchHeight);
    m_parkBenchLeg2.setSize(sf::Vector2f(w * 0.02f, h * 0.1f));
    m_parkBenchLeg2.setFillColor(sf::Color(101, 33, 0));
    m_parkBenchLeg2.setPosition(benchX + benchWidth * 0.8f, benchY + benchHeight);

    float headRadius = 20.f;
    float bodyHeight = 70.f;
    float limbLength = 40.f; 
    float limbThickness = 5.f;
    sf::Vector2f aldenPos(benchX + benchWidth * 0.3f, benchY - bodyHeight - headRadius * 2);
    m_aldenHead.setRadius(headRadius);
    m_aldenHead.setFillColor(aldenColor);
    m_aldenHead.setPosition(aldenPos);
    m_aldenBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
    m_aldenBody.setFillColor(aldenColor);
    m_aldenBody.setPosition(aldenPos.x + headRadius - limbThickness / 2.f, aldenPos.y + headRadius * 2);

    m_aldenArm1.setSize(sf::Vector2f(limbLength, limbThickness));
    m_aldenArm1.setFillColor(aldenColor);
    m_aldenArm1.setPosition(m_aldenBody.getPosition().x, m_aldenBody.getPosition().y + bodyHeight * 0.2f);
    m_aldenArm1.setRotation(-20); 

    m_aldenArm2.setSize(sf::Vector2f(limbLength, limbThickness));
    m_aldenArm2.setFillColor(aldenColor);
    m_aldenArm2.setPosition(m_aldenBody.getPosition().x - (limbLength - limbThickness), m_aldenBody.getPosition().y + bodyHeight * 0.2f);
    m_aldenArm2.setRotation(20); 
    
    m_aldenLeg1.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
    m_aldenLeg1.setFillColor(aldenColor);
    m_aldenLeg1.setPosition(m_aldenBody.getPosition().x, m_aldenBody.getPosition().y + bodyHeight);
    m_aldenLeg2.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
    m_aldenLeg2.setFillColor(aldenColor);
    m_aldenLeg2.setPosition(m_aldenBody.getPosition().x + limbThickness, m_aldenBody.getPosition().y + bodyHeight);

    sf::Vector2f yayaDubPos(benchX + benchWidth * 0.7f - headRadius * 2, benchY - bodyHeight - headRadius * 2);
    m_yayaDubHead.setRadius(headRadius);
    m_yayaDubHead.setFillColor(yayaDubColor);
    m_yayaDubHead.setPosition(yayaDubPos);
    m_yayaDubBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
    m_yayaDubBody.setFillColor(yayaDubColor);
    m_yayaDubBody.setPosition(yayaDubPos.x + headRadius - limbThickness / 2.f, yayaDubPos.y + headRadius * 2);

    m_yayaDubArm1.setSize(sf::Vector2f(limbLength, limbThickness));
    m_yayaDubArm1.setFillColor(yayaDubColor);
    m_yayaDubArm1.setPosition(m_yayaDubBody.getPosition().x, m_yayaDubBody.getPosition().y + bodyHeight * 0.2f);
    m_yayaDubArm1.setRotation(-20);

    m_yayaDubArm2.setSize(sf::Vector2f(limbLength, limbThickness));
    m_yayaDubArm2.setFillColor(yayaDubColor);
    m_yayaDubArm2.setPosition(m_yayaDubBody.getPosition().x - (limbLength - limbThickness), m_yayaDubBody.getPosition().y + bodyHeight * 0.2f);
    m_yayaDubArm2.setRotation(20);
    
    m_yayaDubLeg1.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
    m_yayaDubLeg1.setFillColor(yayaDubColor);
    m_yayaDubLeg1.setPosition(m_yayaDubBody.getPosition().x, m_yayaDubBody.getPosition().y + bodyHeight);
    m_yayaDubLeg2.setSize(sf::Vector2f(limbThickness, bodyHeight * 0.8f));
    m_yayaDubLeg2.setFillColor(yayaDubColor);
    m_yayaDubLeg2.setPosition(m_yayaDubBody.getPosition().x + limbThickness, m_yayaDubBody.getPosition().y + bodyHeight);

    m_exclamationMark.setFont(m_font);
    m_exclamationMark.setString("!");
    m_exclamationMark.setCharacterSize(48);
    m_exclamationMark.setFillColor(sf::Color::Black);
    m_exclamationMark.setPosition(aldenPos.x + headRadius, aldenPos.y - 50);

    m_skyBg.setSize(sf::Vector2f(w, h));
    m_skyBg.setFillColor(sf::Color(135, 206, 235));

    m_aldenHeadLookingUp.setRadius(headRadius * 1.5f);
    m_aldenHeadLookingUp.setFillColor(aldenColor);
    m_aldenHeadLookingUp.setPosition(w * 0.2f, h * 0.7f);

    m_aldenHeadLookingUp.setRadius(w * 0.3f); 
    m_aldenHeadLookingUp.setFillColor(aldenColor);
    m_aldenHeadLookingUp.setPosition(-w * 0.1f, h * 0.4f); 

    sf::Vector2f arjoPos(w * 0.6f, h * 0.3f);
    m_arjoHead.setRadius(headRadius * 1.2f);
    m_arjoHead.setFillColor(arjoColor);
    m_arjoHead.setPosition(arjoPos);
    m_arjoBody.setSize(sf::Vector2f(limbThickness * 1.5f, bodyHeight * 1.2f));
    m_arjoBody.setFillColor(arjoColor);
    m_arjoBody.setPosition(arjoPos.x + headRadius * 1.2f - limbThickness * 1.5f / 2.f, arjoPos.y + headRadius * 2.4f);
    m_arjoArm1.setSize(sf::Vector2f(bodyHeight * 0.6f, limbThickness * 1.5f));
    m_arjoArm1.setFillColor(arjoColor);
    m_arjoArm1.setPosition(m_arjoBody.getPosition());
    m_arjoArm2.setSize(sf::Vector2f(bodyHeight * 0.6f, limbThickness * 1.5f));
    m_arjoArm2.setFillColor(arjoColor);
    m_arjoArm2.setPosition(m_arjoBody.getPosition().x, m_arjoBody.getPosition().y + 10.f);

    m_arjoLeg1.setSize(sf::Vector2f(limbThickness * 1.5f, bodyHeight * 0.8f));
    m_arjoLeg1.setFillColor(arjoColor);
    m_arjoLeg1.setPosition(m_arjoBody.getPosition().x, m_arjoBody.getPosition().y + bodyHeight * 1.2f);
    m_arjoLeg1.setRotation(-10.f);
    m_arjoLeg2.setSize(sf::Vector2f(limbThickness * 1.5f, bodyHeight * 0.8f));
    m_arjoLeg2.setFillColor(arjoColor);
    m_arjoLeg2.setPosition(m_arjoBody.getPosition().x + limbThickness, m_arjoBody.getPosition().y + bodyHeight * 1.2f);
    m_arjoLeg2.setRotation(10.f);
    
    m_yayaDubKidnappedHead.setRadius(headRadius);
    m_yayaDubKidnappedHead.setFillColor(yayaDubColor);
    m_yayaDubKidnappedHead.setPosition(arjoPos.x + 50.f, arjoPos.y + 20.f);
    m_yayaDubKidnappedBody.setSize(sf::Vector2f(limbThickness, bodyHeight));
    m_yayaDubKidnappedBody.setFillColor(yayaDubColor);
    m_yayaDubKidnappedBody.setPosition(m_yayaDubKidnappedHead.getPosition().x + headRadius - limbThickness / 2.f, m_yayaDubKidnappedHead.getPosition().y + headRadius * 2);

    m_yayaDubKidnappedArm1.setSize(sf::Vector2f(limbLength * 0.8f, limbThickness));
    m_yayaDubKidnappedArm1.setFillColor(yayaDubColor);
    m_yayaDubKidnappedArm1.setPosition(m_yayaDubKidnappedBody.getPosition().x, m_yayaDubKidnappedBody.getPosition().y + 5.f);
    m_yayaDubKidnappedArm1.setRotation(20.f); 
    m_yayaDubKidnappedArm2.setSize(sf::Vector2f(limbLength * 0.8f, limbThickness));
    m_yayaDubKidnappedArm2.setFillColor(yayaDubColor);
    m_yayaDubKidnappedArm2.setPosition(m_yayaDubKidnappedBody.getPosition().x, m_yayaDubKidnappedBody.getPosition().y + 10.f);
    m_yayaDubKidnappedArm2.setRotation(10.f); 

    m_yayaDubKidnappedLeg1.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
    m_yayaDubKidnappedLeg1.setFillColor(yayaDubColor);
    m_yayaDubKidnappedLeg1.setPosition(m_yayaDubKidnappedBody.getPosition().x, m_yayaDubKidnappedBody.getPosition().y + bodyHeight);
    m_yayaDubKidnappedLeg1.setRotation(-5.f); 
    m_yayaDubKidnappedLeg2.setSize(sf::Vector2f(limbThickness, limbLength * 0.8f));
    m_yayaDubKidnappedLeg2.setFillColor(yayaDubColor);
    m_yayaDubKidnappedLeg2.setPosition(m_yayaDubKidnappedBody.getPosition().x + limbThickness, m_yayaDubKidnappedBody.getPosition().y + bodyHeight);
    m_yayaDubKidnappedLeg2.setRotation(5.f); 
    
    m_closeupBg.setSize(sf::Vector2f(w, h));
    m_closeupBg.setFillColor(sf::Color(135, 206, 235));
    
    m_aldenCloseupHead.setRadius(w * 0.2f);
    m_aldenCloseupHead.setFillColor(aldenColor);
    m_aldenCloseupHead.setPosition(w / 2.f - m_aldenCloseupHead.getRadius(), h / 2.f - m_aldenCloseupHead.getRadius());
    
    m_aldenCloseupBody.setSize(sf::Vector2f(limbThickness * 10.f, h * 0.5f));
    m_aldenCloseupBody.setFillColor(aldenColor);
    m_aldenCloseupBody.setPosition(w / 2.f - limbThickness * 5.f, m_aldenCloseupHead.getPosition().y + m_aldenCloseupHead.getRadius() * 2.f);

    m_letterboxTop.setSize(sf::Vector2f(w, h * 0.1f));
    m_letterboxTop.setFillColor(sf::Color::Black);
    m_letterboxTop.setPosition(0, 0);

    m_letterboxBottom.setSize(sf::Vector2f(w, h * 0.1f));
    m_letterboxBottom.setFillColor(sf::Color::Black);
    m_letterboxBottom.setPosition(0, h * 0.9f);
}