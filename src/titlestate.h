#include "basestate.h"
#include "raudio/raudio.h"

class Arrow : public sf::Drawable, public sf::Transformable
{
public:

    // add functions to play with the entity's geometry / colors / texturing...
    sf::VertexArray m_vertices;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    
};

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
    Arrow arrow;

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
    virtual void draw(float deltams);
    virtual void update(float deltams);
    virtual void release(IBaseState *nextstate);

    virtual void event(sf::Event &event);
};