#pragma once

/* 
 * GetAppPath: get current application path
 * with \ at the end of the path
 * outPath: The path will be filled if exist
 * nLenth:indicate the outPath length
 */
int GetAppPath(TCHAR *outPath, UINT nLenth);

/************************************************
CharToUnicode
-pszOutBuffer : output buffer
+nOutBufferSize : length of the buffer in TCHAR
+pszInBuffer : input buffer(currently point to the UTF-8 bytes)
+uCodePage : MultiByteToWideChar refer to this codepage 
@return : bytes converted,not character
************************************************/
int CharToUnicode(TCHAR *pszOutBuffer, 
				  int nOutBufferSize, 
				  const char *pszInBuffer , 
				  UINT uCodePage);

int UnicodeToChar(const TCHAR *pszInBuffer, 
				  char *outBuffer, 
				  int nOutBufferSize, 
				  UINT uCodePage);//CP_ACP

double sum(char *num0, char *num1);

#define IS_EMPTY_STR(x)  ((x == NULL?)TRUE:(strcmp(x, "") == 0))
#define NOT_EMPTY_STR(x)  (!IS_EMPTY_STR(x))

BOOL isDirectory(LPCWSTR pathname);