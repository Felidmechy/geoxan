#include "titlestate.h"
#include "app.h"
#include "SFML/Graphics.hpp"

TitleState::TitleState() : IBaseState("TitleState")
{

}


void TitleState::setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window)
{
    IBaseState::setup(prevstate, game, window);
    font.loadFromFile("resources/TTPinesBoldItalicDEMO.ttf");
    music = LoadSound("music/title.ogg");
    PlaySound(music);
}

void TitleState::draw(int deltams)
{
    window->clear();

    sf::Text text;
    text.setString("text");
    text.setFont(font);
    text.setPosition(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    window->draw(text);
}

void TitleState::update(int deltams)
{

}

void TitleState::release(IBaseState* nextstate)
{
    UnloadSound(music);
    IBaseState::release(nextstate);
}

void TitleState::event(sf::Event &event)
{

}