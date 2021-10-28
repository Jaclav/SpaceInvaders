#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Bullet.hpp"
#include "Enemy.hpp"

inline void message(sf::RenderWindow &window, std::wstring message) {
    sf::Font font;
    sf::Event event;
    font.loadFromFile("res/Ubuntu-L.ttf");
    sf::Text text(message, font);
    text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2, (window.getSize().y - text.getLocalBounds().height) / 2);

    while(window.isOpen()) {
        window.draw(text);
        while(window.pollEvent(event)) {
            if(event.type == event.Closed) {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                return;
        }
        window.display();
    }
}

int main() {
begin:
    srand(clock());
    sf::RenderWindow window(sf::VideoMode(600, 800), "Space Invaders");
    window.setFramerateLimit(30);
    window.setPosition(sf::Vector2i(300, 0));

    sf::Event event;

    sf::Texture playerT;
    sf::Sprite player;
    playerT.loadFromFile("res/spaceship.png");
    player.setTexture(playerT);
    player.setPosition(window.getSize().x / 2, window.getSize().y - player.getLocalBounds().height - 20);
    std::vector<Bullet> bullets;

    std::vector<Enemy> enemies;
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 7; i++) {
            enemies.push_back(Enemy(sf::Vector2f(i * 70, j * 70)));
        }
    }

    bool released = true;
    sf::Clock cooldown;

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == event.Closed) {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0) {
                player.move(-20, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x + player.getLocalBounds().width + 5 < window.getSize().x) {
                player.move(20, 0);
            }
            if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && cooldown.getElapsedTime() > sf::milliseconds(250)) {
                released = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && released) {
                released = false;
                bullets.push_back(Bullet(sf::Vector2f(player.getPosition().x + player.getLocalBounds().width / 2, player.getPosition().y - 20), -8));
                cooldown.restart();
            }
        }

        /////draw
        window.clear();

		//if any enemy didn't left
        if(!enemies.size()) {
            message(window, L"Wygrałeś!\nWciśnij ENTER by kontynuować");
            if(window.isOpen())
                goto begin;
        }

        //enemies
        for(auto enemy = enemies.begin(); enemy < enemies.end(); *enemy++) {
            window.draw(*enemy);
            //check is enemy shot
            for(auto bullet = bullets.begin(); bullet < bullets.end(); *bullet++) {
                if(enemy->getGlobalBounds().contains(bullet->getPosition())) {
                    if(bullet->getVelocity() < 0)
                        enemies.erase(enemy);
                    bullets.erase(bullet);
                }
            }
            //shoot
            if(rand() % 80 == 0) {
                bullets.push_back(Bullet(sf::Vector2f(enemy->getPosition().x + enemy->getGlobalBounds().width / 2,
                                                      enemy->getPosition().y + enemy->getGlobalBounds().height + 10), 5));
            }
        }

        window.draw(player);

        //bullets
        for(auto i = bullets.begin(); i < bullets.end(); *i++) {
            window.draw(*i);
			//if exceeded screen
            if(i->getPosition().y < 0 || i->getPosition().y + 30 > window.getSize().y) {
                bullets.erase(i);
            }
            if(player.getGlobalBounds().contains(i->getPosition())) {
                //loose
                message(window, L"Przegrałeś!\nWciśnij ENTER by kontynuować");
                if(window.isOpen())
                    goto begin;
            }
        }

        window.display();
    }
}