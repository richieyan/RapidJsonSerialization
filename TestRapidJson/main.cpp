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

#include "FastData.h"
#include "FastReader.h"

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
    
    using namespace fs;
    
    std::vector<Employee> employees;

    employees.push_back(Employee("Milo YIP", 34, true));
    employees.back().AddDependent(Dependent("Lua YIP", 3, new Education("Happy Kindergarten", 3.5)));
    employees.back().AddDependent(Dependent("Mio YIP", 1));
    
    employees.push_back(Employee("Percy TSE", 30, false));
    
    StringBuffer buf;
    StringWriter bufWriter(buf);
    FastWriter writer(bufWriter);
    writer.putValue(employees);
    std::cout << buf.GetString() << std::endl;
    Document d;
    d.Parse(buf.GetString());
    employees.clear();
    if(d.IsArray()){
        for (int i=0; i<d.Size(); i++) {
            Employee e;
            e.deserialize(d[i]);
            employees.push_back(e);
        }
    }
    std::cout << " deserialize>>>>" << endl;
    buf.Clear();
    
    StringBuffer buf2;
    StringWriter bufWriter2(buf2);
    FastWriter writer2(bufWriter2);
    
    writer2.putValue(employees);
    std::cout << buf2.GetString() << std::endl;
    
    
    return 0;
}
