#include "stdafx.h"
#include "chest.h"

void Chest::filled_in()
{
    //items.resize(8);
    std::string fNum = std::to_string(fileNumber);
    std::string path = "Maps/Resourse/Filling"+fNum+".txt";
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "Error: the file is not open or not found " << std::endl;
        return;
    }
    std::string name_;
    int amount_, max_, index_, frame_numbers, rectLeft, rectTop, rectWidth, rectHeight;
    bool access_ = true;
    while (fin >> name_ >> amount_ >> max_ >> index_ >> frame_numbers >> rectLeft >> rectTop >> rectWidth >> rectHeight)
    {
        items.push_back(new WarehouseItem{ name_, amount_, max_, access_, index_, sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight), frame_numbers });
    }

    fin.close();

}

Chest::~Chest()
{
    for (auto& it : items) delete it;
}

Chest::Chest() : AnimObject()
{
    object_type = OBJECT_TYPE::CHEST;
    this->fileNumber = 0;
	this->opened = false;
}

Chest::Chest(std::string name, float position_x, float position_y, short int size_W, short int size_H, short int anim_factor, short int anim_quantity, float anim_time, short int fileNumber) 
	: AnimObject(name, position_x, position_y, size_W, size_H, anim_factor, anim_quantity, anim_time)
{
    object_type = OBJECT_TYPE::CHEST;
    this->fileNumber = fileNumber;
	this->opened = false;
    filled_in();
}

vector<WarehouseItem*>& Chest::getItems()
{
    return items;
}

void Chest::useObject()
{
    if (opened) 
        opened = false;
    else
        opened = true;
    //std::cout << opened << std::endl;
}

void Chest::animation_object()
{
    if (opened)
    {
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = object_S.getTextureRect();
            pos.left += animation_factor;

            if (pos.left >= animation_factor * animation_quantity)
            {
                pos.left -= animation_factor;
                object_S.setTextureRect(pos);
                return;
            }
            object_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
    else
    {
        if (animationTimer.getElapsedTime().asSeconds() >= animation_time)
        {
            sf::IntRect pos = object_S.getTextureRect();
            pos.left -= animation_factor;

            if (pos.left < 0)
            {
                pos.left += animation_factor;
                object_S.setTextureRect(pos);
                return;
            }
            object_S.setTextureRect(pos);
            animationTimer.restart();
        }
    }
}
