#include "basestate.h"
#include <list>

struct MapEvent
{
    MapEvent(const char* name);
    const char* name;
    int eventtime;
    virtual void OnReached();
};

class GameState : public IBaseState
{
public:
    GameState();

    bool LoadLevel(const char* filename);

    std::list<MapEvent*> mapevents;
    std::list<MapEvent*> mapeventscache;

    sf::CircleShape hexagon;

    void drawdbg(float deltams);
    void drawbg(float deltams);
    void drawfg(float deltams);

    virtual void setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window);
    virtual void draw(float deltams);
    virtual void update(float deltams);
    virtual void release(IBaseState* nextstate);

    virtual void event(sf::Event &event);
};