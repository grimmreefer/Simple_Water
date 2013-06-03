#include <iostream>
#include <SFML/Graphics.hpp>

#include "Water.hpp"

using namespace std;

sf::RenderWindow window;

WATER Water;

sf::Texture rockT;
sf::Sprite rock;

int main()
{
    rockT.loadFromFile("rock.png");
    rock.setTexture(rockT);
    rock.setOrigin(50,50);

    bool rockMoving = false;

    sf::Vector2f Velocity;
    sf::Vector2f Gravity(0.0f, 0.3f);



    window.create(sf::VideoMode(800,600), "Test", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);



	while(window.isOpen())
	{




        sf::Event event;
        while(window.pollEvent(event))
		{

			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();

			default: break;
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            Water.IncreaseTension();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Water.DecreaseTension();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            rockMoving = true;
        }

        if(!rockMoving)
        {
            rock.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        }

        Water.Update();

        if(rockMoving)
        {
            if(rock.getPosition().y > 300.f)
            {
                Velocity *= .84f;
            }

            if(rock.getPosition().y < 300.f && (rock.getPosition().y  + Velocity.y) >= 300)
            {
                Water.Splash(rock.getPosition().x, 300.f);
            }

            rock.setPosition(rock.getPosition() + Velocity);

            Velocity += Gravity;
        }

        if(rock.getPosition().y > 600.f)
        {
            rockMoving = false;
        }

        window.clear(sf::Color(sf::Color(191,239,255)));

        Water.Draw(window);
        window.draw(rock);

        window.display();



	}

};
