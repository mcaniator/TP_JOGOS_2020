#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <SFML/Graphics.hpp>
#include "Colisor.h"


class Plataforma
{
public:
    Plataforma(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    virtual ~Plataforma();

    void Draw(sf::RenderWindow& window);
    Colisor GetColisor()
    {
        return Colisor(body);
    }

private:
    sf::RectangleShape body;
};

#endif // Plataforma_H
