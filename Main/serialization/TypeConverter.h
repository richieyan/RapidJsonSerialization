#pragma once

#include <sstream>

namespace TypeConverter{

    template<typename T>
    std::string to_string(T value){
        std::ostringstream oss;
        oss<<value;
        return oss.str();
    }
	template <typename T>
	T convert(const std::string& str)
	{
		T var;
		std::istringstream iss;
		iss.str(str);
		iss >> var;
		return var;
	}

	///get type of T
	template <class T>
	struct GetType{
		typedef T type;
	};

	// getyp type of T* of T
	template<class T>
	struct GetType<T*>{
		typedef T type;
	};
}
