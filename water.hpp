#ifndef WATER_HPP
#define WATER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

class WATER
{
public:

    WATER();

    void IncreaseTension();
    void DecreaseTension();
    void Update();
    void Splash(unsigned int index, float speed);
    void Draw(sf::RenderWindow &window);


private:

    sf::Text tension_Text;
    sf::Font font;

    float tension;
    float dampening;
    float spread;
    float scale;

    struct WaterColumn
      {
         WaterColumn() :TargetHeight(300.0f), Height(300.0f), Speed(0.0f) {};
         float TargetHeight;
         float Height;
         float Speed;

         void Update(float dampening, float tension)
         {
            float x = TargetHeight - Height;
            Speed += tension * x - Speed * dampening;
            Height += Speed;
         }
      };

      vector<unique_ptr<WaterColumn>> Columns;

};

#endif // WATER_HPP
