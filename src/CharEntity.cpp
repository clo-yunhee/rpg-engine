#include "CharEntity.h"
#include <cmath>

CharEntity::CharEntity(const CharSprite& sprite)
    : m_sprite(sprite), m_frameSpeed(2), m_movSpeed(100), m_movesTileBased(true)
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

    bool moving(pos != m_target);
    unsigned int curFrame(m_sprite.getFrame());

    if (moving || (curFrame != 1 && curFrame != 3))
    {
        // make sure to finish the animation even if not moving (until idle)
        m_frameDelay += delta;
        if (m_frameDelay >= sf::milliseconds(400. / m_frameSpeed)) {
            m_sprite.tickFrame(); 
           
            m_frameDelay = sf::Time::Zero;
        }
    }

    if (moving)
    {
        m_movDelay += delta;

        if (m_movDelay >= sf::milliseconds(50. / m_movSpeed)) {
            sf::Vector2f distance(m_target - pos);
            sf::Vector2f signs((distance.x > 0) - (distance.x < 0),
                               (distance.y > 0) - (distance.y < 0));

            m_sprite.move(signs);

            m_movDelay = sf::Time::Zero;
        }
    }

}

void CharEntity::handleInput()
{
    CharSet::Direction dir(m_sprite.getDirection());
    sf::Vector2f target(m_sprite.getPosition());

    bool isLeftPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)),
         isRightPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)),
         isUpPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)),
         isDownPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    if (isLeftPressed)
    {
        dir = CharSet::Direction::Left;
        if (!m_movesTileBased)
            target.x -= m_frameSpeed;
    }
    if (isRightPressed)
    {
        dir = CharSet::Direction::Right;
        if (!m_movesTileBased)
            target.x += m_frameSpeed;
    }
    if (isUpPressed)
    {
        dir = CharSet::Direction::Up;
        if (!m_movesTileBased)
            target.y -= m_frameSpeed;
    }
    if (isDownPressed)
    {
        dir = CharSet::Direction::Down;
        if (!m_movesTileBased)
            target.y += m_frameSpeed;
    }
    

    // wait for the end of the movement
    if (m_movesTileBased)
    {
        const auto& size(m_sprite.getCharSize());

        sf::Vector2f pos(floor(target.x / size.x) * size.x,
                         floor(target.y / size.y) * size.y);

        // only allow changing direction if 
        if (dir != m_sprite.getDirection() &&
                (pos.x != target.x || pos.y != target.y))
        {
            dir = m_sprite.getDirection();
        }

        if (dir == CharSet::Direction::Left)        pos.x -= size.x;
        else if (dir == CharSet::Direction::Right)  pos.x += size.x;
        else if (dir == CharSet::Direction::Up)     pos.y -= size.y;
        else if (dir == CharSet::Direction::Down)   pos.y += size.y;
        
        target = pos;
    }

    if (m_sprite.getDirection() != dir)
        m_sprite.rotate(dir);

    if (isLeftPressed || isRightPressed || isUpPressed || isDownPressed)
        m_target = target;
    
}

void CharEntity::setTileBased(bool movesTileBased) 
{
    m_movesTileBased = movesTileBased;
}

bool CharEntity::movesTileBased() const
{
    return m_movesTileBased;
}
