#ifndef COLISOR_H
#define COLISOR_H
#include <SFML/Graphics.hpp>

class Colisor
{
public:
    Colisor(sf::RectangleShape& corpo);
    virtual ~Colisor();

    bool ChecaColisao(Colisor outro, sf::Vector2f& direcao);

    sf::Vector2f GetPosicao() { return corpo.getPosition(); };

    sf::Vector2f GetMetade() { return corpo.getSize() / 2.0f; };

private:
    sf::RectangleShape& corpo;
};

#endif // Colisor_H
