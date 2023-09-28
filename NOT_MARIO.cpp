#include <SFML/Graphics.hpp>

const int H = 10;
const int W = 100;
const int size_texture = 64;

std::string TileMap[H] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                                                                                 A",
    "A                                                                                                 A",
    "A                                                                                                 A",
    "A         BB                                                              BB                      A",
    "A        BBBBBB    BB                                 BBBBBB            BBBBBB      BB            A",
    "A      BBBBBBBBBBBBBBBB              BBBBB           BBBBBBBBB  B  BB  BBBBBBBBBB BBBBBB          A",
    "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA",
    "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA",
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 640), "SFML works!");
    sf::Texture t1;

    if (!t1.loadFromFile("D:\\видео\\grass_path_side.png")){
        return -1;
    }

    sf::Sprite map(t1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'A' || TileMap[i][j] == 'B') {
                    map.setTextureRect(sf::IntRect(0, 0, size_texture, size_texture));
                }
                else{
                    continue;
                }
                map.setPosition(j * size_texture, i * size_texture);
                window.draw(map);
            }
        }
        window.display();
    }
    return 0;
}
