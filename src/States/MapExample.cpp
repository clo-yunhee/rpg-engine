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
    : m_tileset("tileset.png", sf::Vector2u(32, 32)),
      m_level(m_tileset, 16, 8)
{
    m_level.setTiles(levelTiles);
}

void MapExample::draw(sf::RenderTarget& target, sf::Time delta) const
{
    (void) delta;

    target.draw(m_level);
}

void MapExample::update(sf::RenderTarget& target, sf::Time delta)
{
    (void) target;
    (void) delta;
}

void MapExample::handleInput(sf::RenderTarget& target)
{
    (void) target;
}
