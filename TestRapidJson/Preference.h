//
//  Preference.h
//  TestRapidJson
//
//  Created by Richie Yan on 2/11/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestRapidJson__Preference__
#define __TestRapidJson__Preference__

#include "Serializable.h"

class Preference : public Serializable{
public:
    bool music;
    int nothing;
    std::string temp;
    std::vector<int> testv;
    Preference(){
        regFields();
    }
    virtual void regFields(){
        //reg fields;
        reg("1",FieldType::BOOLEAN,&music);
        reg("2",FieldType::INT,&nothing);
        reg("3",FieldType::STRING,&temp);
//        reg("4",FieldType::VECTOR_INT,&testv);
    }
};
#endif /* defined(__TestRapidJson__Preference__) */
