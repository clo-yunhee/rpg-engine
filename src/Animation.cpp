#include "Animation.h"

Animation::Animation(const sf::Texture& texture)
    : m_texture(&texture)
{
}

void Animation::addFrame(sf::IntRect rect)
{
    m_frames.push_back(rect);
}

const sf::Texture *Animation::getTexture() const
{
    return m_texture;
}

unsigned int Animation::getSize() const
{
    return m_frames.size();
}

const sf::IntRect& Animation::getFrame(unsigned int n) const
{
    return m_frames.at(n);
}

