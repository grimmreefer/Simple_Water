#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>

#include "water.hpp"

WATER::WATER()
{
    tension = .025f;
    dampening = .025f;
    spread = .25f;
    scale = 800/200;///800 IS WINDOW WIDTH


    font.loadFromFile("font.ttf");

    tension_Text.setCharacterSize(20);
    tension_Text.setColor(sf::Color::Black);
    tension_Text.setFont(font);
    tension_Text.setPosition(10.f, 10.f);

    for(unsigned int i = 0; i < 200; i++)
    {
        Columns.push_back(unique_ptr<WaterColumn>(new WaterColumn));
    }
}



void WATER::Splash(unsigned int index, float speed)
{
    if(index >= 0 && index < 800.f)
    {
        Columns[static_cast<unsigned int>(index / scale)] -> Speed = speed;
    }
}



void WATER::IncreaseTension()
{
    tension += .01f;
}



void WATER::DecreaseTension()
{
    if(tension >= .015f)
    {
        tension -= .01f;
    }
    else
    {
        tension = .001f;
    }
}



void WATER::Update()
{
    stringstream ss;
    ss << tension;

    tension_Text.setString(" Press i to Increas Tension\n d to Decreas\nTension = " + ss.str());

    for(unsigned int i = 0; i < Columns.size(); i++)
    {
        Columns[i]->Update(dampening, tension);
    }

    float lDeltas[200];
    float rDeltas[200];

    for(unsigned int j = 0; j < 8; j++)
    {
        for(unsigned int i = 0; i < Columns.size(); i++)
        {
            if(i > 0)
            {
                lDeltas[i] = spread * (Columns[i]->Height - Columns[i - 1]->Height);
                Columns[i - 1]->Speed += lDeltas[i];
            }

            if(i < Columns.size() -1)
            {
                rDeltas[i] = spread * (Columns[i]->Height - Columns[i + 1]->Height);
                Columns[i + 1]->Speed += rDeltas[i];
            }
        }

        for(unsigned int i = 0; i < Columns.size(); i++)
        {
            if(i > 0)
            {
                Columns[i - 1]->Height += lDeltas[i];
            }

            if(i < Columns.size() - 1)
            {
                Columns[i + 1]->Height += rDeltas[i];
            }
        }
    }
}



void WATER::Draw(sf::RenderWindow &window)
{
    for(unsigned int i = 1; i < Columns.size(); i++)
    {
        sf::Vertex vertices[] =
        {
            sf::Vertex(sf::Vector2f((i - 1) * scale, Columns[i - 1]->Height), sf::Color(0,0,200,180)),
            sf::Vertex(sf::Vector2f((i * scale), Columns[i]->Height), sf::Color(0,0,200,180)),
            sf::Vertex(sf::Vector2f((i * scale), 600.f), sf::Color(0,0,200,255)),
            sf::Vertex(sf::Vector2f((i - 1) * scale, 600.f), sf::Color(0,0,200,255))
        };

        window.draw(vertices, 4, sf::Quads);

    }
    window.draw(tension_Text);
}
