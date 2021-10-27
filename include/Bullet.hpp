#ifndef PLAYER_BULLET
#define PLAYER_BULLET

#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
public:
    Bullet(sf::Vector2f position, int velocity);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2f getPosition(void) const;
    int getVelocity()const;

private:
    mutable sf::RectangleShape laser;
    int velocity;
};

#endif //PLAYER_BULLET