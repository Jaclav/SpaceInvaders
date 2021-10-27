#include "Enemy.hpp"

sf::Texture Enemy::texture;
Enemy::Side Enemy::side = Enemy::Side::Right;

Enemy::Enemy(sf::Vector2f position) {
    if(sprite.getTexture() == nullptr) {
        texture.loadFromFile("res/alien.png");
        sprite.setTexture(texture);
    }
    sf::Color colors[] = {sf::Color::Magenta, sf::Color::Cyan, sf::Color::Green};
    sprite.setPosition(position);
    sprite.setColor(colors[random() % 3]);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(side == Right) {
        sprite.move(velocity, 0);
        if(sprite.getPosition().x + sprite.getLocalBounds().width + 10 >= target.getSize().x) {
            side = Side::Left;
        }
    }
    else {
        sprite.move(-velocity, 0);
        if(sprite.getPosition().x <= 5) {
            side = Side::Right;
            sprite.move(2 * velocity, 0);
        }
    }
    target.draw(sprite);
}

sf::FloatRect Enemy::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition(void) const {
    return sprite.getPosition();
}