#include "Log.h"
#include <stdio.h>
#define TEMP_COPY m_history += m_temp.str()
#define CLEAR_TEMP m_temp.str("")

CLog::CLog(void)
{
    
}


CLog::~CLog(void)
{
	
}


void CLog::MakeLog(void)
{
	FILE * fp;
	fopen_s(&fp, "d:\\log.txt", "wt");
	fprintf(fp, "%s\n", m_history);
	fclose(fp);
}


void CLog::StrAdd(const char *str)
{
	m_temp << str << endl;
    TEMP_COPY;
    CLEAR_TEMP;
}
