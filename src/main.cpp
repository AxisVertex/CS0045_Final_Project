#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>    
#include <cstdlib>   
#include <ctime>     

#include "Scene.h"
#include "MainMenu.h" 
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h" 
#include "Scene6.h"
#include "Scene7.h" 

#define GLEW_STATIC
#include <GL/glew.h>

int main() {
    // --- Window Setup ---
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Outdoor Quest: The YayaDub Rescue");
    window.setFramerateLimit(60);

    // --- GLEW Initialization ---
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
        return -1;
    }
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    // --- Random Seed ---
    srand(static_cast<unsigned>(time(0)));

    // --- Game State Machine ---
    GameState currentState = GameState::MainMenu; 
    std::unique_ptr<Scene> currentScene = std::make_unique<MainMenu>(window); 
    

    sf::Clock deltaClock; 

    // --- Main GameLoop ---
    while (currentState != GameState::Exit) {
        
        sf::Time dt = deltaClock.restart();

        // --- Event Handling ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                currentState = GameState::Exit;
            }
            currentScene->handleInput(event);
        }

        // --- Update ---
        currentScene->update(dt);

        // --- State Transition Check ---
        GameState next = currentScene->getNextState();
        if (next != currentState) {
            currentState = next;
            
            switch (currentState) {
                case GameState::MainMenu:
                    std::cout << "Transitioning to Main Menu..." << std::endl;
                    currentScene = std::make_unique<MainMenu>(window);
                    break;
                case GameState::Scene1_Intro:
                    std::cout << "Transitioning to Scene 1 (Intro)..." << std::endl;
                    currentScene = std::make_unique<Scene1>(window);
                    break;
                case GameState::Scene2_TumbangPreso:
                    std::cout << "Transitioning to Scene 2 (Tumbang Preso)..." << std::endl;
                    currentScene = std::make_unique<Scene2>(window);
                    break;
                case GameState::Scene3_HabolHabulan:
                    std::cout << "Transitioning to Scene 3 (Habol-Habulan)..." << std::endl;
                    currentScene = std::make_unique<Scene3>(window);
                    break;
                case GameState::Scene4_Patintero:
                    std::cout << "Transitioning to Scene 4 (Patintero)..." << std::endl;
                    currentScene = std::make_unique<Scene4>(window);
                    break;
                case GameState::Scene5_Cutscene2: 
                    std::cout << "Transitioning to Scene 5 (Cutscene)..." << std::endl;
                    currentScene = std::make_unique<Scene5>(window);
                    break;
                case GameState::Scene6_SipaShowdown:
                    std::cout << "Transitioning to Scene 6 (Sipa Showdown)..." << std::endl;
                    currentScene = std::make_unique<Scene6>(window); 
                    break;
                case GameState::Scene7_Resolution: 
                    std::cout << "Transitioning to Scene 7 (Resolution)..." << std::endl;
                    currentScene = std::make_unique<Scene7>(window); 
                    break;
                case GameState::GameOver:
                    std::cout << "Game Over! Returning to Main Menu." << std::endl;
                    currentState = GameState::MainMenu; // Go back to Main Menu
                    currentScene = std::make_unique<MainMenu>(window);
                    break;
                case GameState::Exit:
                    std::cout << "Exiting game..." << std::endl;
                    break;
                default:
                    std::cout << "Unknown state! Exiting." << std::endl;
                    currentState = GameState::Exit;
                    break;
            }
        }

        // --- Draw ---
        window.clear(sf::Color::Black);
        currentScene->draw(window);
        window.display();
    }

    std::cout << "Game closed." << std::endl;
    return 0;
}