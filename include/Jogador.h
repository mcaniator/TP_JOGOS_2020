#ifndef JOGADOR_H
#define JOGADOR_H
#include "Animacao.h"
#include "Colisor.h"


class Jogador
{
public:
    Jogador(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel);
    virtual ~Jogador();

    void atualiza(float deltaTempo);
    void desenha(sf::RenderWindow& window);
    void emColisao(char direcao);
    bool colisaoBordasX();
    bool colisaoBordasY();

    sf::Vector2f getPosicao() { return corpoJogador.getPosition(); };

    float getX() { return corpoJogador.getPosition().x; };
    float getY() { return corpoJogador.getPosition().y; };

    float getVX() { return velocidade.x; };
    float getVY() { return velocidade.y; };

    void setVX(float novaVX) { velocidade.x = novaVX; };
    void setVY(float novaVY) { velocidade.y = novaVY; };

    int sentidoMovimentoLateral() { return sentidoMovimentoX; };
    int sentidoMovimentoVertical() { return sentidoMovimentoY; };

    void set(float x, float y) { corpoJogador.setPosition(x, y); };

    Colisor getColisor() { return Colisor(corpoJogador); };

private:
    sf::RectangleShape corpoJogador;
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
