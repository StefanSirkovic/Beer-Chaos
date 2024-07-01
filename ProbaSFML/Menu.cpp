#include "Menu.h"
#include <iostream>
Menu::Menu(float width, float height) : menuItems(2), maxItems(3) { // Povećan maxItems zbog "Play Again"
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }

    naslov.setFont(font);
    naslov.setFillColor(sf::Color::White);
    naslov.setString("Pivski Haos");
    naslov.setPosition(sf::Vector2f(width / 3.1, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.1));
    naslov.setCharacterSize(100);

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Black);
    menu[0].setString("Start");
    menu[0].setPosition(sf::Vector2f(width / 2.17, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));
    menu[0].setCharacterSize(55);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(width / 2.08, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.5));
    menu[1].setCharacterSize(35);
    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        window.draw(backgroundSprite);
    }

    for (int i = 0; i < menuItems; i++) {
        window.draw(menu[i]);
        window.draw(naslov);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::addPlayAgain() {
    if (menuItems < maxItems) {
        menu[2].setFont(font);
        menu[2].setFillColor(sf::Color::White);
        menu[2].setString("Play Again");
        menu[2].setPosition(sf::Vector2f(400.0f, 360.0f));
        menuItems++;
    }
}

void Menu::removePlayAgain() {
    if (menuItems == maxItems) {
        menuItems--;
        if (selectedItemIndex >= menuItems) {
            selectedItemIndex = menuItems - 1;
        }
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::setBackground(const std::string& filename) {
    if (backgroundTexture.loadFromFile("background.png")) {
        backgroundSprite.setTexture(backgroundTexture);
    }
    else {
        std::cerr << "Failed to load background image: " << filename << std::endl;
    }
}
