#include "Game.h"
#include "GameState.h"


Game::Game(unsigned int width, unsigned int height, const std::string& title, unsigned int frameRate)
    : m_window(sf::VideoMode(width, height), title)
{
    m_window.setFramerateLimit(frameRate);
}

void Game::pushState(GameState *state)
{
    m_stateMtx.lock();
    m_states.push(std::shared_ptr<GameState>(state));
    m_stateMtx.unlock();
}

void Game::popState()
{
    m_stateMtx.lock();
    if (!m_states.empty())
        m_states.pop();
    m_stateMtx.unlock();
}

void Game::changeState(GameState *state)
{
    popState();
    pushState(state);
}

GameState *Game::peekState()
{
    if (m_states.empty())
        return nullptr;

    return m_states.top().get();
}

void Game::start()
{
    m_window.setActive(false);
    m_renderThread = std::thread(&Game::gameLoop, this);
}

void Game::join()
{
    m_renderThread.join();
}

void Game::gameLoop()
{
    m_window.setActive(true);

    sf::Clock frameClock;

    while (m_window.isOpen())
    {
        GameState *state = peekState();
        
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                m_window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
        }

        sf::Time frameTime = frameClock.restart();

        m_window.clear(sf::Color::Black);
        m_stateMtx.lock();

        if (state != nullptr)
        {
            state->handleInput();
            state->update(m_window, frameTime);
            state->draw(m_window, frameTime);
        }
        
        m_stateMtx.unlock();
        m_window.display();
    }
}
