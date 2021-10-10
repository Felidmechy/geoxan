#include "SFML/Graphics.hpp"

class IBaseState;

class geoxan
{
public:

    geoxan(sf::RenderWindow* wnd);

    sf::RenderWindow* window;
    IBaseState* state;
    sf::Clock gametimer;
    sf::Clock frametimer;
    int deltams;
    long gamems;

    void changestate(IBaseState* newstate);
    void update();
};