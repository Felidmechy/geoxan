#include "titlestate.h"
#include "app.h"
#include "SFML/Graphics.hpp"
#include "raymath/raymath.h"
#include <string>

TitleState::TitleState() : IBaseState("TitleState")
{

}


void TitleState::setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window)
{
    IBaseState::setup(prevstate, game, window);
    font.loadFromFile("resources/future-terminal.ttf");
    dbgfont.loadFromFile("resources/ProggyClean.ttf");

    titletext.setFont(font);
    starttext.setFont(font);
    optiontext.setFont(font);

    shouldbounce = false;
    hovered = false;
    hoveredlastframe = false;

    titletext.setString("GEOXAN");
    starttext.setString("START");
    optiontext.setString("OPTIONS");

    music = LoadSound("music/title.ogg");
    menuhover = LoadSound("sounds/menuhover.ogg");
    PlaySound(music);
    SetSoundVolume(music, 0.75);

    lastbeat = game->gamems + 11400;
    nextbeat = game->gamems + 11400;
}

void TitleState::draw(int deltams)
{

    sf::Color bg;
    bg.r = Remap(sinf(game->gamems * 0.001), -1.0f, 1.0, 128.0f, 200.0f);
    bg.g = 0;
    bg.b = 0;
    window->clear(bg);

    sf::Text timetext;

    sf::String number("gamems: " + std::to_string(game->gamems));

    timetext.setString(number);

    timetext.setFont(dbgfont);
    timetext.setPosition(25,25);
    timetext.setCharacterSize(16);

    sf::Text deltatext;

    number = ("deltams: " + std::to_string(deltams));

    deltatext.setString(number);

    deltatext.setFont(dbgfont);
    deltatext.setPosition(25,40);
    deltatext.setCharacterSize(16);\

    sf::CircleShape center;
    center.setRadius(2);
    center.setPosition(window->getView().getCenter());
    center.setFillColor(sf::Color::Red);

    if (lastbeat < game->gamems && !shouldbounce)
    {
        shouldbounce = true;
    }

    if (nextbeat < game->gamems)
    {
        lastbeat = game->gamems;
        nextbeat = game->gamems + 600;
    }
    titletext.setCharacterSize(72);
    starttext.setCharacterSize(48);
    optiontext.setCharacterSize(32);

    if (shouldbounce)
    {
        float bounce = Remap(game->gamems, lastbeat, nextbeat, 0, 1);
        float bounce2 = 1.25 - EaseCubicOut(bounce,0,0.25,1);
        titletext.setScale(bounce2, bounce2);
    }
    int screenmiddlex = (window->getView().getSize().x/2u);
    int screenmiddley = (window->getView().getSize().y/2u);

    int posx = (screenmiddlex)-(titletext.getGlobalBounds().width/2);
    int posy = (screenmiddley/2)-(titletext.getGlobalBounds().height/2);
    titletext.setPosition(posx,posy);

    titletext.setOutlineColor(sf::Color::White);
    titletext.setOutlineThickness(8);

    float itemscale = Remap(sinf(game->gamems * 0.01), -1.0f, 1.0f, 1.0f, 1.02f);
    float starttextscale = itemscale;
    float optiontextscale = itemscale;

    starttext.setOutlineThickness(0);
    optiontext.setOutlineThickness(0);

    if (starttext.getGlobalBounds().contains(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y))
    {
        starttextscale += 0.2;
        starttext.setOutlineThickness(8);
    }
    if (optiontext.getGlobalBounds().contains(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y))
    {
        optiontextscale += 0.2;
        optiontext.setOutlineThickness(8);
    }


    starttext.setScale(starttextscale,starttextscale);
    optiontext.setScale(optiontextscale,optiontextscale);


    posx = (screenmiddlex)-(starttext.getGlobalBounds().width/2);
    posy = (screenmiddley + screenmiddley/2)-(starttext.getGlobalBounds().height/2);
    starttext.setPosition(posx, posy);

    posx = (screenmiddlex/3)-(optiontext.getGlobalBounds().width/2);
    posy = (screenmiddley + screenmiddley/3)-(optiontext.getGlobalBounds().height/2);
    optiontext.setPosition(posx, posy);



    //float ratio = (float)window->getView().getSize().y + (float)window->getView().getSize().x;
    //int size = ratio / 24;

    sf::Color color;
    color.r = Remap(sinf(game->gamems * 0.001), -1.0f, 1.0, 0.0f, 255.0f);
    color.g = Remap(sinf(game->gamems * 0.001 + 127), -1.0f, 1.0, 0.0f, 255.0f);
    color.b = Remap(sinf(game->gamems * 0.001 + 255), -1.0f, 1.0, 0.0f, 255.0f);
    titletext.setFillColor(color);

    
    window->draw(timetext);
    window->draw(deltatext);
    window->draw(titletext);
    window->draw(starttext);
    window->draw(optiontext);
    window->draw(center);
}

void TitleState::update(int deltams)
{
    if (starttext.getGlobalBounds().contains(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y))
    {
        hovered = true;
    }
    if (optiontext.getGlobalBounds().contains(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y))
    {
        hovered = true;
    }

    if (hovered && !hoveredlastframe)
    {
        PlaySound(menuhover);
    }

    hoveredlastframe = hovered;
    hovered = false;
}

void TitleState::release(IBaseState* nextstate)
{
    UnloadSound(music);
    UnloadSound(menuhover);
    IBaseState::release(nextstate);
}

void TitleState::event(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            window->close();
        }
    }
}