#ifndef STATES_MAPEXAMPLE_H
#define STATES_MAPEXAMPLE_H


#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TileSet.h"
#include "TileMap.h"

class MapExample : public GameState
{
    public:
        MapExample();

    private:
        void draw(sf::RenderTarget& target, sf::Time delta) const;
        void update(sf::RenderTarget& target, sf::Time delta);
        void handleInput(sf::RenderTarget& target);

        TileSet m_tileset;
        TileMap m_level;
};


#endif // STATES_MAPEXAMPLE_H
