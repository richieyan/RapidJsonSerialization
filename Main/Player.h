#pragma once

#include <string>
#include <vector>
#include <map>

#include "Serializable.h"
#include "Hero.h"
#include "Preference.h"

class Player : public Serializable
{
protected:
    virtual void __exSerialize(FastWriter& writer){
        Serializable::put(writer, "ex1", preference);
        Serializable::put(writer, "ex2", heros);
        Serializable::put(writer, "ex3", hero);
    }
    
    virtual void __exDeserialize(FastReader & reader) {
        Serializable::get(reader,"ex1",preference);
        Serializable::get(reader,"ex2",heros);
        hero = new Hero();
        Serializable::get(reader, "ex3", hero);
    }
    
public:
	int level;
	int age;
	std::string name;
	std::map<int, int> skills;//key-value,key must be string
    std::vector<std::string> titles;
    std::vector<Hero> heros;
    Hero* hero = nullptr;
    Hero* master = nullptr;
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
