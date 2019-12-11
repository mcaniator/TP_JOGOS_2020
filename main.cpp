#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Jogador.h"
#include "Plataforma.h"
#include "Mapa.h"

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

void atualizaPosicao(Jogador* p, float x, float y)
{
    p->set(x, y);
}

float obtemVelocidadeX(Jogador* p)
{
    return p->getVX();
}

float obtemVelocidadeY(Jogador* p)
{
    return p->getVY();
}

void atualizaVelocidadeX(Jogador* p, float novaVX)
{
    p->setVX(novaVX);
}

void atualizaVelocidadeY(Jogador* p, float novaVY)
{
    p->setVY(novaVY);
}

int sentidoMovimentoLateral(Jogador* p)
{
    return p->sentidoMovimentoLateral();
}

int sentidoMovimentoVertical(Jogador* p)
{
    return p->sentidoMovimentoVertical();
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
float deslocamentoLateral(Jogador* p, float deltaTime)
{
    float vx = obtemVelocidadeX(p);
    return vx * deltaTime * sentidoMovimentoLateral(p);
}

///EXERCICIO 2
float deslocamentoVertical(Jogador* p, float deltaTime)
{
    float vy = obtemVelocidadeY(p);
    return vy * deltaTime * sentidoMovimentoVertical(p);
}

///EXERCICIO 3
void calculaDeslocamento(Jogador* p, float deltaTime)
{
    float x, y;
    x = obtemPosicaoX(p);
    y = obtemPosicaoY(p);

///EXERCICIO 4                                                         TEM QUE CONSERTAR COM AS CONDIÇOES NOVAS

///float vx, vy;
///vx = obtemVelocidadeX(p);
///vy = obtemVelocidadeY(p);

///vx = vx + (500 * deltaTime * sentidoMovimentoLateral(p));
///vy = vy + (500 * deltaTime * sentidoMovimentoVertical(p));
///x = x + vx * deltaTime;
///y = y + vy * deltaTime;
///atualizaVelocidadeX(p, vx);
///atualizaVelocidadeY(p, vy);

    ///Essas duas linhas abaixo devem ser excluidas para o funcionamento do exercicio 4;
    x = x + deslocamentoLateral(p, deltaTime);
    y = y + deslocamentoVertical(p, deltaTime);
    atualizaPosicao(p, x, y);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 01", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("mapa.png");
    char direcao;

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);


    std::vector<Plataforma> platforms;

    platforms.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));


    float deltaTime = 0.0f;
    sf::Clock clock;

    ResizeView(window, view);
    while(window.isOpen())
    {
        ////CONFIGURACOES
        deltaTime = clock.restart().asSeconds();
        if(deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128)
                    {
                        printf("%c",evnt.text.unicode);
                    }
                default:
                    break;
            }
        }
        ////
        ////JOGO
        //MOVIMENTACAO



        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            Plataforma& platform = platforms[i];
            if(platform.GetColisor().ChecaColisao(jogador.GetColisor(), direcao))
                jogador.EmColisao(direcao);
        }

        jogador.Update(deltaTime);
        calculaDeslocamento(&jogador, deltaTime);

        //ATUALIZA CONFIGURACOES
        view.setCenter(jogador.GetPosition());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS

        mapa.desenha(window);
        jogador.Draw(window);
        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            Plataforma& platform = platforms[i];
            platform.Draw(window);
        }

        //
        ////

        window.display();
    }
    return 0;
}
