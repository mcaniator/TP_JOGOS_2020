#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Jogador.h"
#include "Plataforma.h"


static const float VIEW_HEIGHT = 512.0f;

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

void ResizeView(const sf::RenderWindow&  window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

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

 ///EXERCICIO 4

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
    sf::RenderWindow window(sf::VideoMode(512, 400), "GettingStarted", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT), sf::Vector2f(512.0f,512.0f));
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("jogador.png");
    sf::Texture platformTexture;
    platformTexture.loadFromFile("Tux.png");

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    std::vector<Plataforma> platforms;

    platforms.push_back(Plataforma(&platformTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
    platforms.push_back(Plataforma(&platformTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    platforms.push_back(Plataforma(&platformTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));


    float deltaTime = 0.0f;
    sf::Clock clock;

    while(window.isOpen())
    {
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
            case sf::Event::Resized:
                cout << "Width: " << evnt.size.width << " Height: " << evnt.size.height << endl;
                ResizeView(window, view);
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128)
                {
                    printf("%c",evnt.text.unicode);
                }
            default:
                break;
            }

            if(evnt.type == evnt.Closed)
            {
                window.close();
            }

        }

        jogador.Update(deltaTime);
        calculaDeslocamento(&jogador, deltaTime);

        sf::Vector2f direction;

        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            Plataforma& platform = platforms[i];
            if(platform.GetColisor().CheckCollision(jogador.GetColisor(), direction, 1.0f))
                jogador.OnCollision(direction);
        }

        view.setCenter(jogador.GetPosition());

        window.clear(sf::Color(150,150,150));
        window.setView(view);
        jogador.Draw(window);

        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            Plataforma& platform = platforms[i];
            platform.Draw(window);
        }

        window.display();
    }
    return 0;
}
