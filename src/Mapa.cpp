#include "Mapa.h"
#include <SFML/Graphics.hpp>

Mapa::Mapa(sf::Texture *texturaMapa)
{
    numBlocos.x = TAMANHO_MAPA_X;
    numBlocos.y = TAMANHO_MAPA_Y;
    tamanhoBlocos = TAMANHO_BLOCOS;

    tamanhoDaImagem.x = 16;
    tamanhoDaImagem.y = 12;

    for(int i = 0; i < numBlocos.x; i++)
    {
        for(int j = 0; j < numBlocos.y; j++)
        {
            blocos[i][j].corpoBloco.width = texturaMapa->getSize().x / (float)tamanhoDaImagem.x;
            blocos[i][j].corpoBloco.height = 32;
            blocos[i][j].corpoBloco.left = 0; //0 e a currentImage
            blocos[i][j].corpoBloco.top = 0;
            blocos[i][j].posicaoBloco.x = tamanhoBlocos * i;
            blocos[i][j].posicaoBloco.y = tamanhoBlocos * j;
        }
    }
    textura.setSize(sf::Vector2f(32.0f, 32.0f));
    textura.setPosition(sf::Vector2f(0.0f, 0.0f));
    textura.setTexture(texturaMapa);
}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::desenha(sf::RenderWindow& window)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            textura.setPosition(blocos[i][j].posicaoBloco);
            textura.setTextureRect(blocos[i][j].corpoBloco);
            window.draw(textura);
        }
    }
}
