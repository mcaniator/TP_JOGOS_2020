#include "Player.h"
#include <math.h>
#include <iostream>

using namespace std;

Player::Player(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime, float vel) :
    animation(texture, tamanhoDaImagem, switchTime)
{
    linha = 0;

    velocidade.x = vel;
    velocidade.y = vel;

    sentidoMovimentoX = 0;
    sentidoMovimentoY = 0;
    ultimaDirecao = 'b';

    body.setSize(sf::Vector2f(200.0f, 200.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
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
        animation.setNumFrames(9);
        ultimaDirecao = 'd';
    }
    else if(sentidoMovimentoX == -1)
    {
        linha = 9;
        animation.setNumFrames(9);
        ultimaDirecao = 'e';
    }
    else if(sentidoMovimentoY == 1)
    {
        linha = 10;
        animation.setNumFrames(9);
        ultimaDirecao = 'b';
    }
    else if(sentidoMovimentoY == -1)
    {
        linha = 8;
        animation.setNumFrames(9);
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
        animation.setNumFrames(0);
        animation.setFrameAtual(0);
    }

    animation.Update(linha, deltaTime, emMovimento);
    body.setTextureRect(animation.uvRect);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
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
