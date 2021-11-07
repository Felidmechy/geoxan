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

enum msglvls
{
    LVL_CRITICAL = 0,
    LVL_ERROR,
    LVL_WARN,
    LVL_DBG,
    LVL_INFO,
    LVL_NONE
};

void msg(msglvls lvl, const char* msg);

class geoxan
{
public:

    geoxan(sf::RenderWindow* wnd);

    sf::RenderWindow* window;
    IBaseState* state;
    sf::Clock gametimer;
    sf::Clock frametimer;
    sf::Font dbgfont;
    float deltams;
    double gamems;

    static void readsettingsfile(Settings &settings);

    void changestate(IBaseState* newstate);
    void update();
    void event(sf::Event &event);
};