#include "app.h"
#include "basestate.h"
#include "speedykv/KeyValue.h"
#include <iostream>

geoxan::geoxan(sf::RenderWindow* wnd)
{
    window = wnd;
    state = nullptr;
    gametimer.restart();
    frametimer.restart();
    dbgfont.loadFromFile("resources/ProggyClean.ttf");
}

void msg(msglvls lvl, const char* msg)
{
    switch (lvl)
    {
    case LVL_CRITICAL:
        std::cout << "### CRITICAL ###: " << msg << std::endl;
        break;
    case LVL_ERROR:
        std::cout << "### ERROR: " << msg << std::endl;
        break;
    case LVL_WARN:
        std::cout << "# WARNING: " << msg << std::endl;
        break;
    case LVL_DBG:
        std::cout << "DBG: " << msg << std::endl;
        break;
    case LVL_INFO:
        std::cout << "INFO: " << msg << std::endl;
        break;
    case LVL_NONE:
        
        break;
    
    default:
        break;
    }
}

void geoxan::readsettingsfile(Settings &settings)
{
    sf::FileInputStream* settingsfile = new sf::FileInputStream;
    settingsfile->open("cfg/settings.cfg");
    settingsfile->seek(0);
    char* settingscontent = new char[settingsfile->getSize()];
    settingsfile->read(settingscontent, settingsfile->getSize());

    KeyValueRoot settingskv(settingscontent);


    if (settingskv["VideoSettings"]["Fullscreen"].IsValid())
    {
        settings.fullscreen = atoi(settingskv["VideoSettings"]["Fullscreen"].value.string);
    }
    if (settingskv["VideoSettings"]["WindowXSize"].IsValid())
    {
        settings.xsize = atoi(settingskv["VideoSettings"]["WindowXSize"].value.string);
    }
    if (settingskv["VideoSettings"]["WindowYSize"].IsValid())
    {
        settings.ysize = atoi(settingskv["VideoSettings"]["WindowYSize"].value.string);
    }
    if (settingskv["VideoSettings"]["MaxFPS"].IsValid())
    {
        settings.maxfps = atoi(settingskv["VideoSettings"]["MaxFPS"].value.string);
    }


    if (settingskv["AudioSettings"]["Volume"].IsValid())
    {
        settings.volume = atof(settingskv["AudioSettings"]["Volume"].value.string);
    }

    delete settingsfile;
    delete settingscontent;
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
    deltams = (float)frametimer.restart().asMicroseconds() / 1000;
    gamems = (double)gametimer.getElapsedTime().asMicroseconds() / 1000;

    state->update(deltams);
    state->draw(deltams);
}

void geoxan::event(sf::Event &event)
{
    if (event.type == sf::Event::Resized)
    {
        msg(LVL_WARN, "Window resizing currently unsupported");
    }

    state->event(event);
}