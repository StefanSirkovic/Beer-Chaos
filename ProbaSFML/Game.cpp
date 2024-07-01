#include "Game.h"
#include <iostream>

const float PlayerSpeed = 600.0f; // Brzina kretanja gajbe
const float GajbaWidth = 100.0f;  // Sirina gajbe, treba da odgovara sirini teksture

Game::Game(sf::RenderWindow& window)
    : window(window), brojSkupljenihPiva(0), brojPromaknutaPiva(0), maxPromaknutaPiva(3), trenutniNivo(1), brzinaPadaPiva(500.0f) {
    backgroundColor = sf::Color(255, 228, 128);
    if (!gajbaTexture.loadFromFile("gajba.png")) {
        std::cerr << "Failed to load gajba.png" << std::endl;
        exit(1);
    }
    gajba.setTexture(gajbaTexture);
    gajba.setPosition(400.0f, 500.0f);

    if (!pivoTexture.loadFromFile("beer.png")) {
        std::cerr << "Failed to load beer.png" << std::endl;
        exit(1);
    }

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load arial.ttf" << std::endl;
        exit(1);
    }
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(1000.0f, 20.0f);

    if (!heartTexture.loadFromFile("srce.png")) {
        std::cerr << "Failed to load srce.png" << std::endl;
        exit(1);
    }

    // Postavljanje srca u gornji desni ugao
    for (int i = 0; i < maxPromaknutaPiva; ++i) {
        sf::Sprite heart(heartTexture);
        heart.setPosition(1250.0f + i * 40.0f, 20.0f);
        hearts.push_back(heart);
    }

    // Učitavanje zvuka
    if (!beerCatchBuffer.loadFromFile("beer_catch.mp3")) {
        std::cerr << "Failed to load beer_catch.mp3" << std::endl;
        exit(1);
    }
    beerCatchSound.setBuffer(beerCatchBuffer);

    if (!beerMissBuffer.loadFromFile("beer_miss.mp3")) {
        std::cerr << "Failed to load beer_miss.mp3" << std::endl;
        exit(1);
    }
    beerMissSound.setBuffer(beerMissBuffer);

    if (!tocenjeBuffer.loadFromFile("tocenje.mp3")) {
        std::cerr << "Failed to load tocenje.mp3" << std::endl;
        exit(1);
    }
    tocenjeZvuk.setBuffer(tocenjeBuffer);

    if (!music.openFromFile("muzika.mp3")) {
        std::cerr << "Failed to open muzika.mp3" << std::endl;
        exit(1);
    }
    music.play();
 
    

    // Učitavanje tekstura za čašu piva
    for (int i = 0; i <= 4; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("beer_glass_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load beer_glass_" << i << ".png" << std::endl;
            exit(1);
        }
        beerGlassTextures.push_back(texture);
    }

    // Inicijalizacija beerGlassSprite
    beerGlassSprite.setTexture(beerGlassTextures[0]);
    beerGlassSprite.setPosition(1300.0f, 100.0f); // Postavite poziciju po želji

    levelText.setFont(font);
    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::Black);
    levelText.setPosition(50.0f, 50.0f);

    setupLevel(trenutniNivo);
}

void Game::run() {

    sf::Clock clock;
    bool isGameOver = false;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        if (!isGameOver) {
            processEvents(deltaTime);
            update(deltaTime);
            isGameOver = (brojPromaknutaPiva >= maxPromaknutaPiva || brojSkupljenihPiva >= 100);
        }

        render();

        if (isGameOver) {
            sf::sleep(sf::seconds(4));
            sf::Clock gameOverClock;
            bool exitGame = false;

            while (!exitGame && window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        
                    }
                    else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                        exitGame = true;
                    }
                }

                // Ako je prošlo 5 sekundi, izađi iz igre
                if (gameOverClock.getElapsedTime().asSeconds() >= 0.1f) {
                    music.stop();
                    exit(0);
                }

                // Ažuriranje ekrana (prazno renderovanje)
                window.clear(sf::Color::White);
                window.display();
            }

            // Ako je pritisnut neki taster ili kliknuto mišem, resetuj igru
            resetGame(); // Resetujemo igru ako je završena
            isGameOver = false; // Resetujemo isGameOver kako bi nova igra mogla da počne
        }
    }
}

void Game::processEvents(float deltaTime) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Enter) {
                handleEnterPressed(); // Pozivamo funkciju za pritisak na Enter
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(); // Pozivamo funkciju za klik mišem
            }
            break;
        default:
            break;
        }
    }

    // Obrada tastature za pomeranje gajbe
    float gajbaSpeed = PlayerSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (gajba.getPosition().x - gajbaSpeed > 0) {
            gajba.move(-gajbaSpeed, 0.0f);
        }
        else {
            gajba.setPosition(0, gajba.getPosition().y);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (gajba.getPosition().x + gajba.getGlobalBounds().width + gajbaSpeed < window.getSize().x) {
            gajba.move(gajbaSpeed, 0.0f);
        }
        else {
            gajba.setPosition(window.getSize().x - gajba.getGlobalBounds().width, gajba.getPosition().y);
        }
    }
}

