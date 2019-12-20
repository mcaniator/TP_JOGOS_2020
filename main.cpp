#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Jogador.h"
#include "Inimigo.h"
#include "Plataforma.h"
#include "Mapa.h"

static const float VIEW_HEIGHT = 312.0f;

using namespace std;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///



///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

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
    sf::Texture texturaInimigo;
    texturaInimigo.loadFromFile("inimigo.png");

    char direcao;

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    std::vector<Plataforma> plataformas;
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));

    std::vector<Inimigo> inimigos;
        inimigos.push_back(Inimigo(&texturaInimigo, sf::Vector2u(13, 21), 0.3f, 80.0f));

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

        direcao = '\0';
        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            jogador.getColisor().checaColisaoPlayer(plataforma.getColisor(), &direcao);
        }

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            inimigo.atualiza(deltaTempo);
        }

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            for(unsigned int j = 0; j < inimigos.size(); j++)
            {
                Inimigo& inimigo = inimigos[j];
                plataforma.getColisor().checaColisao(inimigo.getColisor());
            }
        }

        jogador.atualiza(deltaTempo, direcao);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS

        mapa.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            inimigo.desenha(window);
        }

        jogador.desenha(window);

        ////
        window.display();
    }

    return 0;
}
