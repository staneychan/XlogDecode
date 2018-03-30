#include "stdafx.h"
#include "cfilescan.h"

CFileScan::CFileScan(){

}

CFileScan::~CFileScan(){

}

void CFileScan::scan(LPWSTR path, BOOL recurseSubDir){

	TCHAR fileName[MAX_PATH];
	wsprintf(fileName, _T("%s\\*"), path);

	WIN32_FIND_DATA wfd;
	HANDLE hFile=::FindFirstFile(fileName, &wfd);
	if(hFile != INVALID_HANDLE_VALUE){
		do
		{
			//������ļ���
			if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
				if(wfd.cFileName[0]=='.')continue;
				onDirectory(path, wfd.cFileName);
				//��Ŀ¼
				if(recurseSubDir){
					TCHAR *subDir = new TCHAR[MAX_PATH];
					wsprintf(subDir, _T("%s\\%s"), path, wfd.cFileName);
					scan(subDir, recurseSubDir);
					delete []subDir;
				}
			}else{//�ļ�
				onFile(path, wfd.cFileName);
			}
		}while(::FindNextFile(hFile,&wfd));
		::FindClose(hFile);
	}

}