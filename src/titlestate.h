#include "basestate.h"
#include "raudio/raudio.h"

class Button : public sf::Text
{
    bool hoveredprev;
    bool hovered;
};

class TitleState : public IBaseState
{
public:
    TitleState();

    Sound music;
    Sound menuhover;

    sf::Font font;
    sf::Font dbgfont;

    sf::Text titletext;
    Button starttext;
    Button optiontext;

    sf::CircleShape hexagon;
    sf::VertexArray rays;

    bool shouldbounce;
    bool swapcolors;
    long lastbeat;
    long nextbeat;

    void drawdbg();
    void drawtitle();
    void drawbuttons();
    void drawbg();

    void updatebuttons();

    virtual void setup(IBaseState *prevstate, geoxan *game, sf::RenderWindow *window);
    virtual void draw(int deltams);
    virtual void update(int deltams);
    virtual void release(IBaseState *nextstate);

    virtual void event(sf::Event &event);
};