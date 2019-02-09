#ifndef CHARSET_H
#define CHARSET_H


#include <SFML/Graphics.hpp>
#include "Animation.h"

class CharSet
{
    public:
        enum class Direction 
        {
            Down = 0, Left, Right, Up
        };

        CharSet(const std::string& charset, sf::Vector2u charSize);

        const Animation& getAnimation(Direction dir) const;

        const sf::Vector2u& getCharSize() const;
        const sf::Texture *getTexture() const;

    private:
        std::vector<Animation> m_anims;

        sf::Texture m_charSet;
        sf::Vector2u m_charSize;
};


#endif // CHARSET_H
