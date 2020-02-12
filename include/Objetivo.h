#ifndef OBJETIVO_H
#define OBJETIVO_H
#include <SFML/Graphics.hpp>
#include "Colisor.h"

class Objetivo
{
    public:
        Objetivo(sf::Texture* texturaPessoa, sf::Vector2u tamanhoDaImagemPessoa, sf::Texture* texturaFala, sf::Vector2u tamanhoDaImagemFala, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem);
        virtual ~Objetivo();

        Colisor getColisor() { return Colisor(corpoObjetivo); };

        float getY() { return corpoObjetivo.getPosition().y + 59; };

        void desenha(sf::RenderWindow& window);

    private:
        sf::RectangleShape corpoObjetivo;
        sf::IntRect objetivoRet;
        sf::RectangleShape corpoFala;
        sf::IntRect falaRet;
        sf::RectangleShape corpoItem;
        sf::IntRect itemRet;

        char recebidos[6];
        int numRecebidos;
};

#endif // OBJETIVO_H
