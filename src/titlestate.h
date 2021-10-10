#include "basestate.h"
#include "raudio/raudio.h"

class TitleState : public IBaseState
{
public:

    TitleState();

    Sound music;
    Sound menuhover;

    sf::Font font;
    sf::Font dbgfont;

    sf::Text titletext;
    sf::Text starttext;
    sf::Text optiontext;


    bool shouldbounce;
    bool hovered;
    bool hoveredlastframe;
    long lastbeat;
    long nextbeat;

    virtual void setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window);
    virtual void draw(int deltams);
    virtual void update(int deltams);
    virtual void release(IBaseState* nextstate);

    virtual void event(sf::Event &event);
};