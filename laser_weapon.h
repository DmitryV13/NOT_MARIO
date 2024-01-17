#pragma once
#include "Map.h"
#include "TileMap.h"
#include "GeneralInfo.h"

using sf::Sprite;
using sf::RenderWindow;
using sf::FloatRect;
using sf::View;
using sf::Texture;
using sf::IntRect;
using sf::Clock;
using sf::Vector2f;

enum LASER_ANIMATION_STATES {
    LASER_FIRST = 0, LASER_NEXT
};

class laser_weapon{
protected:
	TileMap* sandbox;
    short attack;
    Texture laser_T;
    Sprite laser_S;
    Sprite laser_area;
    IntRect current_frame;
    Clock animation_timer;
    Clock laser_timer;
    short animation_state;
    bool animation_switch;
    int first;
    int next;
	bool dir_x;


    GeneralInfo* player_info;


	void init_texture();
    void init_sprite();
    void init_variables(int);
    void init_animation();
    void init_physics();
public:
    explicit laser_weapon(TileMap& map, int, float, float, bool, GeneralInfo* player_info_);
    ~laser_weapon() = default;
   
    const bool& get_animation_switch();
    sf::Vector2f get_position() const;
    const FloatRect get_global_bounds() const;
    void set_position(const float x, const float y);
    void render(sf::RenderTarget& target);
    void render_FL(sf::RenderTarget& target);

    //void update(sf::Vector2f);
    void update();
    void update_animation();
    //bool update_collision_x();
    void reset_animation_timer();
    //bool update_collision_x(float x);
    sf::Vector2f calculateEndPosition(float x);
    bool collision_block(int, int);
    bool update_collision_x();
    void damage(sf::Vector2f , sf::Vector2f);


    bool hit_a_wall(const sf::Vector2f& currentPosition, float x) const;
    //bool search_for_enemies();


};

