#include "stdafx.h"
#include "GeneralInfo.h"

    GeneralInfo::GeneralInfo(int HP_, int mana_)
        : HP(HP_), mana(mana_), max_mana(mana), max_HP(HP), stan_time(0.f), mana_is_used(false){
    }
    
    const Vector2f GeneralInfo::getVelocity() const{
        return velocity;
    }

    const float GeneralInfo::getHP() const{
        return HP;;
    }

    float* GeneralInfo::getHp(){
        return &HP;
    }

    float* GeneralInfo::getMana()
    {
        return &mana;
    }

    float GeneralInfo::getMaxMana(){
        return max_mana;
    }

    const float GeneralInfo::getMaxHP(){
        return max_HP;
    }

    const FloatRect GeneralInfo::getGlobalBounds() const{
        return globalBounds;
    }

    const Vector2f GeneralInfo::getPosition() const{
        return position;
    }

    float GeneralInfo::getStanTime(){
        return stan_time;
    }

    void GeneralInfo::changeVelocityX(float x){
        velocity.x += x;
    }

    void GeneralInfo::changeVelocityY(float y) {
        velocity.y += y;
    }

    bool GeneralInfo::changeMana(float x){
        if (mana + x < 0)
            return false;
        mana += x;
        if (mana >= max_mana) {
            mana = max_mana;
        }
        return true;
    }

    void GeneralInfo::setVelocityX(float x){
        velocity.x = x;
    }

    void GeneralInfo::setVelocityY(float y){
        velocity.y = y;
    }

    void GeneralInfo::setStanTime(float new_st){
        stan_time = new_st;
    }

    void GeneralInfo::changeHP(short z){
        HP += z;
    }

    bool GeneralInfo::isManaUsed(){
        return mana_is_used;
    }

    void GeneralInfo::setGlobalBounds(FloatRect new_gb){
        globalBounds = new_gb;
    }

    void GeneralInfo::setPosition(Vector2f new_position){
        position = new_position;
    }

    void GeneralInfo::setManaUtilisation(bool used){
        mana_is_used = used;
    }
