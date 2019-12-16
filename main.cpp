#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Jogador.h"
#include "Plataforma.h"
#include "Mapa.h"
#define BORDA_ESQ 240
#define BORDA_DIR 720
#define BORDA_CIMA 192
#define BORDA_BAIXO 768

static const float VIEW_HEIGHT = 312.0f;

using namespace std;

float obtemPosicaoX(Jogador* p)
{
    return p->getX();
}

float obtemPosicaoY(Jogador* p)
{
    return p->getY();
}

int teclaEsq()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

int teclaDir()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

int teclaCima()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

int teclaBaixo()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///

///EXERCICIO 1
int colisaoBordaX(float posX, float tamanhoX)
{
    if((posX - (tamanhoX / 2) < BORDA_ESQ && teclaEsq()) || (posX + (tamanhoX / 2) > BORDA_DIR && teclaDir()))
        return 1;
    else
        return 0;
}

int colisaoBordaY(float posY, float tamanhoY)
{
    if((posY - (tamanhoY / 2) < BORDA_CIMA && teclaCima()) || (posY + (tamanhoY / 2) > BORDA_BAIXO && teclaBaixo()))
        return 1;
    else
        return 0;
}

///EXERCICIO 2
int colidiu(float jogX, float compJog, float jogY, float largJog, float objX, float compObj, float objY, float largObj)
{
    if((fabs(jogX - objX) <= (compJog + compObj) / 2) || (fabs(jogX - objX) <= (compJog + compObj) / 2))
        return 1;
    else
        return 0;
}

int main()
{
    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 02", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    //VARIAVEIS DO JOGO
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("mapa.png");

    char direcao;

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    std::vector<Plataforma> platformas;
        platformas.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));

    //CONFIGURA TEMPO
    float deltaTempo = 0.0f;
    sf::Clock clock;

    //CONFIGURA VIEW
    ResizeView(window, view);

    while(window.isOpen())
    {
        ////CONFIGURACOES GERAIS

        deltaTempo = clock.restart().asSeconds();
        if(deltaTempo > 1.0f / 20.0f)
            deltaTempo = 1.0f / 20.0f;

        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        ////JOGO

        //MOVIMENTACAO

        for(unsigned int i = 0; i < platformas.size(); i++)
        {
            Plataforma& platforma = platformas[i];
            if(platforma.getColisor().checaColisao(jogador.getColisor(), &direcao))
            {
                jogador.emColisao(direcao);
            }
        }

        jogador.atualiza(deltaTempo, colisaoBordaX(jogador.getX(), jogador.getComprimento()), colisaoBordaY(jogador.getY(), jogador.getLargura()));

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS


        for(unsigned int i = 0; i < platformas.size(); i++)
        {
            Plataforma& platforma = platformas[i];
            platforma.desenha(window);
        }
        mapa.desenha(window);
        jogador.desenha(window);

        ////
        window.display();
    }

    return 0;
}
