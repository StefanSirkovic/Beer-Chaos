#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }
    void addPlayAgain();
    void removePlayAgain();
    void setBackground(const std::string& filename);
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[4];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int menuItems;
    int maxItems;
    sf::Text naslov;

    static const int MAX_NUMBER_OF_ITEMS = 4; // Definisanje MAX_NUMBER_OF_ITEMS
};

#endif
