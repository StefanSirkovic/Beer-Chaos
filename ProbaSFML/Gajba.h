#ifndef GAJBA_H
#define GAJBA_H

#include <SFML/Graphics.hpp>

class Gajba : public sf::Drawable {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Gajba(float x, float y);
    virtual void moveLeft(float deltaTime);
    virtual void moveRight(float deltaTime);
    virtual sf::FloatRect getGlobalBounds() const;

    // Implementacija sf::Drawable interfejsa
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif 
