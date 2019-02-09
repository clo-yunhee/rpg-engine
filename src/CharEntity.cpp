#include "CharEntity.h"
#include <iostream>

CharEntity::CharEntity(const CharSprite& sprite)
    : m_sprite(sprite), m_frameSpeed(2)
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

    bool moving(m_velocity.x != 0 || m_velocity.y != 0);
    unsigned int curFrame(m_sprite.getFrame());

    if (moving || (curFrame != 1 && curFrame != 3))
    {
        // make sure to finish the animation even if not moving (until idle)
        m_frameDelay += delta;
        if (m_frameDelay >= sf::milliseconds(400 / m_frameSpeed)) {
            m_sprite.tickFrame();

            m_frameDelay = sf::Time::Zero;
        }
    }
    
    if (moving)
    {
        m_sprite.move(m_velocity);
    }
}

void CharEntity::handleInput()
{
    sf::Vector2f vel;
    CharSet::Direction dir(m_sprite.getDirection());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        dir = CharSet::Direction::Left;
        vel.x -= m_frameSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        dir = CharSet::Direction::Right;
        vel.x += m_frameSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        dir = CharSet::Direction::Up;
        vel.y -= m_frameSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        dir = CharSet::Direction::Down;
        vel.y += m_frameSpeed;
    }

    if (m_sprite.getDirection() != dir) {
        m_sprite.rotate(dir);
    }
    m_velocity = vel;
}
