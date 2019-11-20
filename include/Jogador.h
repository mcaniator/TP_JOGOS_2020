#ifndef JOGADOR_H
#define JOGADOR_H
#include "Animacao.h"
#include "Colisor.h"


class Jogador
{
public:
    Jogador(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime, float vel);
    virtual ~Jogador();

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

    Colisor GetColisor()
    {
        return Colisor(body);
    }

private:
    sf::RectangleShape body;
    sf::RectangleShape texturaJogador;
    Animacao animacao;

    unsigned int linha;
    bool emMovimento;
    char ultimaDirecao;

    int sentidoMovimentoX;
    int sentidoMovimentoY;
    sf::Vector2f velocidade;

};

#endif // Jogador_H
