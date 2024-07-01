#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 900), "Pivski Haos");
    Menu menu(window.getSize().x, window.getSize().y);
    menu.setBackground("background.png"); // Postavljanje pozadinske slike
    sf::Image icon;
    if (!icon.loadFromFile("ikonica.png")) {
        std::cerr << "Failed to load icon" << std::endl;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    bool gameRunning = false;
    Game* game = nullptr;

    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!gameRunning) {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        switch (menu.getPressedItem()) {
                        case 0: // Play
                            game = new Game(window);
                            gameRunning = true;
                            menu.removePlayAgain();
                            break;
                        case 1: // Exit
                            window.close();
                            break;
                        case 2: // Play Again
                            game->resetGame();
                            gameRunning = true;
                            menu.removePlayAgain();
                            break;
                        }
                    }
                }
            }
        }

        if (gameRunning) {
            game->run();
            gameRunning = false;
            menu.addPlayAgain();
        }
        else {
            window.clear();
            menu.draw(window);
            window.display();
        }
    }

    delete game;
    return 0;
}
