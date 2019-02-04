#include "TileSet.h"


TileSet::TileSet(const std::string& tileset, sf::Vector2u tileSize)
    : m_tileSize(tileSize)
{
    if (!m_tileSet.loadFromFile(tileset))
        throw std::runtime_error("Could not load tileset");
}

void TileSet::setQuad(sf::Vertex *quad, unsigned int tileNumber) const
{
    unsigned int tu = tileNumber % (m_tileSet.getSize().x / m_tileSize.x);
    unsigned int tv = tileNumber / (m_tileSet.getSize().x / m_tileSize.x);

    quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
}

const sf::Vector2u& TileSet::getTileSize() const {
    return m_tileSize;
}

const sf::Texture *TileSet::getTexture() const {
    return &m_tileSet;
}
