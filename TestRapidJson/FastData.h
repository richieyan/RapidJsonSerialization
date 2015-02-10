//
//  FastData.h
//  TestCpp
//
//  Created by Richie Yan on 2/9/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestCpp__FastData__
#define __TestCpp__FastData__


#include <vector>
#include <string>
#include "FastWriter.h"

class Person :public Serializable {
public:
    Person(){}
    Person(const std::string& name, unsigned age,float miles,double gold,int level) : name_(name), age_(age),miles_(miles),gold_(gold),level_(level) {
    }
    virtual ~Person();
    
public:
    //if base class,obj should be false
    virtual void serialize(FastWriter& writer) const {
        using namespace rapidjson;
        writer.put("name",name_);
        writer.put("age",age_);
        writer.put("miles", miles_);
        writer.put("gold",gold_);
        writer.put("level", level_);
    }
    
    virtual void deserialize(const rapidjson::Value& data){
        if(data.HasMember("name")){
            const rapidjson::Value& value = data["name"];
            name_ = value.GetString();
        }
    }
    
private:
    std::string name_;
    unsigned age_;
    float miles_;
    double gold_;
    int level_;
};

Person::~Person() {
}

class Education : public Serializable {
public:
    Education(){}
    Education(const std::string& school, double GPA) : school_(school), GPA_(GPA) {}
    
    void serialize(FastWriter& writer) const {
        using namespace rapidjson;
        writer.put("school",school_);
        writer.put("GPA",GPA_);
        std::vector<int> vec = {1,2,3,4,5};
        writer.putBasicType("kkk", vec);
    }
    virtual void deserialize(const rapidjson::Value& data){
        if(data.HasMember("school")){
            const rapidjson::Value& value = data["school"];
            school_ = value.GetString();
        }
        if(data.HasMember("GPA")){
            const rapidjson::Value& value = data["GPA"];
            GPA_ = value.GetDouble();
        }
    }
private:
    std::string school_;
    double GPA_;
};

class Dependent : public Person {
public:
    Dependent(){};
    Dependent(const std::string& name, unsigned age, Education* education = 0) : Person(name, age,1.0,2,3), education_(education) {}
    Dependent(const Dependent& rhs) : Person(rhs), education_(0) { education_ = (rhs.education_ == 0) ? 0 : new Education(*rhs.education_); }
    virtual ~Dependent();
    
    Dependent& operator=(const Dependent& rhs) {
        if (this == &rhs)
            return *this;
        delete education_;
        education_ = (rhs.education_ == 0) ? 0 : new Education(*rhs.education_);
        return *this;
    }
    
    void serialize(FastWriter& writer) const {
        Person::serialize(writer);
        if(education_){
            writer.put("education",education_);
        }else{
            writer.putNull("education");
        }
    }
    
    virtual void deserialize(const rapidjson::Value& data){
        Person::deserialize(data);
        if(data.HasMember("education")){
            const rapidjson::Value& value = data["education"];
            if(value.IsObject() && !value.IsNull()){
                auto edu = new Education();
                //            Education e;
                //            auto v = new (decltype(e));
                edu->deserialize(value);
                education_ = edu;
            }else{
                std::cout << " value is not object" << std::endl;
            }
        }
    }
    
private:
    Education *education_ = nullptr;
};

Dependent::~Dependent() {
    if(education_!=nullptr)
        delete education_;
}

class Employee : public Person {
public:
    Employee(){};
    Employee(const std::string& name, unsigned age, bool married) : Person(name, age,10.1,11.0,3), dependents_(), married_(married) {}
    virtual ~Employee();
    
    void AddDependent(const Dependent& dependent) {
        dependents_.push_back(dependent);
    }
    
    void serialize(FastWriter& writer) const {
        Person::serialize(writer);
        writer.put("married",married_);
        std::vector<int> arr;
        std::vector<Dependent> dd;
        writer.put("dependents", dependents_);
    }
    virtual void deserialize(const rapidjson::Value& data){
        Person::deserialize(data);
        if(data.HasMember("dependents")){
            const rapidjson::Value& value = data["dependents"];
            if(value.IsArray()){
                for(int i=0;i<value.Size();i++){
                    Dependent d;
                    d.deserialize(value[i]);
                    dependents_.push_back(d);
                }
            }
        }
    }
private:
    std::vector<Dependent> dependents_;
    bool married_;
};

Employee::~Employee() {
}
#endif /* defined(__TestCpp__FastData__) */
