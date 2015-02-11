// Serialize example
// This example shows writing JSON string with writer directly.

#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filestream.h"   // wrapper of C stream for prettywriter as output
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

#include "rapidjson/reader.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "Player.h"

#include "Serializable.h"
#include "CMyString.h"

using namespace rapidjson;
using namespace std;

struct MyHandler {
    bool Null() { cout << "Null()" << endl; return true; }
    bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
    bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
    bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
    bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
    bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
    bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
    bool String(const char* str, SizeType length, bool copy) {
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
    bool StartArray() { cout << "StartArray()" << endl; return true; }
    bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};

struct Handler{
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
};

void test_life()
{
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    
    MyHandler handler;
    Reader reader;
    StringStream ss(json);
    reader.Parse(ss, handler);
    
}

std::string test_serialize(Player &p){
    std::cout << "start ...................." << endl;
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    FastWriter fw(writer);
    fw.startObject();
    p.serialize(fw);
    fw.endObject();
    return buf.GetString();
}
void test_deserialize(const std::string & data){
    
    std::cout << data.c_str() << std::endl;
    
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    
    Player pp;
    FastReader fr(doc);
    pp.deserialize(fr);
    
    std::cout << "-------print result--------" << std::endl;
    
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    FastWriter fw(writer);
    fw.startObject();
    pp.serialize(fw);
    fw.endObject();
    std::cout << buf.GetString() << std::endl;

}

void test_move(){
        {
            {
                std::cout << "test-----------" <<std::endl;
                std::vector<CMyString> heros;
                //        heros.push_back({"name1",11,88.0});
                //        heros.push_back({});
                //        heros.push_back(Hero());
                CMyString mys("hello");
                mys.len = 11;
                mys.nothing = 101;
                std::cout<<"---------"<<mys.nothing<<std::endl;
    //            heros.push_back(mys);
                heros.push_back(mys);
                std::cout << "nothing" << heros.at(0).nothing << std::endl;
    
            }
            //Hero被析构了两次
            std::cout << "test------- end2" << std::endl;
        }

}
void fill_player(Player &p){
    p.name = "higgs";
    p.age = 10;
    p.level = 101;
    p.skills.insert({ 3, 2 });
    p.skills.insert({ 2, 23});
    p.skills.insert({ 11, 23 });
    
    p.titles.push_back("title1");
    p.titles.push_back("title2");
    p.titles.push_back("title3");
    
    p.preference.nothing = 11;
    p.preference.music = true;
    p.preference.temp ="perference";
    {
    {
        Hero h1("hero1",12,188.0);
        Hero h2("hero2",121,188.0);
        Hero h3("hero3",155,188.0);
        p.heros.push_back(h1);
        p.heros.push_back(h2);
        p.heros.push_back(h3);
    }
        cout << "----------destroy heros" << endl;
    }
}
int main(int, char*[]) {
    Player p;
    fill_player(p);
    cout << "------------end fill player------" <<endl;
    std::string data = test_serialize(p);
    cout << "-----result------" << endl;
    cout << data.c_str() << endl;
    cout << "-----------deserialize------" << endl;
    test_deserialize(data);
    return 0;
}
