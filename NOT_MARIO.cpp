#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        //
        // 
        // 
        // 
        // 
        // 
        // //
    	auto time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;
        if (time > 20) time = 20;
   
        zombi.update(time, 1200);
        ghost.update(time,1200);
        //gost.MoveEnemy(TileMap, time, 1200);
        ////
        // 
        // 
        // 
        // 
        // 
        // //
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}