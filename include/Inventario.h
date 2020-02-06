#ifndef INVENTARIO_H
#define INVENTARIO_H
#define MAX_ITENS 7
#include <SFML/Graphics.hpp>


class Inventario
{
    public:
        Inventario();
        virtual ~Inventario();

    private:
        char itens[MAX_ITENS];
        int numItens[MAX_ITENS];
};

#endif // INVENTARIO_H
