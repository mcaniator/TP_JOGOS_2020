#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"


static const float VIEW_HEIGHT = 512.0f;

using namespace std;

float obtemPosicaoX(Player* p)
{
    return p->getX();
}

float obtemPosicaoY(Player* p)
{
    return p->getY();
}

void atualizaPosicao(Player* p, float x, float y)
{
    p->set(x, y);
}

float obtemVelocidadeX(Player* p)
{
    return p->getVX();
}

float obtemVelocidadeY(Player* p)
{
    return p->getVY();
}

void atualizaVelocidadeX(Player* p, float novaVX)
{
    p->setVX(novaVX);
}

void atualizaVelocidadeY(Player* p, float novaVY)
{
    p->setVY(novaVY);
}

int sentidoMovimentoLateral(Player* p)
{
    return p->sentidoMovimentoLateral();
}

int sentidoMovimentoVertical(Player* p)
{
    return p->sentidoMovimentoVertical();
}

void ResizeView(const sf::RenderWindow&  window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

///EXERCICIO 1
float deslocamentoLateral(Player* p, float deltaTime)
{
    float vx = obtemVelocidadeX(p);
    return vx * deltaTime * sentidoMovimentoLateral(p);
}

///EXERCICIO 2
float deslocamentoVertical(Player* p, float deltaTime)
{
    float vy = obtemVelocidadeY(p);
    return vy * deltaTime * sentidoMovimentoVertical(p);
}

///EXERCICIO 3
void calculaDeslocamento(Player* p, float deltaTime)
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
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Tux.png");
    sf::Texture platformTexture;
    platformTexture.loadFromFile("Tux.png");

    Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, 200.0f);

    std::vector<Platform> platforms;

    platforms.push_back(Platform(&platformTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    platforms.push_back(Platform(&platformTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));


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

        player.Update(deltaTime);
        calculaDeslocamento(&player, deltaTime);

        sf::Vector2f direction;

        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            Platform& platform = platforms[i];
            if(platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);
        }

        view.setCenter(player.GetPosition());

        window.clear(sf::Color(150,150,150));
        window.setView(view);
        player.Draw(window);

        for(unsigned int i = 0; i < platforms.size(); i++)
        {
            Platform& platform = platforms[i];
            platform.Draw(window);
        }

        window.display();
    }
    return 0;
}