void Game::update(float deltaTime) {
    spawnPivo(deltaTime);
    checkCollisions();
    checkGameEnd();
    updateLevel();

    // Ažuriranje pozicija piva
    for (auto& pivo : padajucaPiva) {
        pivo.update(deltaTime);
    }

    // Ažuriranje teksta za skor
    scoreText.setString("Broj piva: " + std::to_string(brojSkupljenihPiva));

    // Ažuriranje srca
    while (hearts.size() > maxPromaknutaPiva - brojPromaknutaPiva) {
        removeHeart();
    }
}

void Game::render() {
    window.clear(backgroundColor);
    window.draw(gajba);
    for (auto& pivo : padajucaPiva) {
        window.draw(pivo.sprite);
    }

    // Crta srca
    for (auto& heart : hearts) {
        window.draw(heart);
    }

    // Crta tekst za skor
    window.draw(scoreText);

    // Crta tekst za nivo
    window.draw(levelText);

    // Crta čašu piva
    window.draw(beerGlassSprite);

    if (brojPromaknutaPiva >= maxPromaknutaPiva || brojSkupljenihPiva>=100) {
        window.draw(gameOverText);
        window.draw(newGameText);
    }
    
    window.display();
}

void Game::spawnPivo(float deltaTime) {
    static float timer = 0.0f;
    timer += deltaTime;
    float spawnInterval = 1.0f + 1.0f * (0.3f * (float)trenutniNivo+0.75);
    if (timer > 1.5f / spawnInterval) { // Brže padanje sa većim nivoom
        float x = static_cast<float>(rand() % (window.getSize().x - static_cast<int>(pivoTexture.getSize().x)));
        Pivo pivo(pivoTexture, x, 0.0f, brzinaPadaPiva);
        padajucaPiva.push_back(pivo);
        timer = 0.0f;
    }
}

void Game::checkCollisions() {
    for (auto it = padajucaPiva.begin(); it != padajucaPiva.end(); ) {
        if (it->sprite.getGlobalBounds().intersects(gajba.getGlobalBounds())) {
            brojSkupljenihPiva+=10;
            it = padajucaPiva.erase(it);
            beerCatchSound.play();
        }
        else if (it->sprite.getPosition().y > 720) {
            brojPromaknutaPiva++;
            it = padajucaPiva.erase(it);
            beerMissSound.play();
        }
        else {
            ++it;
        }
    }
}

void Game::checkGameEnd() {
    if ((brojPromaknutaPiva >= maxPromaknutaPiva) || brojSkupljenihPiva>=100) {
        music.stop();
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(70);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("Igra je zavrsena!");
        gameOverText.setPosition(500.0f, 350.0f);
        newGameText.setFont(font);
        newGameText.setCharacterSize(30);
        newGameText.setFillColor(sf::Color::Black);
        newGameText.setString("Pritisnite Enter za novu igru.");
        newGameText.setPosition(500.0f, 450.0f);
    }
}

void Game::removeHeart() {
    if (!hearts.empty()) {
        hearts.pop_back();
    }
}

void Game::setupLevel(int level) {
    trenutniNivo = level;
    brzinaPadaPiva = 200.0f + 50.0f * level;
        updateBeerGlass();
    
    levelText.setString("Nivo: " + std::to_string(trenutniNivo));
}

void Game::updateLevel() {
    if (brojSkupljenihPiva >= trenutniNivo * 25) {
        setupLevel(++trenutniNivo);
        tocenjeZvuk.play();
    }
    
}

void Game::resetGame() {
    music.stop();
    brojSkupljenihPiva = 0;
    brojPromaknutaPiva = 0;
    trenutniNivo = 1;
    brzinaPadaPiva = 500.0f; // Vratimo brzinu pada piva na početnu vrednost
    padajucaPiva.clear();
    hearts.clear();
    
    // Ponovno postavljanje srca u gornji desni ugao
    for (int i = 0; i < maxPromaknutaPiva; ++i) {
        sf::Sprite heart(heartTexture);
        heart.setPosition(1250.0f + i * 40.0f, 20.0f);
        hearts.push_back(heart);
    }
    music.play();
    setupLevel(trenutniNivo);
}

void Game::handleEnterPressed() {
    if (brojPromaknutaPiva >= maxPromaknutaPiva) {
        resetGame(); // Resetujemo igru ako je završena
    }
}

void Game::handleMouseClick() {
    if (brojPromaknutaPiva >= maxPromaknutaPiva) {
        resetGame(); // Resetujemo igru ako je završena
    }
}

bool Game::isGameOver() {
    return brojPromaknutaPiva >= maxPromaknutaPiva;
}

void Game::updateBeerGlass() {

    
    int textureIndex = std::min(trenutniNivo -1, static_cast<int>(beerGlassTextures.size()) -1);
    beerGlassSprite.setTexture(beerGlassTextures[textureIndex]);
}
