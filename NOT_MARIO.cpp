#include "stdafx.h"//for each class
#include "Player.h"
#include "Map.h"
#include "MyView.h"
#include "Game.h"
#include "Menu.h"

using sf::Clock;
using sf::FloatRect;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::View;
using std::cout;
using std::endl;




int main() {
    srand(static_cast<unsigned>(time(0)));
    Menu h(3);

    h.start();


    //Game game(1500,600);
    //
    //while (game.getWindow().isOpen()) {
    //    game.update();
    //    game.render();
    //}
    //sf::RenderWindow menu(sf::VideoMode(1500, 600), "Main Menu", sf::Style::Default);
    //MainMenu mainMenu(menu.getSize().x, menu.getSize().y);
    //while (menu.isOpen()) {
    //    sf::Event event;
    //    while (menu.pollEvent(event)) {
    //        if (event.type == sf::Event::Closed) {
    //            menu.close();
    //        }
    //        if (event.type == sf::Event::KeyReleased) {
    //            if (event.key.code == sf::Keyboard::Up) {
    //                mainMenu.moveUp();
    //            }
    //            if (event.key.code == sf::Keyboard::Down) {
    //                mainMenu.moveDown();
    //            }
    //            if (event.key.code == sf::Keyboard::Return) {
    //                sf::RenderWindow PLAY(sf::VideoMode(1500, 600), "Play");
    //                sf::RenderWindow OPTIONS(sf::VideoMode(1500, 600), "Options");
    //                sf::RenderWindow ABOUT(sf::VideoMode(1500, 600), "About");
    //
    //                int x = mainMenu.mainMenuPressed();
    //                if(x==0){
    //                    while (PLAY.isOpen()) {
    //                        
    //                        Game game(1500,600);
    //                        
    //                        while (game.getWindow().isOpen()) {
    //                            game.update();
    //                            game.render();
    //                        }
    //                        OPTIONS.close();
    //                        ABOUT.close();
    //                        PLAY.clear();
    //                        PLAY.display();
    //                    }
    //                }
    //                if (x == 1) {
    //                    while (OPTIONS.isOpen()) {
    //                        sf::Event event1;
    //                        while (OPTIONS.pollEvent(event1)) {
    //                            if (event1.type == sf::Event::Closed) {
    //                                OPTIONS.close();
    //                            }
    //                            if (event1.type == sf::Event::KeyReleased) {
    //                                if (event1.key.code == sf::Keyboard::Escape) {
    //                                    OPTIONS.close();
    //                                }
    //                            }
    //                        }
    //                        PLAY.close();
    //                        ABOUT.close();
    //                        OPTIONS.clear();
    //                        OPTIONS.display();
    //                    }
    //                }
    //                if (x == 2) {
    //                    while (ABOUT.isOpen()) {
    //                        sf::Event event1;
    //                        while (ABOUT.pollEvent(event1)) {
    //                            if (event1.type == sf::Event::Closed) {
    //                                ABOUT.close();
    //                            }
    //                            if (event1.type == sf::Event::KeyReleased) {
    //                                if (event1.key.code == sf::Keyboard::Escape) {
    //                                    ABOUT.close();
    //                                }
    //                            }
    //                        }
    //                        PLAY.close();
    //                        OPTIONS.close();
    //                        ABOUT.clear();
    //                        ABOUT.display();
    //                    }
    //                }
    //                if (x == 3) {
    //                    menu.close();
    //                }
    //            }
    //        }
    //    }
    //    menu.clear();
    //    mainMenu.draw(menu);
    //    menu.display();
    //}
    //
    //
    return 0;
}