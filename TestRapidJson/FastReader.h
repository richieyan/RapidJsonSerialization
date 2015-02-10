#pragma once

#include <string>
#include <vector>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"

#include "TypeConverter.h"

class FastReader {
public:
	FastReader(rapidjson::Value & data):m_data(data) {
	}
	
	template<typename Key,typename Value>
	std::map<Key, Value> getMap(const std::string & name){
		std::map<Key, Value> rt;
		auto & value = m_data[name.c_str()];;
		if (value.IsObject()){
			for (auto m = value.MemberBegin(); m != value.MemberEnd(); m++){
				auto key = TypeConverter::convert<Key>(m->name.GetString());
				auto value = convert<Value>(m->value);
				rt.insert(std::make_pair(key, value));
			}
		}
		return rt;
	}
    
    template<typename Value>
    std::vector<Value> getVector(const std::string & name){
        std::vector<Value> rt;
        auto & value = m_data[name.c_str()];;
        if (value.IsArray()){
            for(int i=0;i<value.Size();i++){
                rt.push_back(convert<Value>(value[i]));
            }
        }
        return rt;
    }
	

	template<typename TValue>
	TValue get(const std::string & name){
		const rapidjson::Value& value = m_data[name.c_str()];
		return convert<TValue>(value);
	}

	template<typename TValue>
	TValue convert(const rapidjson::Value& value){
		TValue rt;
		return rt;
	}

private:
	rapidjson::Value & m_data;

	bool check(const std::string &name){
		return m_data.HasMember(name.c_str());
	}
	
};

template<> int64_t FastReader::convert(const rapidjson::Value& value){
    return value.GetInt64();
}

template<> uint64_t FastReader::convert(const rapidjson::Value& value){
    return value.GetUint64();
}

template<> unsigned FastReader::convert(const rapidjson::Value& value){
    return value.GetUint();
}

template<> double FastReader::convert(const rapidjson::Value& value){
    return value.GetDouble();
}

template<> bool FastReader::convert(const rapidjson::Value& value){
    return value.GetBool();
}

template<> int FastReader::convert(const rapidjson::Value& value){
    return value.GetInt();
}

template<> std::string FastReader::convert(const rapidjson::Value& value){
    return value.GetString();
}

