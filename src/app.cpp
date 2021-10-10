#include "app.h"
#include "basestate.h"

geoxan::geoxan(sf::RenderWindow* wnd)
{
    window = wnd;
    state = nullptr;
    gametimer.restart();
    frametimer.restart();
}

void geoxan::changestate(IBaseState* newstate)
{
    if (state)
    {
        newstate->setup(state, this, window);
        state->release(newstate);
        state = newstate;
    }
    else
    {
        newstate->setup(state, this, window);
        state = newstate;
    }
}

void geoxan::update()
{
    deltams = frametimer.restart().asMilliseconds();
    gamems = gametimer.getElapsedTime().asMicroseconds() / 1000;

    state->update(deltams);
    state->draw(deltams);
}