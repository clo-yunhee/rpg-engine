#ifndef ANIMATION_H
#define ANIMATION_H


#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation(const sf::Texture& texture);

        void addFrame(sf::IntRect rect);

        const sf::Texture *getTexture() const;
        unsigned int getSize() const;
        const sf::IntRect& getFrame(unsigned int n) const;

    private:
        std::vector<sf::IntRect> m_frames;
        const sf::Texture *m_texture;
};


#endif // ANIMATION_H
