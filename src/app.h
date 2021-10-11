#include "SFML/Graphics.hpp"

struct Settings
{
    bool fullscreen;
    int xsize;
    int ysize;
    int maxfps;
    float volume;
};

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

    static void readsettingsfile(Settings &settings);

    void changestate(IBaseState* newstate);
    void update();
};