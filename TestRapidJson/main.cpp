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

int main(int, char*[]) {
    
    Player p;
    p.name = "higgs";
    p.age = 10;
    p.level = 101;
    p.skills.insert({ 3, 2 });
    p.skills.insert({ 2, 23});
    p.skills.insert({ 11, 23 });
    p.titles.push_back("title1");
    p.titles.push_back("title2");
    p.titles.push_back("title3");
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    FastWriter fw(writer);
    fw.startObject();
    p.serialize(fw);
    fw.endObject();
    
    std::string data = buf.GetString();
    std::cout << data.c_str() << std::endl;

    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    
    Player pp;
    FastReader fr(doc);
    pp.deserialize(fr);
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    
    rapidjson::StringBuffer buf2;
    rapidjson::Writer<rapidjson::StringBuffer> writer2(buf2);
    FastWriter fw2(writer2);
    writer2.StartObject();
    pp.serialize(fw2);
    writer2.EndObject();
    std::cout << buf2.GetString() << std::endl;

    
    return 0;
}
