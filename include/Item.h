#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>

class Item
{
    public:
        Item(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, sf::Vector2f posicao, char tipo);
        virtual ~Item();

        void desenha(sf::RenderWindow& window);

    private:
        sf::RectangleShape corpoItem;
        sf::IntRect itemRet;
        bool coletado;
        char tipo;
};

#endif // ITEM_H
