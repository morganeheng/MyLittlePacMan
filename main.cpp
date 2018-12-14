#include <SFML/Graphics.hpp>
#include "Scene.hh"
#include "TimeManager.hh"
#include "ResourcesManager.hh"

int main()
{
    TimeManager &tm = TimeManager::GetInstance();
    Scene &Window = Scene::GetInstance();
    ResourcesManager &rm = ResourcesManager::GetInstance();

    sf::Text Play;
    sf::Text Exit;

    int menu = 0;

    //variable pour déterminer si le jeu a commencé ou non
    bool Playing = false;

    //Choix du menu
    Play.setFont(rm.font);
    Play.setCharacterSize(40);
    Play.setString("Play");
    Play.setPosition({ 260.f, 160.f });

    Exit.setFont(rm.font);
    Exit.setCharacterSize(40);
    Exit.setString("Exit");
    Exit.setPosition({ 260.f, 220.f });

    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                Window.close();
        }

        //Couleur du choix dans le menu
        if (menu == 0)
        {
            Play.setFillColor(sf::Color(255, 255, 0));
            Exit.setFillColor(sf::Color(255, 255, 255));
        }
        else
        {
            Play.setFillColor(sf::Color(255, 255, 255));
            Exit.setFillColor(sf::Color(255, 255, 0));
        }

        //Menu du début
        if (!Playing)
        {
            Window.draw(Play);
            Window.draw(Exit);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if (menu == 0)
                {
                    Playing = true;
                    Window.Play();
                }
                else
                    Window.close();

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                menu = 0;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                menu = 1;
        }
        else
            Window.Update();
        Window.display();
        Window.clear();
    }
    return EXIT_SUCCESS;
}
