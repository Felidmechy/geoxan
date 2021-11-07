#include "gamestate.h"
#include "app.h"


MapEvent::MapEvent(const char* name)
{
    this->name = name;
}

void MapEvent::OnReached()
{
    
}


GameState::GameState() : IBaseState("GameState")
{

}

void GameState::setup(IBaseState* prevstate, geoxan* game, sf::RenderWindow* window)
{
    IBaseState::setup(prevstate, game, window);

    hexagon.setPointCount(6);
    hexagon.setFillColor(sf::Color::White);
    hexagon.setRadius(window->getView().getSize().x * 0.05);
    hexagon.setOrigin(hexagon.getRadius(), hexagon.getRadius());
    hexagon.setPosition(window->getView().getCenter().x, window->getView().getCenter().y);
}

void GameState::drawdbg(float deltams)
{
    sf::Text text;
    text.setString("deltams: " + std::to_string(deltams));
    text.setFont(game->dbgfont);
    text.setCharacterSize(16);

    float width, height;
    width = window->getView().getSize().x;
    height = window->getView().getSize().y;
    text.setPosition(width * 0.02, height * 0.02);

    window->draw(text);
}

void GameState::drawbg(float deltams)
{

}

void GameState::drawfg(float deltams)
{
    window->draw(hexagon);
}

void GameState::draw(float deltams)
{
    window->clear();
    drawbg(deltams);
    drawfg(deltams);

    drawdbg(deltams);
}

void GameState::update(float deltams)
{
    hexagon.rotate(0.25 * deltams);
}

void GameState::release(IBaseState* nextstate)
{
    IBaseState::release(nextstate);
}

void GameState::event(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Escape)
        {
            window->close();
        }
    }
}