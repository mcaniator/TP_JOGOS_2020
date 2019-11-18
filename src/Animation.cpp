#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime)
{
    this->tamanhoDaImagem = tamanhoDaImagem;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / (float)tamanhoDaImagem.x;
    uvRect.height = texture->getSize().y / (float)tamanhoDaImagem.y;
}

Animation::~Animation()
{
    //dtor
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += 5 * deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= tamanhoDaImagem.x)
        {
            currentImage.x = 0;
        }
    }

    if(faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    uvRect.top = currentImage.y * uvRect.height;
}
