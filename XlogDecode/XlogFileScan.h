#pragma once
#include "cfilescan.h"


class XlogFileScan : public CFileScan{
private:
	BOOL isXlogFile(CString pathname);
	BOOL isDirectory(LPCWSTR pathname);
protected:
	virtual void onFile(LPCWSTR dir, LPCWSTR fileName);
	virtual void onDirectory(LPCWSTR dir, LPCWSTR dirName);

	CStringArray m_fileXlogs;
	CString m_scanPath;
public:
	XlogFileScan(LPCWSTR path = NULL);
	~XlogFileScan();

	int scan(CString path, BOOL recurseSubDir);
	CStringArray & getList(){return m_fileXlogs;}

	static BOOL genDecodeFileName(const CString &in, CString &out);

};