#include "enemy.hpp"

Enemy::Enemy(int i) : _type(i)
{
    if (_type == 1)
    {
        _name = "Goblin";
        _hitpoints = 20;
        _strenght = 10;
    }
    else if (_type == 2)
    {
        _name = "Ogre";
        _hitpoints = 50;
        _strenght = 20;
    }
    else if (_type == 3)
    {
        _name = "Skeleton Archer";
        _hitpoints = 10;
        _strenght = 5;
    }
}

void Enemy::showStats()
{
    std::cout << "Gegner: " << _name << ", Gesundheit: " << _hitpoints << std::endl;
}

void Enemy::attack()
{
    // Implementiere die Logik für den Angriff des Gegners
}
void Enemy::save(std::ofstream &outputFile)
{
    outputFile << "Enemy" << std::endl;
    outputFile << _name << std::endl;
    outputFile << _hitpoints << std::endl;
    outputFile << _strenght << std::endl;
}
void Enemy::load(std::ifstream &inputFile)
{
    inputFile >> _type;
    inputFile >> _name;
    inputFile >> _hitpoints;
    inputFile >> _strenght;
}

// Getter
int Enemy::getType() const
{
    return _type;
}

std::string Enemy::getName() const
{
    return _name;
}

int Enemy::getHitpoints() const
{
    return _hitpoints;
}

int Enemy::getStrength() const
{
    return _strenght;
}

// Setter
void Enemy::setType(int type)
{
    _type = type;
}

void Enemy::setName(std::string name)
{
    _name = name;
}

void Enemy::setHitpoints(int hitpoints)
{
    _hitpoints = hitpoints;
}

void Enemy::setStrength(int strength)
{
    _strenght = strength;
}
