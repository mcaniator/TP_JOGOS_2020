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
    corpoFala.setSize(sf::Vector2f(32.0f, 96.0f));
    corpoFala.setTexture(texturaFala);

    falaRet.width = texturaFala->getSize().x / (float)tamanhoDaImagemFala.x;
    falaRet.height = (texturaFala->getSize().y / (float)tamanhoDaImagemFala.y) * 3;
    corpoFala.setTextureRect(falaRet);

    //ITEM OBJETIVO
    corpoItem.setSize(sf::Vector2f(32.0f, 32.0f));
    corpoItem.setTexture(texturaItem);

    itemRet.width = texturaItem->getSize().x / (float)tamanhoDaImagemItem.x;
    itemRet.height = texturaItem->getSize().y / (float)tamanhoDaImagemItem.y;
    corpoItem.setTextureRect(itemRet);

    //CORPO
    corpo.setSize(sf::Vector2f(26.0f, 15.0f));
    corpo.setOrigin(corpo.getSize() / 2.0f);
    corpo.setPosition(corpoObjetivo.getPosition().x, corpoObjetivo.getPosition().y + 27);
}

Objetivo::~Objetivo()
{
    //dtor
}

void Objetivo::desenha(sf::RenderWindow& window)
{
    window.draw(corpoObjetivo);
    /*
    for(int i = 0; i < 5; i++)
    {

        if(i == 0)
        {
            falaRet.left = 11 * falaRet.width;
            falaRet.top = 32;
            corpoFala.setTextureRect(falaRet);
        }
        else if(i == 4)
        {
            falaRet.left = 13 * falaRet.width;
            falaRet.top = 32;
            corpoFala.setTextureRect(falaRet);
        }
        else
        {
            falaRet.left = 12 * falaRet.width;
            falaRet.top = 32;
            corpoFala.setTextureRect(falaRet);
        }
        corpoFala.setPosition(300 + (i * 32), 200);
        window.draw(corpoFala);
    }*/
}
