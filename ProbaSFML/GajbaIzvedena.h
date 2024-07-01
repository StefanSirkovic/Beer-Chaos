#pragma once
#ifndef FANCY_GAJBA_H
#define FANCY_GAJBA_H

#include "Gajba.h"

class GajbaIzvedena : public Gajba {
public:
    GajbaIzvedena(float x, float y);

    // Predefinisane virtualne metode iz Gajba klase
    virtual void moveLeft(float deltaTime) override;
    virtual void moveRight(float deltaTime) override;
    virtual sf::FloatRect getGlobalBounds() const override;
};

#endif 


