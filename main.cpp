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
int colidiu(float jogX, float compJog, float jogY, float altJog, float objX, float compObj, float objY, float altObj)
{
    float deltaX = fabs(jogX - objX);
    float deltaY = fabs(jogY - objY);
    float distMinX = (compJog + compObj) / 2;
    float distMinY = (altJog + altObj) / 2;
    if((deltaX <= distMinX) && (deltaY <= distMinY))
        return 1;
    else
        return 0;
}

///EXERCICIO 3
char ladoColisao(float jogX, float compJog, float jogY, float altJog, float objX, float compObj, float objY, float altObj)
{
    float e, d, c, b;
    e = fabs((jogX - (compJog / 2)) - (objX + (compObj / 2)));
    d = fabs((jogX + (compJog / 2)) - (objX - (compObj / 2)));
    c = fabs((jogY - (altJog / 2)) - (objY + (altObj / 2)));
    b = fabs((jogY + (altJog / 2)) - (objY - (altObj / 2)));

    if(e < d && e < c && e < b)
        return 'e';
    else if(d < e && d < c && d < b)
        return 'd';
    else if(c < d && c < e && c < b)
        return 'c';
    else if(b < d && b < c && b < e)
        return 'b';
    else
        return '0';
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

    std::vector<Plataforma> plataformas;
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));

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
            if(colidiu(jogador.getX(), jogador.getComprimento(), jogador.getY(), jogador.getAltura(), plataforma.getX(), plataforma.getComprimento(), plataforma.getY(), plataforma.getAltura()))
            {
                direcao = ladoColisao(jogador.getX(), jogador.getComprimento(), jogador.getY(), jogador.getAltura(), plataforma.getX(), plataforma.getComprimento(), plataforma.getY(), plataforma.getAltura());
                cout << direcao;
            }
        }

        jogador.atualiza(deltaTempo, colisaoBordaX(jogador.getX(), jogador.getComprimento()), colisaoBordaY(jogador.getY(), jogador.getAltura()), direcao);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS


        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            plataforma.desenha(window);
        }
        mapa.desenha(window);
        jogador.desenha(window);

        ////
        window.display();
    }

    return 0;
}
