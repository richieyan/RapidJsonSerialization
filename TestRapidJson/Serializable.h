//
//  Serializable.h
//
//  Created by Richie Yan on 2/10/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//
#pragma once

#include <string>
#include <vector>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "TypeConverter.h"
#include "FastReader.h"
#include "FastWriter.h"

enum class FieldType{
    INT,
    UINT,
    INT64,
    UINT64,
    DOUBLE,
    STRING,
    BOOLEAN,
    VECTOR_INT,//vector<int>
    VECTOR_STRING,//vector<string>
    MAP_INT_INT,//map<int,int>
    MAP_STRING_INT,//map<string,int>
    MAP_STRING_STRING,//map<string,string>
    CUSTOM_OBJECT,//自定义对象类型
};

enum class ExtraType {
    
};

struct Field {
    std::string ID;
    FieldType type;
    void* addr;
};

class Serializable {
public:
    Serializable(){
    }
    
    virtual void serialize(FastWriter& writer){
        __serialize(writer);
        __exSerialize(writer);
    }
    
    virtual void deserialize(FastReader & reader){
        __deserialize(reader);
        __exDeserialize(reader);
    }
    
protected:
    
    virtual void regFields() = 0;
    
    ///serialize custom object
    virtual void __exSerialize(FastWriter& writer){
        
    }
    
    ///deserialize custom object
    virtual void __exDeserialize(FastReader & reader){
        
    }
    
    void __deserialize(FastReader & reader);
    void __serialize(FastWriter& writer) const;
    void reg(std::string ID, FieldType type, void* addr);
    
    //nest serialize object
    void put(FastWriter& writer, const std::string& key, Serializable & value);
    
    template<typename E>
    void put(FastWriter& writer, const std::string& key, std::vector<E>& valueArray);
    
    template<typename T>
    void get(FastReader& reader,const std::string& key,T & value){
        Serializable& obj = dynamic_cast<Serializable&>(value);
        FastReader objReader(reader.getRaw(key));
        obj.deserialize(objReader);
    }
    
    template<typename T>
    void get(FastReader& reader,const std::string& key,std::vector<T> & data){
        auto & rawValue = reader.getRaw(key);
        if(rawValue.IsArray()){
            for(int i =0;i<rawValue.Size();i++){
                T temp;
                Serializable& obj = temp;
                FastReader objReader(rawValue[i]);
                obj.deserialize(objReader);
                data.push_back(std::move(temp));
            }
        }else{
            //should be an error
        }
        
        
    }
    
private:
    std::vector<Field> __fields;
};

void Serializable::put(FastWriter& writer,const std::string& key, Serializable & value){
    writer.putValue(key);
    writer.startObject();
    value.serialize(writer);
    writer.endObject();
}

template<typename E>
void Serializable::put(FastWriter& writer,const std::string& key, std::vector<E>& valueArray){
    writer.putValue(key);
    writer.startArray();
    for (E& ele : valueArray) {
        Serializable* obj = dynamic_cast<Serializable*>(&ele);
        writer.startObject();
        obj->serialize(writer);
        writer.endObject();
    }
    writer.endArray();
}

void Serializable::reg(std::string ID, FieldType type, void* addr){
    __fields.push_back({ID,type,addr});
}

void Serializable::__serialize(FastWriter& writer) const{
    for(auto & f:__fields){
        writer.putValue(f.ID);
        switch (f.type) {
            case FieldType::INT:
                writer.putValue(*(int*)f.addr);
                break;
            case FieldType::UINT:
                writer.putValue(*(uint*)f.addr);
                break;
            case FieldType::INT64:
                writer.putValue(*(int64_t*)f.addr);
                break;
            case FieldType::UINT64:
                writer.putValue(*(uint64_t*)f.addr);
                break;
            case FieldType::DOUBLE:
                writer.putValue(*(double*)f.addr);
                break;
            case FieldType::STRING:
                writer.putValue(*(std::string*)f.addr);
                break;
            case FieldType::BOOLEAN:
                writer.putValue(*(bool*)f.addr);
                break;
            case FieldType::VECTOR_INT:
                writer.putBasicValue(*(std::vector<int>*)f.addr);
                break;
            case FieldType::VECTOR_STRING:
                writer.putBasicValue(*(std::vector<std::string>*)f.addr);
                break;
            case FieldType::MAP_INT_INT:
                writer.putBasicValue(*(std::map<int,int>*)f.addr);
                break;
            case FieldType::MAP_STRING_INT:
                writer.putBasicValue(*(std::map<std::string,int>*)f.addr);
                break;
            case FieldType::MAP_STRING_STRING:
                using namespace std;
                writer.putBasicValue(*(map<string,string>*)f.addr);
                break;
            default:
                break;
        }
    }
    
}
void Serializable::__deserialize(FastReader & reader){
    for(auto & f:__fields){
        switch (f.type) {
            case FieldType::INT:
                (*(int*)f.addr) = reader.get<int>(f.ID);
                break;
            case FieldType::UINT:
                (*(uint*)f.addr) = reader.get<uint>(f.ID);
                break;
            case FieldType::INT64:
                (*(int64_t*)f.addr) = reader.get<int64_t>(f.ID);
                break;
            case FieldType::UINT64:
                (*(uint64_t*)f.addr) = reader.get<uint64_t>(f.ID);
                break;
            case FieldType::DOUBLE:
                (*(double*)f.addr) = reader.get<double>(f.ID);
                break;
            case FieldType::STRING:
                (*(std::string*)f.addr) = reader.get<std::string>(f.ID);
                break;
            case FieldType::BOOLEAN:
                (*(bool*)f.addr) = reader.get<bool>(f.ID);
                break;
            case FieldType::VECTOR_INT:
                (*(std::vector<int>*)f.addr) = reader.getVector<int>(f.ID);
                break;
            case FieldType::VECTOR_STRING:
                (*(std::vector<std::string>*)f.addr) = reader.getVector<std::string>(f.ID);
                break;
            case FieldType::MAP_INT_INT:
                (*(std::map<int,int>*)f.addr) = reader.getMap<int, int>(f.ID);
                break;
            case FieldType::MAP_STRING_INT:
                (*(std::map<std::string,int>*)f.addr) = reader.getMap<std::string, int>(f.ID);
                break;
            case FieldType::MAP_STRING_STRING:
                using namespace std;
                (*(map<string,string>*)f.addr) = reader.getMap<string, string>(f.ID);
                break;
            default:
                break;
        }
    }
}


