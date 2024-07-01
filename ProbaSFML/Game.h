#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Pivo.h"

class Game {
public:
    Game(sf::RenderWindow& window);
    void run();
    void processEvents(float deltaTime);
    void update(float deltaTime);
    void render();
    void spawnPivo(float deltaTime);
    void checkCollisions();
    void checkGameEnd();
    void removeHeart();
    void setupLevel(int level);
    void updateLevel();
    void resetGame();
    void handleEnterPressed();
    void handleMouseClick();
    bool isGameOver();
    void updateBeerGlass();
protected:
    sf::RenderWindow& window;
    sf::Texture gajbaTexture;
    sf::Sprite gajba;
    sf::Texture pivoTexture;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Color backgroundColor;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text newGameText;
    sf::SoundBuffer beerCatchBuffer;
    sf::Sound beerCatchSound;
    sf::SoundBuffer beerMissBuffer;
    sf::Sound beerMissSound;
    sf::SoundBuffer tocenjeBuffer;
    sf::Sound tocenjeZvuk;
    sf::Music music;
    sf::Texture heartTexture;
    std::vector<sf::Sprite> hearts;
    int brojSkupljenihPiva;
    int brojPromaknutaPiva;
    int maxPromaknutaPiva;
    int trenutniNivo;
    float brzinaPadaPiva;
    std::vector<Pivo> padajucaPiva;
    std::vector<sf::Texture> beerGlassTextures;
    sf::Sprite beerGlassSprite;
    sf::Text levelText;

};
