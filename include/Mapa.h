#ifndef MAPA_H
#define MAPA_H
#include <SFML/Graphics.hpp>
#define TAMANHO_MAPA_X 30
#define TAMANHO_MAPA_Y 30
#define TAMANHO_BLOCOS 32

typedef struct
{
    sf::IntRect corpoBloco;
    sf::Vector2f posicaoBloco;
    sf::Vector2i posicaoNaImagem;
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
        Bloco blocos[TAMANHO_MAPA_X][TAMANHO_MAPA_Y];
};

#endif // MAPA_H
