#include "stdafx.h"
#include "xlogfilescan.h"

#define XLOG_SURFIX  _T(".xlog")


XlogFileScan::XlogFileScan(LPCWSTR path){
	if(path != NULL)m_scanPath = path;
}

XlogFileScan::~XlogFileScan(){

}

void XlogFileScan::onFile(LPCWSTR dir, LPCWSTR fileName){
	TCHAR *pathname = new TCHAR[MAX_PATH];
	wsprintf(pathname, _T("%s\\%s"), dir, fileName);
	if(isXlogFile(pathname)){
		m_fileXlogs.Add(pathname);
	}
	delete []pathname;
}

void XlogFileScan::onDirectory(LPCWSTR dir, LPCWSTR dirName){

}

BOOL XlogFileScan::isXlogFile(CString pathname){
	DWORD flag = ::GetFileAttributes(pathname);
	if(0xffffffff != flag && FILE_ATTRIBUTE_DIRECTORY != flag){
		if(pathname.Find(XLOG_SURFIX) != -1 && 
			wcscmp(pathname.Mid(pathname.GetLength() - 5), XLOG_SURFIX) == 0){
			return TRUE;
		}
	}
	return FALSE;
}

BOOL XlogFileScan::isDirectory(LPCWSTR pathname){
	DWORD flag = ::GetFileAttributes(pathname);
	return (0xffffffff != flag && FILE_ATTRIBUTE_DIRECTORY == flag);
}

int XlogFileScan::scan(CString path, BOOL recurseSubDir){
	//清空所有记录
	m_fileXlogs.RemoveAll();

	if(!isDirectory(path)){
		if(isXlogFile(path)){
			m_fileXlogs.Add(path);
		}else{
			return 0;
		}
	}else{
		CFileScan::scan(path.GetBuffer(), recurseSubDir);
	}

	return m_fileXlogs.GetCount();
}

BOOL XlogFileScan::genDecodeFileName(const CString &in, CString &out){
	CString filename(in);
	filename.Replace(XLOG_SURFIX, L"_.log");
	out = filename;
	return 1;
}