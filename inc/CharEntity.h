#ifndef CHARENTITY_H
#define CHARENTITY_H


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "CharSprite.h"
#include "CharSet.h"

class CharEntity : public Entity
{
    public:
        CharEntity(const CharSprite& sprite);
        CharEntity(const CharSet& charset);
        CharEntity(const std::string& charset, sf::Vector2u charSize);

        virtual void draw(sf::RenderTarget& target, sf::Time delta) const;
        virtual void update(sf::RenderTarget& target, sf::Time delta);
        virtual void handleInput();
    
    private:
        CharSprite m_sprite;

        float m_frameSpeed;
        sf::Time m_frameDelay;

        sf::Vector2f m_velocity;
};


#endif // CHARENTITY_H
