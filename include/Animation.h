#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML\Graphics.hpp>

class Animation
{
    ///FUNCOES
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    virtual ~Animation();

    void Update(int row, float deltaTime, bool faceRight);
private:

    ///VARIAVEIS
public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};

#endif // ANIMATION_H
