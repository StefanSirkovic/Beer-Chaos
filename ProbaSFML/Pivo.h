#pragma once
#ifndef PIVO_H
#define PIVO_H

#include <SFML/Graphics.hpp>

struct Pivo {
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;

    Pivo(sf::Texture& texture, float x, float y, float fallSpeed);
    bool operator==(const Pivo& other) const;
    void update(float deltaTime);
    sf::FloatRect getGlobalBounds() const;
    bool isOffScreen() const;
};

#endif // PIVO_H


