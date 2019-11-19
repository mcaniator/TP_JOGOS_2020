#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML\Graphics.hpp>

class Animation
{
    ///FUNCOES
public:
    Animation(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime);
    virtual ~Animation();

    void Update(int linha, float deltaTime, bool faceRight);

    void setNumFrames(int numFrames) { tamanhoDaImagem.x = numFrames; };
    void setFrameAtual(int frame) { currentImage.x = frame; };
private:

    ///VARIAVEIS
public:
    sf::IntRect uvRect;

private:
    sf::Vector2u tamanhoDaImagem;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};

#endif // ANIMATION_H
