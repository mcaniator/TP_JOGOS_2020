#ifndef INVENTARIO_H
#define INVENTARIO_H
#define MAX_ITENS 7
#include <SFML/Graphics.hpp>

typedef struct
{
    sf::IntRect corpoItem;
    sf::Vector2f posicaoItem;
    sf::Vector2i posicaoNaImagem;
    bool coletado;
    char tipo;
}Item;

class Inventario
{
    public:
        Inventario();
        virtual ~Inventario();

    private:
        Item itens[MAX_ITENS];
        int numItens[MAX_ITENS];
};

#endif // INVENTARIO_H
