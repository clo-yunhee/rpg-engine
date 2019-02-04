#include "TileMap.h"


TileMap::TileMap(const TileSet& tileset, unsigned int width, unsigned int height)
    : m_tileSet(tileset),
      m_width(width), m_height(height),
      m_tiles(new unsigned int[width * height]),
      m_vertices(sf::Quads, width * height * 4)
{
    const sf::Vector2u& tileSize = m_tileSet.getTileSize();

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
        }
}

TileMap::TileMap(const std::string& tileSet, const sf::Vector2u& tileSize, unsigned int width, unsigned int height)
    : TileMap(TileSet(tileSet, tileSize), width, height)
{
}

TileMap::~TileMap()
{
    delete m_tiles;
}

void TileMap::setTile(unsigned int i, unsigned int j, unsigned int tileNumber)
{
    m_tiles[i + j * m_width] = tileNumber;

    sf::Vertex *quad = &m_vertices[(i + j * m_width) * 4];
    
    m_tileSet.setQuad(quad, tileNumber);
}

void TileMap::setTiles(const unsigned int *tiles)
{
    for (unsigned int i = 0; i < m_width; ++i)
        for (unsigned int j = 0; j < m_height; ++j) {
            unsigned int tileNumber = tiles[i + j * m_width];

            setTile(i, j, tileNumber);
        }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = m_tileSet.getTexture();

    // draw the vertex array
    target.draw(m_vertices, states);
}
