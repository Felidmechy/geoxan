#include "basestate.h"
#include "app.h"

IBaseState::IBaseState(const char* state_name)
{
    game = nullptr;
    window = nullptr;
    this->state_name = state_name;
}


void IBaseState::setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window)
{
    this->window = window;
    this->game = game;
}

void IBaseState::draw(float deltams)
{

}

void IBaseState::update(float deltams)
{

}

void IBaseState::release(IBaseState* nextstate)
{
    delete this;
}

void IBaseState::event(sf::Event &event)
{

}