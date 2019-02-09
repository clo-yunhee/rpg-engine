#ifndef ENTITY_H
#define ENTITY_H


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Entity 
{
    protected:
        virtual void draw(sf::RenderTarget& target, sf::Time delta) const = 0;
        virtual void update(sf::RenderTarget& target, sf::Time delta) = 0;
        virtual void handleInput() = 0;
};


#endif // ENTITY_H 
