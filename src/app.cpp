#include "app.h"
#include "basestate.h"
#include "speedykv/KeyValue.h"

geoxan::geoxan(sf::RenderWindow* wnd)
{
    window = wnd;
    state = nullptr;
    gametimer.restart();
    frametimer.restart();
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
    deltams = frametimer.restart().asMilliseconds();
    gamems = gametimer.getElapsedTime().asMicroseconds() / 1000;

    state->update(deltams);
    state->draw(deltams);
}