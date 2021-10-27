#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable {
public:
    enum Side {Left = 0, Right};
    Enemy(sf::Vector2f position);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition(void) const;
private:
    static sf::Texture texture;
    mutable sf::Sprite sprite;

    static Side side;

    int velocity = 5;
};

#endif //ENEMY_HPP