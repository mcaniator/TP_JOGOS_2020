#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Jogador.h"
#include "Inimigo.h"
#include "Plataforma.h"
#include "Mapa.h"
#define BORDA_ESQ 240
#define BORDA_DIR 720
#define BORDA_CIMA 192
#define BORDA_BAIXO 768

static const float VIEW_HEIGHT = 322.0f;

using namespace std;

float obtemPosicaoX(Jogador* p)
{
    return p->getX();
}

float obtemPosicaoY(Jogador* p)
{
    return p->getY();
}

float obtemPosicaoXinimigo(Inimigo* i)
{
    return i->getX();
}

float obtemPosicaoYinimigo(Inimigo* i)
{
    return i->getY();
}

float obtemCompInimigo(Inimigo* i)
{
    return i->getComprimento();
}

void atualizaPosicaoXinimigo(Inimigo* i, float x)
{
    i->set(x, i->getY());
}

void atualizaSentidoXinimigo(Inimigo* i, int s)
{
    i->setSentidoMovimentoX(s);
}

void atualizaSentidoYinimigo(Inimigo* i, int s)
{
    i->setSentidoMovimentoY(s);
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
    return 0;
}

int colisaoBordaY(float posY, float tamanhoY)
{
    return 0;
}

///EXERCICIO 2
int colidiu(float jogX, float compJog, float jogY, float altJog, float objX, float compObj, float objY, float altObj)
{
    return 0;
}

///EXERCICIO 3
char ladoColisao(float jogX, float compJog, float jogY, float altJog, float objX, float compObj, float objY, float altObj)
{
    return '0';
}

///EXERCICIO 4
int moveInimigo(Inimigo* i, Jogador* p)
{
    return 0;
}

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
    texturaJogador.loadFromFile("texturas/jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("texturas/mapa.png");
    sf::Texture texturaInimigo;
    texturaInimigo.loadFromFile("texturas/inimigo.png");

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

        //COLISAO

        direcao = '\0';
        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];

            //PLATAFORMA x JOGADOR
            if(colidiu(jogador.getX(), jogador.getComprimento(), jogador.getY(), jogador.getAltura(), plataforma.getX(), plataforma.getComprimento(), plataforma.getY(), plataforma.getAltura()))
            {
                direcao = ladoColisao(jogador.getX(), jogador.getComprimento(), jogador.getY(), jogador.getAltura(), plataforma.getX(), plataforma.getComprimento(), plataforma.getY(), plataforma.getAltura());
            }

            //PLATAFORMA x INIMIGO
            for(unsigned int j = 0; j < inimigos.size(); j++)
            {
                Inimigo& inimigo = inimigos[j];
                plataforma.getColisor().checaColisao(inimigo.getColisor());

                //INIMIGO x JOGADOR
                if(jogador.getStatus())
                    jogador.setStatus(!jogador.getColisor().checaColisao2(inimigo.getColisor()));
            }
        }

        //MOVIMENTACAO

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            inimigo.atualiza(deltaTempo, jogador.getX() - inimigo.getX(), jogador.getY() - inimigo.getY(), moveInimigo(&inimigo, &jogador));
        }

        jogador.atualiza(deltaTempo, colisaoBordaX(jogador.getX(), jogador.getComprimento()), colisaoBordaY(jogador.getY(), jogador.getAltura()), direcao);

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
        ////
        window.display();
    }

    return 0;
}
