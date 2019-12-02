#include "Jogador.h"
#include <math.h>
#include <iostream>

using namespace std;

Jogador::Jogador(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime, float vel) :
    animacao(texture, tamanhoDaImagem, switchTime)
{
    linha = 0;

    velocidade.x = vel;
    velocidade.y = vel;

    sentidoMovimentoX = 0;
    sentidoMovimentoY = 0;
    ultimaDirecao = 'b';

    corpoJogador.setSize(sf::Vector2f(30.0f, 15.0f));
    corpoJogador.setOrigin(corpoJogador.getSize() / 2.0f);
    corpoJogador.setPosition(10.0f, 10.0f);
    texturaJogador.setSize(sf::Vector2f(64.0f, 64.0f));
    texturaJogador.setOrigin(texturaJogador.getSize() / 2.0f);
    texturaJogador.setPosition(10.0f, 10.0f);
    texturaJogador.setTexture(texture);
}

Jogador::~Jogador()
{

}

void Jogador::Update(float deltaTime)
{
    //COMANDOS TECLADO
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sentidoMovimentoY == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sentidoMovimentoX = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sentidoMovimentoY == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sentidoMovimentoX = 1;
    }
    else
        sentidoMovimentoX = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sentidoMovimentoX == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sentidoMovimentoY = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sentidoMovimentoX == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sentidoMovimentoY = 1;
    }
    else
        sentidoMovimentoY = 0;

    //EM MOVIMENTO
    if(sentidoMovimentoX || sentidoMovimentoY)
        emMovimento = true;
    else
        emMovimento = false;

    //ANIMACAO
    if(sentidoMovimentoX == 1)
    {
        linha = 11;
        animacao.setNumFrames(9);
        ultimaDirecao = 'd';
    }
    else if(sentidoMovimentoX == -1)
    {
        linha = 9;
        animacao.setNumFrames(9);
        ultimaDirecao = 'e';
    }
    else if(sentidoMovimentoY == 1)
    {
        linha = 10;
        animacao.setNumFrames(9);
        ultimaDirecao = 'b';
    }
    else if(sentidoMovimentoY == -1)
    {
        linha = 8;
        animacao.setNumFrames(9);
        ultimaDirecao = 'c';
    }
    else
    {
        switch(ultimaDirecao)
        {
            case 'c':
                linha = 0;
                break;
            case 'e':
                linha = 1;
                break;
            case 'b':
                linha = 2;
                break;
            case 'd':
                linha = 3;
                break;
        }
        animacao.setNumFrames(0);
        animacao.setFrameAtual(0);
    }

    animacao.Update(linha, deltaTime, emMovimento);
    sf::Vector2f posicao = corpoJogador.getPosition();
    posicao.y -= 27;
    texturaJogador.setPosition(posicao);
    texturaJogador.setTextureRect(animacao.uvRect);

}

void Jogador::Draw(sf::RenderWindow& window)
{
    window.draw(corpoJogador);
    window.draw(texturaJogador);
}

void Jogador::OnCollision(sf::Vector2f direction)
{
    if(direction.x < 0.0f)
    {
        sentidoMovimentoX = 0;
    }
    else if(direction.x > 0.0f)
    {
        sentidoMovimentoX = 0;
    }
    if(direction.y < 0.0f)
    {
        sentidoMovimentoY = 0;
    }
    else if(direction.y > 0.0f)
    {
        sentidoMovimentoY = 0;
    }
}
