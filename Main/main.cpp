
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"

#include "Serializable.h"
#include "CMyString.h"

using namespace rapidjson;
using namespace std;

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
    Player pp;
    pp.deserialize(data);
    std::cout << "-------print result--------" << std::endl;
    auto rt = pp.serialize();
    std::cout << rt << std::endl;

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
    Hero h1("hero1",12,188.0);
    Hero h2("hero2",121,188.0);
    Hero h3("hero3",155,188.0);
    p.heros.push_back(h1);
    p.heros.push_back(h2);
    p.heros.push_back(h3);

}
int main(int, char*[]) {
    Player p;
    p.hero = new Hero("point_hero",1,22.0);
    fill_player(p);
    cout << "------------end fill player------" <<endl;
    std::string data = test_serialize(p);
    cout << "-----result------" << endl;
    cout << data.c_str() << endl;
    cout << "-----------deserialize------" << endl;
    test_deserialize(data);
    
    Hero h("h111",11,23.0);
    Hero m(h);
    cout << m.name << endl;
    return 0;
}
