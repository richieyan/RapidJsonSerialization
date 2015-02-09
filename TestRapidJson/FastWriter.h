//
//  FastWriter.h
//  TestCpp
//
//  Created by Richie Yan on 2/9/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestCpp__FastWriter__
#define __TestCpp__FastWriter__

#include <string>
#include <vector>
#include <map>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filestream.h"
#include "rapidjson/document.h"


namespace fs {//rapidjson-fast serialization
    typedef rapidjson::Writer<rapidjson::StringBuffer> StringWriter;
    
    class FastWriter;
    
    class Serializable {
        
    public:
        virtual void serialize(FastWriter& writer) const = 0;
        virtual void deserialize(const rapidjson::Value& data) = 0;
    };
    
    class FastWriter {
    public:
        
        FastWriter(StringWriter& writer):m_writer(writer){
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
            writeString(key);
            m_writer.Null();
        }
        
        void put(const std::string& key,std::string value){
            writeString(key);
            writeString(value);
        }
        
        void put(const std::string& key,int value){
            writeString(key);
            m_writer.Int(value);
        }
        void put(const std::string& key,unsigned value){
            writeString(key);
            m_writer.Uint(value);
        }
        
        void put(const std::string& key,long long value){
            writeString(key);
            m_writer.Int64(value);
        }
        
        void put(const std::string& key,long value){
            writeString(key);
            m_writer.Int64(value);
        }
        
        void put(const std::string& key,double value){
            writeString(key);
            m_writer.Double(value);
        }
        
        void put(const std::string& key, bool value){
            writeString(key);
            m_writer.Bool(value);
        }
        
        void put(const std::string& key, Serializable & value){
            writeString(key);
            startObject();
            value.serialize(*this);
            endObject();
        }
        
        void put(const std::string& key, Serializable * value){
            writeString(key);
            startObject();
            value->serialize(*this);
            endObject();
        }
        
        
        template<typename E>
        void put(const std::string& key, const std::vector<E>& valueArray){
            writeString(key);
            putValue(valueArray);
        }
        
        template<typename E>
        void putValue(const std::vector<E>& valueArray){
            startArray();
            for (const E& ele : valueArray) {
                const Serializable* obj = dynamic_cast<const Serializable*>(&ele);
                startObject();
                obj->serialize(*this);
                endObject();
            }
            endArray();
        }
        
        template<typename E>
        void putBasicType(const std::string& key, const std::vector<E>& valueArray){
            writeString(key);
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
        void put(const std::string& key,const std::vector<E*>& valueArray){
            writeString(key);
            putValue(valueArray);
        }
        
        template<typename E>
        void putValue(const std::vector<E*>& valueArray){
            startArray();
            for (const E* ele : valueArray) {
                const Serializable* obj = dynamic_cast<const Serializable*>(ele);
                startObject();
                obj->serialize(*this);
                endObject();
            }
            endArray();
        }
        
        /// put values only
        void putValue(long long value){
            m_writer.Int64(value);
        }
        void putValue(double value){
            m_writer.Double(value);
        }
        void putValue(const std::string & value){
            writeString(value);
        }
        
        void putValue(long value){
            m_writer.Int64(value);
        }
        
        void putValue(unsigned value){
            m_writer.Uint(value);
        }
        
        void putValue(int value){
            m_writer.Int(value);
        }
        
    private:
        void writeString(const std::string& value){
            using namespace rapidjson;
            m_writer.String(value.c_str(), (SizeType)value.length());
        }
        StringWriter & m_writer;
    };
}

#endif /* defined(__TestCpp__FastWriter__) */
