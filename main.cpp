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
    sf::Texture texturaIventario;
    texturaIventario.loadFromFile("inventario.png");
    sf::Texture texturaItens;
    texturaItens.loadFromFile("itens.png");

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    std::vector<Plataforma> plataformas;
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(480.0f, 1104.0f), sf::Vector2f(192.0f, 384.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(624.0f, 528.0f), sf::Vector2f(288.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(864.0f, 624.0f), sf::Vector2f(192.0f, 384.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1056.0f, 1296.0f), sf::Vector2f(192.0f, 384.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1248.0f, 1200.0f), sf::Vector2f(192.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1296.0f, 576.0f), sf::Vector2f(192.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(768.0f, 1104.0f), sf::Vector2f(192.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1128.0f, 888.0f), sf::Vector2f(144.0f, 144.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1392.0f, 1512.0f), sf::Vector2f(96.0f, 144.0f)));

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

        //COLISOES

        char direcao;

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            plataforma.getColisor().checaColisaoJogadorPlataforma(jogador.getColisor());
        }

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            for(unsigned int j = 0; j < inimigos.size(); j++)
            {
                Inimigo& inimigo = inimigos[j];
                direcao = plataforma.getColisor().checaColisaoInimigoPlataforma(inimigo.getColisor());
                switch(direcao)
                {
                    case 'c':
                        inimigo.setSentidoY(1);
                        break;
                    case 'b':
                        inimigo.setSentidoY(-1);
                        break;
                    case 'd':
                        inimigo.setSentidoX(-1);
                        break;
                    case 'e':
                        inimigo.setSentidoX(1);
                        break;
                    default:
                        break;
                }
            }
        }

        if(jogador.getStatus())
        {
            for(unsigned int i = 0; i < inimigos.size(); i++)
            {
                Inimigo& inimigo = inimigos[i];
                jogador.setStatus(!jogador.getColisor().checaColisao(inimigo.getColisor()));
            }
        }

        //MOVIMENTACAO

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            inimigo.atualiza(deltaTempo);
        }

        jogador.atualiza(deltaTempo);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS

        mapa.desenha(window);

        bool vivo = jogador.getStatus();

        if(!vivo)
            jogador.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() < jogador.getY())
                inimigo.desenha(window);
        }

        if(vivo)
            jogador.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() > jogador.getY())
                inimigo.desenha(window);
        }
/*
        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            plataforma.desenha(window);
        }
*/
        ////
        window.display();
    }

    return 0;
}
