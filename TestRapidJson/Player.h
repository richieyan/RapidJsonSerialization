#pragma once

#include <string>
#include <vector>
#include <map>

#include "Serializable.h"

class Player : public Serializable
{
public:
	Player();
	~Player();

	virtual void serialize(FastWriter& writer) const{
        __serialize(writer);
	}

	virtual void deserialize(FastReader & reader) {
        __deserialize(reader);
	}


public:
	int level;
	int age;
	std::string name;
	std::map<int, int> skills;//key-value,key must be string
    std::vector<std::string> titles;

private:

};

Player::Player()
{
    reg("1", FieldType::INT, &level);
    reg("2", FieldType::INT, &age);
    reg("3", FieldType::STRING, &name);
    reg("4", FieldType::MAP_INT_INT, &skills);
    reg("5", FieldType::VECTOR_STRING, &titles);
}

Player::~Player()
{
}