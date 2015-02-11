//
//  Hero.h
//  TestRapidJson
//
//  Created by Richie Yan on 2/11/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestRapidJson__Hero__
#define __TestRapidJson__Hero__

#include "Serializable.h"

class Hero : public Serializable {
public:
    std::string name;
    int level;
    double gold;
    std::vector<int> skills;
    std::map<std::string,int> nothing;
    
    virtual void regFields(){
        //reg fields;
        reg("1",FieldType::STRING,&name);
        reg("2",FieldType::INT,&level);
        reg("3",FieldType::DOUBLE,&gold);
        reg("4",FieldType::VECTOR_INT,&skills);
        reg("5",FieldType::MAP_STRING_INT,&nothing);
    }
    
    Hero(){
    }
    
    Hero(std::string name_,int level_,double gold_):name(name_),level(level_),gold(gold_){
    }
    
    Hero(const Hero&s)
    {
        std::cout << "hero copy constructor" <<std::endl;
        this->name = s.name;
        this->level = s.level;
    }

};

#endif /* defined(__TestRapidJson__Hero__) */
