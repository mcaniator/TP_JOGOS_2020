#ifndef MAPA_H
#define MAPA_H
#include <SFML/Graphics.hpp>

typedef struct
{
    sf::IntRect corpoBloco;
    sf::Vector2f posicaoBloco;
}Bloco;

class Mapa
{
    public:
        Mapa(sf::Texture *texturaMapa);
        virtual ~Mapa();
        void desenha(sf::RenderWindow& window);

    private:
        sf::Vector2i numBlocos;
        int tamanhoBlocos;
        sf::Vector2i tamanhoDaImagem;
        sf::RectangleShape textura;
        Bloco blocos[10][10];
};

#endif // MAPA_H
