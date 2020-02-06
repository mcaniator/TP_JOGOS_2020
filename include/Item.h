#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>

class Item
{
    public:
        Item();
        virtual ~Item();

    private:
        bool coletado;
        char tipo;
};

#endif // ITEM_H
