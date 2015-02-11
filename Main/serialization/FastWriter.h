//
//  FastWriter.h
//  RapidJsonSerialization
//
//  Created by Richie Yan on 2/10/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestRapidJson__FastWriter__
#define __TestRapidJson__FastWriter__

#include <string>
#include <vector>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "TypeConverter.h"

typedef rapidjson::Writer<rapidjson::StringBuffer> StringWriter;

class FastWriter {
public:
    
    FastWriter(StringWriter& writer) :m_writer(writer){
    }
    
    void startObject(){
        m_writer.StartObject();
    }
    void endObject(){
        m_writer.EndObject();
    }
    
    void startArray(){
        m_writer.StartArray();
    }
    
    void endArray(){
        m_writer.EndArray();
    }
    
    void putNull(const std::string& key){
        putValue(key);
        m_writer.Null();
    }
    
    void put(const std::string& key, std::string value){
        putValue(key);
        putValue(value);
    }
    
    void put(const std::string& key, int value){
        putValue(key);
        putValue(value);
    }
    void put(const std::string& key, unsigned value){
        putValue(key);
        putValue(value);
    }
    
    void put(const std::string& key, long long value){
        putValue(key);
        putValue(value);
    }
    
    void put(const std::string& key, double value){
        putValue(key);
        putValue(value);
    }
    
    void put(const std::string& key, bool value){
        putValue(key);
        putValue(value);
    }
    
    
    template<typename E>
    void put(const std::string& key, const std::vector<E>& valueArray){
        putValue(key);
        putValue(valueArray);
    }
    
    template<typename Key,typename Value>
    void putBasicType(const std::string & key, const std::map<Key, Value>& valueMap){
        putValue(key);
        putBasicValue(valueMap);
    }
    
    template<typename Key,typename Value>
    void putBasicValue(const std::map<Key, Value>& valueMap){
        startObject();
        for (auto& entry : valueMap){
            putValue(TypeConverter::to_string(entry.first));//in json,key must be string
            putValue(entry.second);
        }
        endObject();
    }
    
    template<typename E>
    void putBasicType(const std::string& key, const std::vector<E>& valueArray){
        putValue(key);
        putBasicValue(valueArray);
    }
    
    template<typename E>
    void putBasicValue(const std::vector<E>& valueArray){
        startArray();
        for (const E& ele : valueArray) {
            putValue(ele);
        }
        endArray();
    }
    
    template<typename E>
    void put(const std::string& key, const std::vector<E*>& valueArray){
        putValue(key);
        putValue(valueArray);
    }
    
    /// put values only
    void putValue(uint64_t value){
        m_writer.Uint64(value);
    }
    
    void putValue(int64_t value){
        m_writer.Int64(value);
    }
    void putValue(double value){
        m_writer.Double(value);
    }
    
    void putValue(const std::string & value){
        using namespace rapidjson;
        m_writer.String(value.c_str(), (SizeType)value.length());
    }
    
    void putValue(unsigned value){
        m_writer.Uint(value);
    }
    
    void putValue(int value){
        m_writer.Int(value);
    }
    void putValue(bool value){
        m_writer.Bool(value);
    }

private:

    StringWriter & m_writer;
};

#endif /* defined(__TestRapidJson__FastWriter__) */
