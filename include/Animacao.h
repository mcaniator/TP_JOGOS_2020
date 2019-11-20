#ifndef ANIMACAO_H
#define ANIMACAO_H
#include <SFML\Graphics.hpp>

class Animacao
{
    ///FUNCOES
public:
    Animacao(sf::Texture* texture, sf::Vector2u tamanhoDaImagem, float switchTime);
    virtual ~Animacao();

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

#endif // Animacao_H
