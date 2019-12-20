#ifndef JOGADOR_H
#define JOGADOR_H
#include "Animacao.h"
#include "Colisor.h"


class Jogador
{
    public:
        Jogador(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel);
        virtual ~Jogador();

        void atualiza(float deltaTempo, char direcao);
        void desenha(sf::RenderWindow& window);

        sf::Vector2f getPosicao() { return corpoJogador.getPosition(); };



        Colisor getColisor() { return Colisor(corpoJogador); };

    private:
        sf::RectangleShape corpoJogador;
        sf::RectangleShape texturaJogador;
        Animacao animacao;

        unsigned int linha;
        bool emMovimento;
        char ultimaDirecao;

        int velocidadeX;
        int velocidadeY;
        int sentidoMovimentoX;
        int sentidoMovimentoY;
        int velMax;

};

#endif // Jogador_H
