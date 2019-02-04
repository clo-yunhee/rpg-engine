#ifndef TILESET_H
#define TILESET_H


#include <SFML/Graphics.hpp>

class TileSet
{
    public:
        TileSet(const std::string& tileset, sf::Vector2u tileSize);

        void setQuad(sf::Vertex *quad, unsigned int tileNumber) const;

        const sf::Vector2u& getTileSize() const;
        const sf::Texture *getTexture() const;

    private:
        sf::Texture m_tileSet;
        sf::Vector2u m_tileSize;
};


#endif // TILESET_H
