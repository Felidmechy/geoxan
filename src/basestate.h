#include "SFML/Graphics.hpp"

class geoxan;

class IBaseState
{
public:

    IBaseState(const char* state_name);
    const char* state_name;
    geoxan* game;
    sf::RenderWindow* window;

    virtual void setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window);
    virtual void draw(int deltams);
    virtual void update(int deltams);
    virtual void release(IBaseState* nextstate);

    virtual void event(sf::Event &event);
};