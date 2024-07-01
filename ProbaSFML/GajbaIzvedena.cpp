#include "GajbaIzvedena.h"

const float PlayerSpeed = 9000.0f;

GajbaIzvedena::GajbaIzvedena(float x, float y)
    : Gajba(x, y) {
    // Možete dodati dodatne inicijalizacije ako su potrebne
}

void GajbaIzvedena::moveLeft(float deltaTime) {
    sprite.move(-PlayerSpeed * deltaTime, 0.0f);
    // Dodajte dodatnu logiku ili izmene ako je potrebno
}

void GajbaIzvedena::moveRight(float deltaTime) {
    sprite.move(PlayerSpeed * deltaTime, 0.0f);
    // Dodajte dodatnu logiku ili izmene ako je potrebno
}

sf::FloatRect GajbaIzvedena::getGlobalBounds() const {
    return sprite.getGlobalBounds();
    // Implementacija granica može se promeniti ili proširiti po potrebi
}
