#include "CharSet.h"


CharSet::CharSet(const std::string& charset, sf::Vector2u charSize)
    : m_charSize(charSize)
{
    if (!m_charSet.loadFromFile(charset))
        throw std::runtime_error("Could not load charset");

    sf::IntRect rect(0, 0, charSize.x, charSize.y);

    for (unsigned int dir = 0; dir < 4; ++dir)
    {
        Animation anim(m_charSet);
        sf::IntRect still;

        for (unsigned int frame = 0; frame < 3; ++frame)
        {
            if (frame == 1)
                still = rect; 
            anim.addFrame(rect);

            rect.left += charSize.x;
        }

        anim.addFrame(still);
        m_anims.push_back(anim);

        rect.top += charSize.y;
    }
}

const Animation& CharSet::getAnimation(Direction dir) const
{
    return m_anims.at(static_cast<unsigned int>(dir));
}

const sf::Vector2u& CharSet::getCharSize() const
{
    return m_charSize;
}

const sf::Texture *CharSet::getTexture() const
{
    return &m_charSet;
}
