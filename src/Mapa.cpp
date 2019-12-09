#include "Mapa.h"
#include <SFML/Graphics.hpp>

Mapa::Mapa(sf::Texture *texturaMapa)
{
    numBlocos.x = TAMANHO_MAPA_X;
    numBlocos.y = TAMANHO_MAPA_Y;
    tamanhoBlocos = TAMANHO_BLOCOS;

    tamanhoDaImagem.x = 16;
    tamanhoDaImagem.y = 16;

    for(int i = 0; i < numBlocos.x; i++)
    {
        for(int j = 0; j < numBlocos.y; j++)
        {
            //tipoBlocos[i][j] = rand()%2;
            switch(tipoBlocos[i][j])
            {
                case 0:
                    blocos[i][j].posicaoNaImagem.x = 0;
                    blocos[i][j].posicaoNaImagem.y = 0;
                    break;
                case 1:
                    blocos[i][j].posicaoNaImagem.x = 0;
                    blocos[i][j].posicaoNaImagem.y = 10;
                    break;
                case 2:
                    blocos[i][j].posicaoNaImagem.x = 1;
                    blocos[i][j].posicaoNaImagem.y = 10;
                    break;
                case 3:
                    blocos[i][j].posicaoNaImagem.x = 1;
                    blocos[i][j].posicaoNaImagem.y = 11;
                    break;
                case 4:
                    blocos[i][j].posicaoNaImagem.x = 0;
                    blocos[i][j].posicaoNaImagem.y = 8;
                    break;
                case 5:
                    blocos[i][j].posicaoNaImagem.x = 1;
                    blocos[i][j].posicaoNaImagem.y = 8;
                    break;
                case 6:
                    blocos[i][j].posicaoNaImagem.x = 0;
                    blocos[i][j].posicaoNaImagem.y = 9;
                    break;
                case 7:
                    blocos[i][j].posicaoNaImagem.x = 1;
                    blocos[i][j].posicaoNaImagem.y = 9;
                    break;
            }
            blocos[i][j].corpoBloco.width = texturaMapa->getSize().x / (float)tamanhoDaImagem.x;
            blocos[i][j].corpoBloco.height = texturaMapa->getSize().y / (float)tamanhoDaImagem.y;
            blocos[i][j].corpoBloco.left = blocos[i][j].corpoBloco.width * blocos[i][j].posicaoNaImagem.x;
            blocos[i][j].corpoBloco.top = blocos[i][j].corpoBloco.height * blocos[i][j].posicaoNaImagem.y;
            blocos[i][j].posicaoBloco.x = tamanhoBlocos * i;
            blocos[i][j].posicaoBloco.y = tamanhoBlocos * j;
        }
    }
    textura.setSize(sf::Vector2f(TAMANHO_BLOCOS, TAMANHO_BLOCOS));
    textura.setPosition(sf::Vector2f(0.0f, 0.0f));
    textura.setTexture(texturaMapa);
}

Mapa::~Mapa()
{
    //dtor
}

void Mapa::desenha(sf::RenderWindow& window)
{
    for(int i = 0; i < numBlocos.x; i++)
    {
        for(int j = 0; j < numBlocos.y; j++)
        {
            textura.setPosition(blocos[i][j].posicaoBloco);
            textura.setTextureRect(blocos[i][j].corpoBloco);
            window.draw(textura);
        }
    }
}
