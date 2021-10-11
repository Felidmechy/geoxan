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

    swapcolors = false;
    shouldbounce = false;

    titletext.setString("GEOXAN");
    starttext.setString("START");
    optiontext.setString("OPTIONS");
    
    titletext.setCharacterSize(72);
    starttext.setCharacterSize(48);
    optiontext.setCharacterSize(32);

    

    hexagon.setPointCount(6);
    hexagon.setRadius(100);
    hexagon.setOrigin(hexagon.getRadius(), hexagon.getRadius());
    hexagon.setPosition(window->getView().getCenter().x, window->getView().getSize().y);
    hexagon.setOutlineColor(sf::Color::White);
    hexagon.setOutlineThickness(8);

    rays.resize(4 * hexagon.getPointCount());
    rays.setPrimitiveType(sf::PrimitiveType::Quads);

    music = LoadSound("music/title.ogg");
    menuhover = LoadSound("sounds/menuhover.ogg");
    PlaySound(music);
    SetSoundVolume(music, 0.75);

    lastbeat = game->gamems + 11400;
    nextbeat = game->gamems + 11400;
}

void TitleState::drawdbg()
{
    sf::Text timetext;

    sf::String number("gamems: " + std::to_string(game->gamems));

    timetext.setString(number);

    timetext.setFont(dbgfont);
    timetext.setPosition(25,25);
    timetext.setCharacterSize(16);

    sf::Text deltatext;

    number = ("deltams: " + std::to_string(game->deltams));

    deltatext.setString(number);

    deltatext.setFont(dbgfont);
    deltatext.setPosition(25,40);
    deltatext.setCharacterSize(16);

    sf::CircleShape center;
    center.setRadius(2);
    center.setPosition(hexagon.getPosition());
    center.setFillColor(sf::Color::Red);

    window->draw(timetext);
    window->draw(deltatext);
    window->draw(center);
}

void TitleState::drawtitle()
{
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

    //float ratio = (float)window->getView().getSize().y + (float)window->getView().getSize().x;
    //int size = ratio / 24;

    sf::Color color;
    color.r = Remap(sinf(game->gamems * 0.001), -1.0f, 1.0, 0.0f, 255.0f);
    color.g = Remap(sinf(game->gamems * 0.001 + 127), -1.0f, 1.0, 0.0f, 255.0f);
    color.b = Remap(sinf(game->gamems * 0.001 + 255), -1.0f, 1.0, 0.0f, 255.0f);
    titletext.setFillColor(color);

    window->draw(titletext);
}

void TitleState::drawbuttons()
{
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

    int screenmiddlex = (window->getView().getSize().x/2u);
    int screenmiddley = (window->getView().getSize().y/2u);

    int posx = (screenmiddlex)-(starttext.getGlobalBounds().width/2);
    int posy = (screenmiddley + screenmiddley/2)-(starttext.getGlobalBounds().height/2);

    starttext.setPosition(posx, posy);

    posx = (screenmiddlex/3)-(optiontext.getGlobalBounds().width/2);
    posy = (screenmiddley + screenmiddley/3)-(optiontext.getGlobalBounds().height/2);
    optiontext.setPosition(posx, posy);

    window->draw(starttext);
    window->draw(optiontext);
}

void TitleState::drawbg()
{
    window->clear();

    sf::Color color;
    color.r = Remap(sinf(game->gamems * 0.001), -1.0f, 1.0, 0.0f, 255.0f);
    color.g = Remap(sinf(game->gamems * 0.001 + 127), -1.0f, 1.0, 0.0f, 255.0f);
    color.b = Remap(sinf(game->gamems * 0.001 + 255), -1.0f, 1.0, 0.0f, 255.0f);
    hexagon.setFillColor(color);

    if (swapcolors)
    {
        hexagon.rotate(-0.3*game->deltams);
    }
    else
    {
        hexagon.rotate(0.2*game->deltams);
    }

    if (shouldbounce)
    {
        float bounce = Remap(game->gamems, lastbeat, nextbeat, 0, 1);
        float bounce2 = 1.75 - EaseBounceOut(bounce,0,0.75,1);
        hexagon.setScale(bounce2, bounce2);
    }

    for (int i = 0; i < hexagon.getPointCount(); i++)
    {
        sf::Vector2f curpoint = hexagon.getTransform().transformPoint(hexagon.getPoint(i));
        sf::Vector2f nextpoint = hexagon.getTransform().transformPoint(hexagon.getPoint(i+1));

        if (i == hexagon.getPointCount())
        {
            nextpoint = hexagon.getTransform().transformPoint(hexagon.getPoint(0));
        }

        bool even = i % 2;
        
        int vert = i*4;

        sf::Color color1(255,45,45);
        sf::Color color2(60,41,60);

        for (int p = vert; p < vert+4; p++)
        {
            if (swapcolors)
            {
                if (even)
                {
                    rays[p].color = color2;
                }
                else
                {
                    rays[p].color = color1;
                }
            }
            else
            {
                if (even)
                {
                    rays[p].color = color1;
                }
                else
                {
                    rays[p].color = color2;
                }
            }
        }
        
        rays[vert].position = curpoint;
        rays[vert+1].position = nextpoint;

        Vector2 normal;

        normal.x = nextpoint.x - hexagon.getPosition().x;
        normal.y = nextpoint.y - hexagon.getPosition().y;
        normal = Vector2Normalize(normal);
        normal = Vector2Scale(normal, 5000);

        rays[vert+2].position.x = normal.x;
        rays[vert+2].position.y = normal.y;

        normal.x = curpoint.x - hexagon.getPosition().x;
        normal.y = curpoint.y - hexagon.getPosition().y;
        normal = Vector2Normalize(normal);
        normal = Vector2Scale(normal, 5000);

        rays[vert+3].position.x = normal.x;
        rays[vert+3].position.y = normal.y;

    }
    
    

    window->draw(rays);
    window->draw(hexagon);
}

void updatebuttons()
{

}

void TitleState::draw(int deltams)
{
    drawbg();
    drawbuttons();
    drawtitle();
    drawdbg();
}

void TitleState::update(int deltams)
{
    /*
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
    */

   if (lastbeat < game->gamems && !shouldbounce)
    {
        shouldbounce = true;
    }

    if (nextbeat < game->gamems)
    {
        swapcolors = !swapcolors;
        lastbeat = game->gamems;
        nextbeat = game->gamems + 600;
    }

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
        if (event.key.code == sf::Keyboard::Key::Up)
        {
            hexagon.setPointCount(hexagon.getPointCount()+1);
            rays.resize(4 * hexagon.getPointCount());
        }
        if (event.key.code == sf::Keyboard::Key::Down)
        {
            hexagon.setPointCount(hexagon.getPointCount()-1);
            rays.resize(4 * hexagon.getPointCount());
        }
    }
}