#include "Gajba.h"
#include <iostream>

const float PlayerSpeed = 9000.0f;

Gajba::Gajba(float x, float y) {
    if (!texture.loadFromFile("gajba.jpg")) {
        std::cerr << "Failed to load gajba.png" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Gajba::moveLeft(float deltaTime) {
    sprite.move(-PlayerSpeed * deltaTime, 0.0f);
}

void Gajba::moveRight(float deltaTime) {
    sprite.move(PlayerSpeed * deltaTime, 0.0f);
}

sf::FloatRect Gajba::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Gajba::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
