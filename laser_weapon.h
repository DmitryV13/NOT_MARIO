#pragma once
#include "Map.h"
#include "TileMap.h"
using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;


enum LASER_ANIMATION_STATES {
    LASER_FIRST = 0, LASER_NEXT
};
class laser_weapon
{
protected:
	TileMap* sandbox;
    Texture laser_T;
    Sprite laser_S;
    IntRect current_frame;
    Clock animation_timer;
    short animation_state;
    bool animation_switch;
    int first;
    int next;
	bool dir_x;


	void init_texture();
    void init_sprite();
    void init_variables(int);
    void init_animation();
    void init_physics();
public:
    explicit laser_weapon(TileMap& map,int,float,float,bool);
    ~laser_weapon() = default;
   
    const bool& get_animation_switch();
    sf::Vector2f get_position() const;
    const FloatRect get_global_bounds() const;
    void set_position(const float x, const float y);
    void render(sf::RenderTarget& target);
    //void update(sf::Vector2f);
    void update();
    void update_animation();
    //bool update_collision_x();
    void reset_animation_timer();
    //bool search_for_enemies();


};

