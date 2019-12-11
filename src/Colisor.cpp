#include "Colisor.h"

Colisor::Colisor(sf::RectangleShape& corpo) :
    corpo(corpo)
{
    //ctor
}

Colisor::~Colisor()
{
    //dtor
}

bool Colisor::ChecaColisao(Colisor outro, sf::Vector2f& direcao)
{
    sf::Vector2f posicaoOutro = outro.GetPosicao();
    sf::Vector2f metadeOutro = outro.GetMetade();
    sf::Vector2f posicao = GetPosicao();
    sf::Vector2f metade = GetMetade();

    float deltaX = posicaoOutro.x - posicao.x;
    float deltaY = posicaoOutro.y - posicao.y;

    float intersecaoX = abs(deltaX) - (metadeOutro.x + metade.x);
    float intersecaoY = abs(deltaY) - (metadeOutro.y + metade.y);

    if(intersecaoX < 0.0f && intersecaoY < 0.0f)
    {
        if(intersecaoX > intersecaoY)
        {
            if(deltaX > 0.0f)
            {
                direcao.x = 1.0f;
                direcao.y = 0.0f;
            }
            else
            {
                direcao.x = -1.0f;
                direcao.y = 0.0f;
            }
        }
        else
        {
            if(deltaY > 0.0f)
            {
                direcao.x = 0.0f;
                direcao.y = 1.0f;
            }
            else
            {
                direcao.x = 0.0f;
                direcao.y = -1.0f;
            }
        }
        return true;
    }
    return false;
}

