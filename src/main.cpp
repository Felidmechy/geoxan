#include "SFML/Graphics.hpp"
#include "raudio/raudio.h"
#include "app.h"
#include "icon.h"
#include "titlestate.h"

int main()
{

    
    Settings settings;
    geoxan::readsettingsfile(settings);

    sf::RenderWindow window;

    if (settings.fullscreen)
    {
        window.create(sf::VideoMode::getFullscreenModes().front(), "geoxan", sf::Style::Fullscreen);
    }
    else
    {
        window.create(sf::VideoMode(settings.xsize, settings.ysize), "geoxan");
    }

    window.setActive(true);
    window.setFramerateLimit(settings.maxfps);

    window.setIcon(96, 87, (unsigned char*)icon);

    InitAudioDevice();
    SetMasterVolume(settings.volume);

    geoxan *game = new geoxan(&window);
    //hack to update before first state
    game->deltams = game->frametimer.restart().asMilliseconds();
    game->gamems = game->gametimer.getElapsedTime().asMicroseconds() / 1000;
    game->changestate(new TitleState);


    

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
