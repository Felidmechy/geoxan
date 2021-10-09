#include "basestate.h"
#include "raudio/raudio.h"

class TitleState : public IBaseState
{
public:

    TitleState();

    Sound music;

    sf::Font font;

    virtual void setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window);
    virtual void draw(int deltams);
    virtual void update(int deltams);
    virtual void release(IBaseState* nextstate);

    virtual void event(sf::Event &event);
};