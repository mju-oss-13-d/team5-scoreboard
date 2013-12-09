#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

class CLog
{
public:
	CLog(void);
	virtual ~CLog(void);
	void MakeLog(void);
	void StrAdd(const char *str);
private:
	string m_history;
	stringstream m_temp;
	
};

