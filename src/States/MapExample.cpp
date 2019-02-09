#include "States/MapExample.h"


static constexpr unsigned int levelTiles[] =
{
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
};


MapExample::MapExample()
    : m_tileSet("tileset.png", sf::Vector2u(32, 32)),
      m_tileMap(m_tileSet, 16, 8),
      m_charSet("charset.png", sf::Vector2u(32, 32)),
      m_charSprite(m_charSet),
      m_charEntity(m_charSprite)
{
    m_tileMap.setTiles(levelTiles);
}

void MapExample::draw(sf::RenderTarget& target, sf::Time delta) const
{
    (void) delta;

    target.draw(m_tileMap);

    m_charEntity.draw(target, delta);
}

void MapExample::update(sf::RenderTarget& target, sf::Time delta)
{
    (void) target;
    (void) delta;

    m_charEntity.update(target, delta);
}

void MapExample::handleInput()
{
    m_charEntity.handleInput();
}
