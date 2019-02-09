#ifndef STATES_MAPEXAMPLE_H
#define STATES_MAPEXAMPLE_H


#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "TileMap.h"
#include "CharEntity.h"

class MapExample : public GameState
{
    public:
        MapExample();

    private:
        void draw(sf::RenderTarget& target, sf::Time delta) const;
        void update(sf::RenderTarget& target, sf::Time delta);
        void handleInput();
        
        TileSet m_tileSet;
        TileMap m_tileMap;

        CharSet m_charSet;
        CharSprite m_charSprite;
        CharEntity m_charEntity;
};


#endif // STATES_MAPEXAMPLE_H
