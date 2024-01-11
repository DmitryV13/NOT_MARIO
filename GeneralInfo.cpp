#include "stdafx.h"
#include "GeneralInfo.h"

    GeneralInfo::GeneralInfo(short HP_): HP(HP_){
    }
    
    const Vector2f GeneralInfo::getVelocity() const{
        return velocity;
    }

    const short GeneralInfo::getHP() const{
        return HP;;
    }

    const FloatRect GeneralInfo::getGlobalBounds() const{
        return globalBounds;
    }

    const Vector2f GeneralInfo::getPosition() const{
        return position;
    }

    void GeneralInfo::changeVelocityX(int x){
        velocity.x += x;
    }

    void GeneralInfo::changeVelocityY(int y) {
        velocity.y += y;
    }

    void GeneralInfo::setVelocityX(int x){
        velocity.x = x;
    }

    void GeneralInfo::setVelocityY(int y){
        velocity.y = y;
    }

    void GeneralInfo::changeHP(short z){
        HP += z;
    }

    void GeneralInfo::setGlobalBounds(FloatRect new_gb){
        globalBounds = new_gb;
    }

    void GeneralInfo::setPosition(Vector2f new_position){
        position = new_position;
    }
