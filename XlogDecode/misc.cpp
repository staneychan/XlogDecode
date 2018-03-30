#include "stdafx.h"
#include "misc.h"

int GetAppPath(TCHAR *outPath, UINT nLenth)//with \ at the end of the path
{
	if(!outPath || !nLenth){
		return 0;
	}
	if( 0 == GetModuleFileName(NULL , outPath , nLenth) ){
		return 0;
	}
	int nLen = 0;
	for(nLen = (int)wcslen(outPath) - 1 ; nLen >= 0 ;nLen-- ){
		if(outPath[nLen] == '\\'){
			nLen++;//include "\" here
			outPath[nLen] = '\0';
			break;
		}
	}
	return nLen;
}


/************************************************
CharToUnicode
-pszOutBuffer : output buffer
+nOutBufferSize : length of the buffer in TCHAR
+pszInBuffer : input buffer(currently point to the UTF-8 bytes)
+uCodePage : MultiByteToWideChar refer to this codepage 
@return : bytes converted,not character
************************************************/
int CharToUnicode(TCHAR *pszOutBuffer, int nOutBufferSize, const char *pszInBuffer , UINT uCodePage)
{
// CODE_PAGE_CHS	936
// CODE_PAGE_CHT	950
	int nLen = MultiByteToWideChar(uCodePage, 0, pszInBuffer, -1, NULL, 0);
	if(nOutBufferSize < nLen)return 0;

	return MultiByteToWideChar(uCodePage, 0, pszInBuffer, -1, pszOutBuffer, nLen);;
}

int UnicodeToChar(const TCHAR *pszInBuffer, char *outBuffer, int nOutBufferSize, UINT uCodePage)//CP_ACP
{
	int nLen = WideCharToMultiByte(uCodePage, 0, pszInBuffer, -1, NULL, 0, NULL, NULL);
	if(nOutBufferSize < nLen)return 0;

	return WideCharToMultiByte (uCodePage, 0,pszInBuffer, -1,outBuffer , nLen, NULL,NULL);;
}

double sum(char *num0, char *num1)
{
	double val = 0.0;
	if(num0 ==NULL || num1 == NULL)return val;

	val = atof(num0) + atof(num1);
	
	return val;
}

BOOL isDirectory(LPCWSTR pathname){
	DWORD flag = ::GetFileAttributes(pathname);
	return (0xffffffff != flag && FILE_ATTRIBUTE_DIRECTORY == flag);
}