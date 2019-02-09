#include "CharSprite.h"


CharSprite::CharSprite(const CharSet& charset)
    : m_charSet(charset), m_sprite(*charset.getTexture()),
      m_direction(CharSet::Direction::Down), m_animFrame(1),
      m_anim(&charset.getAnimation(m_direction))
{
    updateSpriteRect(m_direction, m_animFrame);
}

CharSprite::CharSprite(const std::string& charset, sf::Vector2u charSize)
    : CharSprite(CharSet(charset, charSize))
{
}

void CharSprite::rotate(CharSet::Direction direction)
{
    updateSpriteRect(direction, 1);
}

void CharSprite::tickFrame()
{
    unsigned int nextFrame = (m_animFrame + 1) % m_anim->getSize();

    updateSpriteRect(m_direction, nextFrame);
}

void CharSprite::resetFrame()
{
    updateSpriteRect(m_direction, 1);
}

CharSet::Direction CharSprite::getDirection() const
{
    return m_direction;
}

unsigned int CharSprite::getFrame() const
{
    return m_animFrame;
}

void CharSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_charSet.getTexture();

    target.draw(m_sprite, states);
}

void CharSprite::updateSpriteRect(CharSet::Direction direction, unsigned int frame)
{
    const Animation *anim((direction != m_direction) ? &m_charSet.getAnimation(direction) : m_anim);
    const sf::IntRect& frameRect(anim->getFrame(frame));

    m_sprite.setTextureRect(frameRect);
    
    m_anim = anim;
    m_direction = direction;
    m_animFrame = frame;
}
