//
//  FastReader.h
//  TestCpp
//
//  Created by Richie Yan on 2/9/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestCpp__FastReader__
#define __TestCpp__FastReader__

#include <string>
#include <vector>

#include "rapidjson/reader.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

template <typename T>
struct FastReader {
public:
    FastReader(rapidjson::Document& doc,T& target):m_doc(doc),m_target(target){}
    
    bool Null() {
        return true;
    }
    bool Bool(bool b) {
        return true;
    }
    bool Int(int i) {
        return true;
    }
    bool Uint(unsigned u) {
        return true;
    }
    bool Int64(int64_t i) {
        return true;
    }
    bool Uint64(uint64_t u) {
        return true;
    }
    bool Double(double d) {
        return true;
    }
    bool String(const char* str, rapidjson::SizeType length, bool copy) {
        return true;
    }
    bool StartObject() {
        return true;
    }
    bool Key(const char* str, rapidjson::SizeType length, bool copy) {
        return true;
    }
    bool EndObject(rapidjson::SizeType memberCount) {
        return true;
    }
    bool StartArray() {
        return true;
    }
    bool EndArray(rapidjson::SizeType elementCount) {
        return true;
    }
    
private:
    rapidjson::Document & m_doc;
    bool m_isObj;
    std::string m_key;
    T& m_target;
};

#endif /* defined(__TestCpp__FastReader__) */
