//
//  CMyString.h
//  TestRapidJson
//
//  Created by Richie Yan on 2/11/15.
//  Copyright (c) 2015 Richie Yan. All rights reserved.
//

#ifndef __TestRapidJson__CMyString__
#define __TestRapidJson__CMyString__
#include <iostream>

using namespace std;

class CMyString{
public:
    CMyString(const char* src = nullptr){
        cout << "CMyString" << endl;
        if(src == nullptr){
            m_data = new char[1];
            *m_data='\0';
        }else{
            m_data = new char[strlen(src)+1];
            strcpy(m_data, src);
        }
    }
    CMyString(const CMyString&s)
    {
        cout << "CMyString &"<< endl;
        m_data = new char[strlen(s.m_data)+1];
        strcpy(m_data, s.m_data);
    }
    
    CMyString(CMyString&&s){
        cout << "CMyString &&"<< endl;
        m_data = new char[strlen(s.m_data)+1];
        strcpy(m_data, s.m_data);
    }
    
    ~CMyString(){
        cout << "~CMyString"<< endl;
        delete [] m_data;
        m_data=nullptr;
    }
    
    CMyString &operator=(const CMyString&s){
        cout <<"CMyString &operator=" << endl;
        if(this!=&s){
            delete [] m_data;
            m_data = new char[strlen(s.m_data)+1];
            strcpy(m_data, s.m_data);
        }
        return *this;
    }
    
    CMyString& operator=(CMyString&&s){
        cout <<"CMyString &operator= &&" << endl;
        if(this!=&s){
            delete [] m_data;
            m_data = s.m_data;
            s.m_data = nullptr;
        }
        return *this;
    }
    
    int len;
    int nothing;
    
private:
    char* m_data;
};
#endif /* defined(__TestRapidJson__CMyString__) */
