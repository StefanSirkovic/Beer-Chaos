#include "Pivo.h"


Pivo::Pivo(sf::Texture& texture, float x, float y, float fallSpeed)
    : speed(fallSpeed)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    position = sf::Vector2f(x, y);
}

bool Pivo::operator==(const Pivo& other) const {
    return (position == other.position);
}

void Pivo::update(float deltaTime) {
    position.y += speed * deltaTime;
    sprite.setPosition(position);
}

sf::FloatRect Pivo::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

bool Pivo::isOffScreen() const {
    return position.y > 600.0f;
}
