#include "Mapa.h"
#include <SFML/Graphics.hpp>


Mapa::Mapa(sf::Texture *texturaMapa)
{
    minimapa.setSize(sf::Vector2f(3.0f, 3.0f));
    filtro.setSize(minimapa.getSize());

    numBlocos.x = TAMANHO_MAPA_X;
    numBlocos.y = TAMANHO_MAPA_Y;
    tamanhoBlocos = TAMANHO_BLOCOS;

    tamanhoDaImagem.x = 16;
    tamanhoDaImagem.y = 16;

    padrao.posicaoNaImagem.x = 0;
    padrao.posicaoNaImagem.y = 0;
    padrao.corpoBloco.width = texturaMapa->getSize().x / (float)tamanhoDaImagem.x;
    padrao.corpoBloco.height = texturaMapa->getSize().y / (float)tamanhoDaImagem.y;
    padrao.corpoBloco.left = padrao.corpoBloco.width * padrao.posicaoNaImagem.x;
    padrao.corpoBloco.top = padrao.corpoBloco.height * padrao.posicaoNaImagem.y;

    for(int i = 0; i < numBlocos.x; i++)
    {
        for(int j = 0; j < numBlocos.y; j++)
        {
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
                    blocos[i][j].posicaoNaImagem.x = 0;
                    blocos[i][j].posicaoNaImagem.y = 8;
                    break;
                case 4:
                    blocos[i][j].posicaoNaImagem.x = 1;
                    blocos[i][j].posicaoNaImagem.y = 8;
                    break;
                case 5:
                    blocos[i][j].posicaoNaImagem.x = 0;
                    blocos[i][j].posicaoNaImagem.y = 9;
                    break;
                case 6:
                    blocos[i][j].posicaoNaImagem.x = 1;
                    blocos[i][j].posicaoNaImagem.y = 9;
                    break;
                case 7:
                    blocos[i][j].posicaoNaImagem.x = 11;
                    blocos[i][j].posicaoNaImagem.y = 1;
                    break;
                case 8:
                    blocos[i][j].posicaoNaImagem.x = 12;
                    blocos[i][j].posicaoNaImagem.y = 1;
                    break;
            }
            blocos[i][j].corpoBloco.width = texturaMapa->getSize().x / (float)tamanhoDaImagem.x;
            blocos[i][j].corpoBloco.height = texturaMapa->getSize().y / (float)tamanhoDaImagem.y;
            blocos[i][j].corpoBloco.left = padrao.corpoBloco.width * blocos[i][j].posicaoNaImagem.x;
            blocos[i][j].corpoBloco.top = padrao.corpoBloco.height * blocos[i][j].posicaoNaImagem.y;
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
            textura.setTextureRect(padrao.corpoBloco);
            window.draw(textura);
            textura.setTextureRect(blocos[i][j].corpoBloco);
            window.draw(textura);
        }
    }
}

void Mapa::desenhaMinimapa(sf::RenderWindow& window, sf::Vector2f posicao, int mapa[TAMANHO_MAPA_X][TAMANHO_MAPA_Y])
{
    int tipo, tipo2;
    sf::Color green(43, 209, 31);
    sf::Color darkgreen(20, 97, 15);
    sf::Color grey(128, 128, 128);
    sf::Color brown(139,69,19);

    for(int i = 0; i < TAMANHO_MAPA_X; i++)
    {
        for(int j = 0; j < TAMANHO_MAPA_Y; j++)
        {
            tipo = tipoBlocos[i][j];
            tipo2 = mapa[i][j];
            minimapa.setPosition(posicao.x + 80 + 3 * i, posicao.y + 38 + 3 * j);
            filtro.setPosition(minimapa.getPosition());

            //PRIMEIRO
            if(tipo == 0)
                minimapa.setFillColor(green);
            else if(tipo == 7 || tipo == 8)
                minimapa.setFillColor(grey);
            else
                minimapa.setFillColor(darkgreen);

            //SEGUNDO

            if(tipo2 == 1)
                filtro.setFillColor(sf::Color::Red);
            else if(tipo2 == 2)
                filtro.setFillColor(sf::Color::Black);
            else
                filtro.setFillColor(sf::Color::Transparent);

            if(i == 0 || i == TAMANHO_MAPA_X - 1 || j == 0 || j == TAMANHO_MAPA_Y - 1)
            {
                minimapa.setFillColor(brown);
                filtro.setFillColor(brown);
            }

            window.draw(minimapa);
            window.draw(filtro);
        }
    }
}


