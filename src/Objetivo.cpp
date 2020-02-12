#include "Objetivo.h"

Objetivo::Objetivo(sf::Texture* texturaObjetivo, sf::Vector2u tamanhoDaImagemObjetivo, sf::Texture* texturaFala, sf::Vector2u tamanhoDaImagemFala, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem)
{
    recebidos[0] = '\0';
    numRecebidos = 0;

    //OBJETIVO
    corpoObjetivo.setPosition(500.0, 200.0);
    corpoObjetivo.setSize(sf::Vector2f(64.0f, 64.0f));
    corpoObjetivo.setOrigin(corpoObjetivo.getSize() / 2.0f);
    corpoObjetivo.setTexture(texturaObjetivo);

    objetivoRet.width = texturaObjetivo->getSize().x / (float)tamanhoDaImagemObjetivo.x;
    objetivoRet.height = texturaObjetivo->getSize().y / (float)tamanhoDaImagemObjetivo.y;
    objetivoRet.left = 0 * objetivoRet.width;
    objetivoRet.top = 2 * objetivoRet.height;
    corpoObjetivo.setTextureRect(objetivoRet);

    //FALA OBJETIVO
    corpoFala.setSize(sf::Vector2f(185.6f, 57.6f));
    corpoFala.setTexture(texturaFala);
    corpoFala.setOrigin(corpoFala.getSize() / 2.0f);
    corpoFala.setPosition(corpoObjetivo.getPosition().x, corpoObjetivo.getPosition().y - 57);

    //ITEM OBJETIVO
    corpoItem.setSize(sf::Vector2f(32.0f, 32.0f));
    corpoItem.setTexture(texturaItem);
    corpoItem.setOrigin(corpoItem.getSize() / 2.0f);

    itemRet.width = texturaItem->getSize().x / (float)tamanhoDaImagemItem.x;
    itemRet.height = texturaItem->getSize().y / (float)tamanhoDaImagemItem.y;

    //CORPO
    corpo.setSize(sf::Vector2f(26.0f, 15.0f));
    corpo.setOrigin(corpo.getSize() / 2.0f);
    corpo.setPosition(corpoObjetivo.getPosition().x, corpoObjetivo.getPosition().y + 27);
}

Objetivo::~Objetivo()
{
    //dtor
}

void Objetivo::desenha(sf::RenderWindow& window, char resposta[])
{
    window.draw(corpoObjetivo);
    window.draw(corpoFala);
    for(int i = 0; i < 5; i++)
    {
        switch(resposta[i])
        {
            case 'a':
                itemRet.left = 12 * itemRet.width;
                itemRet.top = 3 * itemRet.height;
                break;
            case 'b':
                itemRet.left = 12 * itemRet.width;
                itemRet.top = 4 * itemRet.height;
                break;
            case 'c':
                itemRet.left = 12 * itemRet.width;
                itemRet.top = 5 * itemRet.height;
                break;
            case 'd':
                itemRet.left = 13 * itemRet.width;
                itemRet.top = 0 * itemRet.height;
                break;
            case 'e':
                itemRet.left = 13 * itemRet.width;
                itemRet.top = 1 * itemRet.height;
                break;
            case 'f':
                itemRet.left = 13 * itemRet.width;
                itemRet.top = 2 * itemRet.height;
                break;
            case 'g':
                itemRet.left = 3 * itemRet.width;
                itemRet.top = 5 * itemRet.height;
                break;
            case 'h':
                itemRet.left = 4 * itemRet.width;
                itemRet.top = 5 * itemRet.height;
                break;
            case 'i':
                itemRet.left = 5 * itemRet.width;
                itemRet.top = 5 * itemRet.height;
                break;
            default:
                break;
        }
        corpoItem.setTextureRect(itemRet);
        corpoItem.setPosition(corpoObjetivo.getPosition().x - 64 + 32 * i, corpoObjetivo.getPosition().y - 70);
        window.draw(corpoItem);
    }
}
