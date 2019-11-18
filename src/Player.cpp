#include "Player.h"
#include <math.h>
#include <iostream>

using namespace std;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
    animation(texture, imageCount, switchTime)
{
    row = 0;
    faceRight = true;

    velocidade.x = 180;
    velocidade.y = 180;

    sentidoMovimentoX = 1;
    sentidoMovimentoY = 1;
    body.setSize(sf::Vector2f(100.0f, 150.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sentidoMovimentoX = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sentidoMovimentoX = 1;
    }
    else
        sentidoMovimentoX = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sentidoMovimentoY = -1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sentidoMovimentoY = 1;
    }
    else
        sentidoMovimentoY = 0;

    animation.Update(row, deltaTime, faceRight);
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
