#include "CharEntity.h"
#include <cmath>

CharEntity::CharEntity(const CharSprite& sprite)
    : m_sprite(sprite), m_frameSpeed(2), m_isTileBased(true), m_movSpeed(100), m_isMoving(false)
{
}

CharEntity::CharEntity(const CharSet& charset)
    : CharEntity(CharSprite(charset))
{
}

CharEntity::CharEntity(const std::string& charset, sf::Vector2u charSize)
    : CharEntity(CharSprite(charset, charSize))
{
}

void CharEntity::draw(sf::RenderTarget& target, sf::Time delta) const
{
    (void) delta;

    target.draw(m_sprite);
}

void CharEntity::update(sf::RenderTarget& target, sf::Time delta)
{
    (void) target;

    const auto& pos(m_sprite.getPosition());
    unsigned int curFrame(m_sprite.getFrame());

    // animate
    if (m_isMoving || (curFrame != 1 && curFrame != 3))
    {
        // make sure to finish the animation even if not moving (until idle)
        m_frameDelay += delta;
        if (m_frameDelay >= sf::milliseconds(400. / m_frameSpeed)) {
            m_sprite.tickFrame(); 
           
            m_frameDelay = sf::Time::Zero;
        }
    }

    // move
    if (m_isMoving)
    {
        sf::Vector2f distance(m_target - pos);

        m_movDelay += delta;

        if (m_movDelay >= sf::milliseconds(50. / m_movSpeed))
        {
            sf::Vector2f signs((distance.x > 0) - (distance.x < 0),
                               (distance.y > 0) - (distance.y < 0));

            m_sprite.move(signs);

            m_movDelay = sf::Time::Zero;
        }

        if (distance.x == 0 && distance.y == 0)
        {
            m_isMoving = false;
        }
    }

}

void CharEntity::handleInput()
{
    CharSet::Direction dir(m_sprite.getDirection());

    bool isLeftPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)),
         isRightPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)),
         isUpPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)),
         isDownPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    if (isLeftPressed)   dir = CharSet::Direction::Left;
    if (isRightPressed)  dir = CharSet::Direction::Right;
    if (isUpPressed)     dir = CharSet::Direction::Up;
    if (isDownPressed)   dir = CharSet::Direction::Down;
    
    sf::Vector2f target(m_sprite.getPosition());

    if (!m_isTileBased)
    {
        if (isLeftPressed)   target.x--;
        if (isRightPressed)  target.x++;
        if (isUpPressed)     target.y--;
        if (isDownPressed)   target.y++;

        m_target = target;
    }
    else if (!m_isMoving)
    {
        const auto& size(m_sprite.getCharSize());

        sf::Vector2f pos(floor(target.x / size.x + .5) * size.x,
                         floor(target.y / size.y + .5) * size.y);

        if (dir != m_sprite.getDirection() &&
                (pos.x != target.x || pos.y != target.y))
        {
            dir = m_sprite.getDirection();
        }

        if (dir == CharSet::Direction::Left)        pos.x -= size.x;
        else if (dir == CharSet::Direction::Right)  pos.x += size.x;
        else if (dir == CharSet::Direction::Up)     pos.y -= size.y;
        else if (dir == CharSet::Direction::Down)   pos.y += size.y;
        
        // only allow changing direction if on tile 
        if (isLeftPressed || isRightPressed || isDownPressed || isUpPressed)
        {
            m_isMoving = true;
            m_target = pos;
        }

    }
    else return;

    if (m_sprite.getDirection() != dir)
        m_sprite.rotate(dir);
}

void CharEntity::setTileBased(bool isTileBased) 
{
    m_isTileBased = isTileBased;
}

bool CharEntity::isTileBased() const
{
    return m_isTileBased;
}

