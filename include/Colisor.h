#ifndef COLISOR_H
#define COLISOR_H
#include <SFML/Graphics.hpp>

class Colisor
{
public:
    Colisor(sf::RectangleShape& body);
    virtual ~Colisor();

    void Move(float dx, float dy)
    {
        body.move(dx, dy);
    }

    bool CheckCollision(Colisor other, sf::Vector2f& direction, float push);
    sf::Vector2f GetPosition()
    {
        return body.getPosition();
    }
    sf::Vector2f GetHalfSize()
    {
        return body.getSize() / 2.0f;
    }

private:
    sf::RectangleShape& body;
};

#endif // Colisor_H
