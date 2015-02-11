#pragma once

#include <string>
#include <vector>
#include <map>

#include "Serializable.h"
#include "Hero.h"
#include "Preference.h"

class Player : public Serializable
{
public:
	Player();
	~Player();

protected:
    
    virtual void __exSerialize(FastWriter& writer){
        Serializable::put(writer, "ex1", preference);
//        Serializable::put(writer, "ex2", heros);
    }
    
    virtual void __exDeserialize(FastReader & reader) {
        Serializable::get(reader,"ex1",preference);
//        Serializable::get(reader,"ex2",heros);
    }
    
public:
	int level;
	int age;
	std::string name;
	std::map<int, int> skills;//key-value,key must be string
    std::vector<std::string> titles;
    std::vector<Hero> heros;
    Preference preference;
protected:
    virtual void regFields(){
        reg("1", FieldType::INT, &level);
        reg("2", FieldType::INT, &age);
        reg("3", FieldType::STRING, &name);
        reg("4", FieldType::MAP_INT_INT, &skills);
        reg("5", FieldType::VECTOR_STRING, &titles);
    }
};

Player::Player()
{
    regFields();
}

Player::~Player()
{
}