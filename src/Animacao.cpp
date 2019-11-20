#include "Animacao.h"

Animacao::Animacao(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime)
{
    this->tamanhoDaImagem = tamanhoDaImagem;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / (float)tamanhoDaImagem.x;
    uvRect.height = texture->getSize().y / (float)tamanhoDaImagem.y;
}

Animacao::~Animacao()
{
    //dtor
}

void Animacao::Update(int linha, float deltaTime, bool emMovimento)
{
    currentImage.y = linha;
    totalTime += 5 * deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= tamanhoDaImagem.x)
        {
            if(emMovimento)
                currentImage.x = 1;
            else
                currentImage.x = 0;
        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
    uvRect.top = currentImage.y * uvRect.height;
}
