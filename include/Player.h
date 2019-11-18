#ifndef PLAYER_H
#define PLAYER_H
#include "Animation.h"
#include "Collider.h"


class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imagecount, float switchTime, float speed, float jumpHeight);
    virtual ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void OnCollision(sf::Vector2f direction);

    sf::Vector2f GetPosition()
    {
        return body.getPosition();
    }

    float getX()
    {
        return body.getPosition().x;
    }

    float getY()
    {
        return body.getPosition().y;
    }

    float getVX()
    {
        return velocidade.x;
    }

    float getVY()
    {
        return velocidade.y;
    }

    void setVX(float newVX)
    {
        velocidade.x = newVX;
    }

    void setVY(float newVY)
    {
        velocidade.y = newVY;
    }

    int sentidoMovimentoLateral()
    {
        return sentidoMovimentoX;
    }

    int sentidoMovimentoVertical()
    {
        return sentidoMovimentoY;
    }

    void set(float x, float y)
    {
        body.setPosition(x, y);
    }

    Collider GetCollider()
    {
        return Collider(body);
    }

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    bool faceRight;
    int sentidoMovimentoX;
    int sentidoMovimentoY;
    sf::Vector2f velocidade;

};

#endif // PLAYER_H
