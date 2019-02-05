#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <string>
#include <stack>
#include <memory>
#include <mutex>
#include <thread>
#include "constants.h"

class GameState;

class Game
{
    public:
        Game(unsigned int width = WINDOW_WIDTH, unsigned int height = WINDOW_HEIGHT,
                const std::string& title = WINDOW_TITLE, unsigned int frameRate = WINDOW_FRAMERATE);

        void pushState(GameState *state);
        void popState();
        void changeState(GameState *state);
        GameState *peekState();

        void start();
        void join();

    private:
        void gameLoop();

        std::stack<std::shared_ptr<GameState>> m_states;
        
        std::mutex m_stateMtx;
        std::thread m_renderThread;

        sf::RenderWindow m_window;
};


#endif // GAME_H
