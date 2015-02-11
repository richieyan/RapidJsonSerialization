# RapidJsonSerialization
A simple C++ implementation of serialization by rapid json
####Movtivation
I need a simple and easy implementation of serialiaztion framework, and cannot find a suitable one.<br/>
I use the serialization to store my game data in local storage by key value style. <br/>
I dont like sqlite way to store game data, because i have to handle sql things.<br/>
####Implementation
The rapidjson library is the only dependency.<br/>
Usage:
If you have a simple POD object, all you need to is to register you fields.
```cpp
 	#include "Serializable.h"
	class Player:public Serializable {
		private:
			int level;
			double gold;
			std::string name;
		protected:
			//you must implements this method to register you field that to be serialized
			virtual void regFields(){
        		reg("1", FieldType::INT, &level);
        		reg("2", FieldType::DOUBLE, &gold);
        		reg("3", FieldType::STRING, &name);
    		}
	}

	//in you main.cpp
	Player p;
	//afeter fill p,invoke serialize
	auto result = p.serialize();//to json std::string
```

if you want to nest a object and serialize
```

 	#include "Serializable.h"
 	class Skill:public Serializable {
 	private:
 		int level;
 		std::string name;
 	}
	class Player:public Serializable {
		private:
			int level;
			double gold;
			std::string name;
			Skill skill;
		protected:

			//you must implement this method to register you field that to be serialized
			virtual void regFields(){
        		reg("1", FieldType::INT, &level);
        		reg("2", FieldType::DOUBLE, &gold);
        		reg("3", FieldType::STRING, &name);
    		}

    		//for nest object, you must implement __exSerialize and __exDeserialize
    		//no need to reg the nest object
    		virtual void __exSerialize(FastWriter& writer){
        		Serializable::put(writer, "ex1", skill);
    		}
    		
    		virtual void __exDeserialize(FastReader & reader) {
        		Serializable::get(reader,"ex1",skill);
    		}
	}
```
if you want nest std::vector<YourObject>,please implements copy constructor of YourObject.
```cpp
	public Skill:public Serializable{
	...
	public:
		//must implments your copy constructor
		Skill(const Skill&s)
    	{
    		...
    	}
	}
	class Player:public Serializable {
		private:
			std::vector<Skill> skills;
		protected:
			virtual void __exSerialize(FastWriter& writer){
        		Serializable::put(writer, "ex1", skills);
    		}
    		
    		virtual void __exDeserialize(FastReader & reader) {
        		Serializable::get(reader,"ex1",skills);
    		}
	}
```

I will make a cocos2d-x version later.


