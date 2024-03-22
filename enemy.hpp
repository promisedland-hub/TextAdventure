#if !defined(ENEMY_HPP)
#define ENEMY_HPP 1

#include <iostream>
#include <sstream>
#include <fstream>

class Enemy
{
private:
    int _type;
    std::string _name;
    int _hitpoints;
    int _strenght;

public:
    Enemy(int);
    void showStats();
    void attack();
    void save(std::ofstream &outputFile);
    void load(std::ifstream &inputFile);

    // Getter
    int getType() const;
    std::string getName() const;
    int getHitpoints() const;
    int getStrength() const;

    // Setter
    void setType(int);
    void setName(std::string);
    void setHitpoints(int);
    void setStrength(int);
};
#endif // ENEMY_HPP
