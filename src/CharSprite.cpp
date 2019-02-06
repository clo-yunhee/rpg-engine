#include "CharSprite.h"


CharSprite::CharSprite(const CharSet& charset)
    : m_charSet(charset), m_sprite(*charset.getTexture())
{
    rotate(CharSet::Direction::down);
}

CharSprite::CharSprite(const std::string& charset, sf::Vector2u charSize)
    : CharSprite(CharSet(charset, charSize))
{
}

void CharSprite::rotate(CharSet::Direction direction)
{
    m_anim = &m_charSet.getAnimation(direction);
    m_direction = direction;
    m_animFrame = 1; // idle

    updateSpriteRect();
}

void CharSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_charSet.getTexture();

    target.draw(m_sprite, states);
}

void CharSprite::updateSpriteRect()
{
    const Animation& anim(m_charSet.getAnimation(m_direction));
    const sf::IntRect& frameRect(anim.getFrame(m_animFrame));

    m_sprite.setTextureRect(frameRect);
}
