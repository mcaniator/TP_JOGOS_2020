#ifndef OBJETIVO_H
#define OBJETIVO_H
#include <SFML/Graphics.hpp>
#include "Colisor.h"

class Objetivo
{
    public:
        Objetivo(sf::Texture* texturaPessoa, sf::Vector2u tamanhoDaImagemPessoa, sf::Texture* texturaFala, sf::Vector2u tamanhoDaImagemFala, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem);
        virtual ~Objetivo();

        Colisor getColisorPlayer() { return Colisor(corpo); };
        Colisor getColisorItens() { return Colisor(corpoObjetivo); };

        float getY() { return corpo.getPosition().y; };

        void desenha(sf::RenderWindow& window, char resposta[], char recebidos[], bool ganhou, bool terminou);
        void desenhaFinal(sf::RenderWindow& window, sf::Vector2f posicao, bool ganhou);

    private:
        sf::RectangleShape corpo;

        sf::RectangleShape corpoObjetivo;
        sf::IntRect objetivoRet;

        sf::RectangleShape corpoFala;
        sf::IntRect falaRet;

        sf::RectangleShape corpoItem;
        sf::IntRect itemRet;

        sf::Text texto;
        sf::Font fonte;

        char recebidos[6];
        int numRecebidos;
};

#endif // OBJETIVO_H
