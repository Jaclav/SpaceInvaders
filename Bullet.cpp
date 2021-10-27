#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, int velocity) {
    laser.setSize(sf::Vector2f(5, 30));
    laser.setPosition(position);
    laser.setFillColor(sf::Color::Red);
    this->velocity = velocity;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(laser);
    laser.move(0, velocity);
}

sf::Vector2f Bullet::getPosition(void) const {
    return laser.getPosition();
}

int Bullet::getVelocity()const {
    return velocity;
}