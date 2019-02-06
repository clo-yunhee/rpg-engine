#ifndef CHARSPRITE_H
#define CHARSPRITE_H


#include <SFML/Graphics.hpp>
#include "CharSet.h"

class CharSprite : public sf::Drawable, public sf::Transformable
{
    public:
        CharSprite(const CharSet& charset);

        CharSprite(const std::string& charset, sf::Vector2u charSize);

        void rotate(CharSet::Direction direction);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void updateSpriteRect();

        CharSet m_charSet;
        sf::Sprite m_sprite;

        CharSet::Direction m_direction;
        const Animation *m_anim;
        unsigned int m_animFrame;
};


#endif // CHARSPRITE_H
