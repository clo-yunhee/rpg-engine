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

        void setTileBased(bool isTileBased);
        bool isTileBased() const;

        void setTarget(const sf::Vector2f& target);
        void setTileTarget(const sf::Vector2u& target);

    private:
        CharSprite m_sprite;

        float m_frameSpeed;
        sf::Time m_frameDelay;

        bool m_isTileBased;
        float m_movSpeed;
        sf::Time m_movDelay;

        bool m_isMoving;
        sf::Vector2f m_target;

};


#endif // CHARENTITY_H
