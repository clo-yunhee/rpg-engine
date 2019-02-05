#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"

class GameState
{
    protected:
        Game *game;

        virtual void draw(sf::RenderTarget& target, sf::Time delta) const = 0;
        virtual void update(sf::RenderTarget& target, sf::Time delta) = 0;
        virtual void handleInput(sf::RenderTarget& target) = 0;
        
        friend class Game;
};


#endif // GAMESTATE_H
