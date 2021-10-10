#include "SFML/Graphics.hpp"
#include "raudio/raudio.h"
#include "app.h"
#include "icon.h"
#include "titlestate.h"
#include "speedykv/KeyValue.h"

int main()
{

    sf::FileInputStream* settingsfile = new sf::FileInputStream;
    settingsfile->open("cfg/settings.cfg");
    settingsfile->seek(0);
    char* settingscontent = new char[settingsfile->getSize()];
    settingsfile->read(settingscontent, settingsfile->getSize());

    KeyValueRoot settingskv(settingscontent);

    bool fullscreen = 0;
    int xsize = 640;
    int ysize = 480;
    int maxfps = 60;

    if (settingskv["VideoSettings"]["Fullscreen"].IsValid())
    {
        fullscreen = atoi(settingskv["VideoSettings"]["Fullscreen"].value.string);
    }
    if (settingskv["VideoSettings"]["WindowXSize"].IsValid())
    {
        fullscreen = atoi(settingskv["VideoSettings"]["WindowXSize"].value.string);
    }
    if (settingskv["VideoSettings"]["WindowYSize"].IsValid())
    {
        fullscreen = atoi(settingskv["VideoSettings"]["WindowYSize"].value.string);
    }
    if (settingskv["VideoSettings"]["MaxFPS"].IsValid())
    {
        fullscreen = atoi(settingskv["VideoSettings"]["MaxFPS"].value.string);
    }


    float volume = 1.0f;

    if (settingskv["AudioSettings"]["Volume"].IsValid())
    {
        volume = atof(settingskv["AudioSettings"]["Volume"].value.string);
    }


    sf::RenderWindow window;

    if (fullscreen)
    {
        window.create(sf::VideoMode::getFullscreenModes().front(), "geoxan", sf::Style::Fullscreen);
    }
    else
    {
        window.create(sf::VideoMode(xsize, ysize), "geoxan");
    }

    window.setActive(true);
    window.setFramerateLimit(maxfps);

    window.setIcon(96, 87, (unsigned char*)icon);

    InitAudioDevice();
    SetMasterVolume(volume);

    geoxan *game = new geoxan(&window);
    game->changestate(new TitleState);


    delete settingsfile;
    delete settingscontent;

    // run the program as long as the window is open
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            game->state->event(event);

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game->update();

        window.display();

    }

    delete game;

    CloseAudioDevice();

    return 0;
}
