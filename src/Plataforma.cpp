#include "Plataforma.h"

Plataforma::Plataforma(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
}

Plataforma::~Plataforma()
{
    //dtor
}

void Plataforma::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
