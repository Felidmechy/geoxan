#include "SFML/Graphics.hpp"
#include "raudio/raudio.h"
#include "app.h"
#include "titlestate.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(256, 256), "geoxan");

    window.setActive(true);

    InitAudioDevice();

    geoxan *game = new geoxan(&window);

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
