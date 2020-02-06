#include "Item.h"

Item::Item(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, sf::Vector2f posicao, char tipo)
{
    this->tipo = tipo;
    coletado = false;

    corpoItem.setSize(sf::Vector2f(35.0f, 35.0f));
    corpoItem.setOrigin(corpoItem.getSize() / 2.0f);
    corpoItem.setPosition(posicao);
    corpoItem.setTexture(textura);

    itemRet.width = textura->getSize().x / (float)tamanhoDaImagem.x;
    itemRet.height = textura->getSize().y / (float)tamanhoDaImagem.y;

    switch(tipo)
    {
        case 'a':
            itemRet.left = 12 * itemRet.width;
            itemRet.top = 3 * itemRet.height;

    }

    corpoItem.setTextureRect(itemRet);
}

Item::~Item()
{
    //dtor
}

void Item::desenha(sf::RenderWindow& window)
{
    window.draw(corpoItem);
}
