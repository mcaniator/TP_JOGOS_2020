#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Jogador.h"
#include "Inimigo.h"
#include "Plataforma.h"
#include "Mapa.h"
#include "Item.h"
#include "Inventario.h"
#include "Objetivo.h"

static const float VIEW_HEIGHT = 322.0f;

using namespace std;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int teclaPressionada()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        return 1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        return 2;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        return 3;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        return 4;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        return 5;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        return 6;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        return 7;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        return 8;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        return 9;
    else
        return 0;
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///

void removeChar (char str[], int indice)
{
    for(int i = indice; str[i] != '\0'; i++)
    {
        str[i] = str[i + 1];
    }
}

void montaObjetivo (char letras[], char resposta[])
{
    int indice;
    int tam;
    for(tam = 0; letras[tam] != '\0'; tam++);
    for(int i = 0; i < 5; i++)
    {
        indice = rand() % (tam - i);
        resposta[i] = letras[indice];
        removeChar(letras, indice);
    }
    resposta[5] = '\0';
}

void organizaInventario(char coletou, char coletados[], int numcoletados[])
{
    if(numcoletados[coletou - 'a'] == 0)
    {
        int indice = 0;
        for(int i = 0; i < 9; i++)
            if(numcoletados[i] != 0)
                indice++;
        coletados[indice] = coletou;
        coletados[indice + 1] = '\0';
    }
    numcoletados[coletou - 'a']++;
}

int comparaString(char resp[], char colocados[])
{
    for(int i = 0; resp[i] != '\0'; i++)
        if(resp[i] != colocados[i])
            return 0;
    return 1;
}

///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

int main()
{
    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 02", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    //VARIAVEIS DOS EXERCICIOS
    bool terminou = false;
    bool ganhou = false;

    char letras[10] = "abcdefghi";
    char resposta[6];

    char coletados[10];
    int numcoletados[9] = {0};

    char recebidos[6];
    int numRecebidos = 0;
        //OBJETIVO
        montaObjetivo(letras, resposta);

    //VARIAVEIS DO JOGO
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("texturas/jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("texturas/mapa.png");
    sf::Texture texturaInimigo;
    texturaInimigo.loadFromFile("texturas/inimigo.png");
    sf::Texture texturaInventario;
    texturaInventario.loadFromFile("texturas/inventario.png");
    sf::Texture texturaItem;
    texturaItem.loadFromFile("texturas/itens.png");
    sf::Texture texturaIndice;
    texturaIndice.loadFromFile("texturas/indices.png");
    sf::Texture texturaObjetivo;
    texturaObjetivo.loadFromFile("texturas/amigo.png");
    sf::Texture texturaFala;
    texturaFala.loadFromFile("texturas/fala.png");

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    Inventario inventario(&texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16), &texturaIndice, sf::Vector2u(4, 1));

    Objetivo objetivo(&texturaObjetivo, sf::Vector2u(13, 21), &texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16));

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
        inimigos.push_back(Inimigo(&texturaInimigo, sf::Vector2u(13, 21), 0.3f, 80.0f, 0, 1));

    std::vector<Item> itens;
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(300.0f, 300.0f), 'a'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(330.0f, 300.0f), 'b'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(360.0f, 300.0f), 'c'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(390.0f, 300.0f), 'd'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(420.0f, 300.0f), 'e'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(450.0f, 300.0f), 'f'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(480.0f, 300.0f), 'g'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(510.0f, 300.0f), 'h'));
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(540.0f, 300.0f), 'i'));

    //CONFIGURA TEMPO
    float deltaTempo = 0.0f;
    sf::Clock clock;

    //DELAY TECLA
    float delay = 1;

    //CONFIGURA VIEW
    ResizeView(window, view);

    while(window.isOpen())
    {
        ////CONFIGURACOES GERAIS

        deltaTempo = clock.restart().asSeconds();
        if(deltaTempo > 1.0f / 20.0f)
            deltaTempo = 1.0f / 20.0f;

        if(delay > 0)
            delay -= deltaTempo;
        else
            delay = 0;

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

        //ITENS

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            if(item.getColisor().checaColisao(jogador.getColisor()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !item.getStatus())
            {
                item.coletou();
                organizaInventario(item.getTipo(), coletados, numcoletados);
            }
        }

        int tecla = teclaPressionada();

        if(tecla != 0 && delay == 0)
        {
            int tamanho = 0;
            for(int i = 0; i < 9; i++)
                if(numcoletados[i] > 0)
                    tamanho++;

            if(tecla <= tamanho)
            {
                int indice = coletados[tecla - 1] - 'a';
                char tipo = coletados[tecla - 1];

                if(numcoletados[indice] == 1)
                    removeChar(coletados, tecla - 1);
                if(numcoletados[indice] > 0)
                    numcoletados[indice]--;

                for(unsigned int i = 0; i < itens.size(); i++)
                {
                    Item& item = itens[i];
                    if(item.getTipo() == tipo && item.getStatus())
                    {
                        item.soltou(jogador.getPosicao().x, jogador.getPosicao().y - 20);
                        break;
                    }
                }
            }
            delay = 0.6;
        }

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            if(item.getColisor().checaColisao(objetivo.getColisorItens()) && !item.getStatus() && numRecebidos != 5)
            {
                item.coletou();
                recebidos[numRecebidos] = item.getTipo();
                numRecebidos++;
                recebidos[numRecebidos] = '\0';
            }
        }

        //COLISOES

        char direcao;

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];
            plataforma.getColisor().checaColisaoJogadorPlataforma(jogador.getColisor());
        }

        objetivo.getColisorPlayer().checaColisaoJogadorPlataforma(jogador.getColisor());

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

        if(!terminou)
            jogador.atualiza(deltaTempo);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS

        mapa.desenha(window);

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            item.desenha(window);
        }

        bool vivo = jogador.getStatus();
        bool naFrente = (objetivo.getY() > jogador.getY());

        if(!vivo)
            jogador.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() < jogador.getY())
                inimigo.desenha(window);
        }

        if(!naFrente)
            objetivo.desenha(window, resposta, recebidos, ganhou, terminou);

        if(vivo)
            jogador.desenha(window);

        if(naFrente)
            objetivo.desenha(window, resposta, recebidos, ganhou, terminou);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() > jogador.getY())
                inimigo.desenha(window);
        }

        if(!terminou)
            inventario.desenha(window, jogador.getPosicao(), coletados, numcoletados);

        //FINAL DO JOGO

        if(numRecebidos == 5)
        {
            if(!terminou)
            {
                terminou = true;
                ganhou = comparaString(resposta, recebidos);
                cout << ganhou;
            }
            objetivo.desenhaFinal(window, jogador.getPosicao(), ganhou);
        }

        ////
        window.display();
    }

    return 0;
}
