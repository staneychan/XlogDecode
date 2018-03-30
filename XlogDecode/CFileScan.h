#pragma once

class CFileScan{
protected:
	CFileScan();
	~CFileScan();

	virtual void onFile(LPCWSTR dir, LPCWSTR fileName) = 0;
	virtual void onDirectory(LPCWSTR dir, LPCWSTR dirName) = 0;
	void scan(LPWSTR path, BOOL recurseSubDir = FALSE);
public:

};