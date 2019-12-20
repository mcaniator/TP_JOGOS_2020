#ifndef INIMIGO_H
#define INIMIGO_H
#include "Animacao.h"
#include "Colisor.h"

class Inimigo
{
    public:
        Inimigo(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel);
        virtual ~Inimigo();

        void atualiza(float deltaTempo);
        void desenha(sf::RenderWindow& window);
        void emColisao(char direcao);

        Colisor getColisor() { return Colisor(corpoInimigo); };

    private:
        sf::RectangleShape corpoInimigo;
        sf::RectangleShape texturaInimigo;
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

#endif // INIMIGO_H
