#ifndef TILEMAP_H
#define TILEMAP_H


#include <SFML/Graphics.hpp>
#include "TileSet.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap(const TileSet& tileSet, unsigned int width, unsigned int height);

        TileMap(const std::string& tileSet, const sf::Vector2u& tileSize, unsigned int width, unsigned int height);

        virtual ~TileMap();

        void setTile(unsigned int i, unsigned int j, unsigned int tileNumber);
        void setTiles(const unsigned int *tiles);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        TileSet m_tileSet;
        unsigned int m_width;
        unsigned int m_height;

        unsigned int *m_tiles;
        sf::VertexArray m_vertices;
};


#endif // TILEMAP_H
