#pragma once

//enum OpenFileFlags {
//
//	FILE_FLAG_READ = 0x00000,
//	FILE_FLAG_WRITE = 0x00001,
//	FILE_FLAG_READWRITE = 0x00002,
//	modeRead =         (int) 0x00000,
//	modeWrite =        (int) 0x00001,
//	modeReadWrite =    (int) 0x00002,
//	shareCompat =      (int) 0x00000,
//	shareExclusive =   (int) 0x00010,
//	shareDenyWrite =   (int) 0x00020,
//	shareDenyRead =    (int) 0x00030,
//	shareDenyNone =    (int) 0x00040,
//	modeNoInherit =    (int) 0x00080,
//	modeCreate =       (int) 0x01000,
//	modeNoTruncate =   (int) 0x02000,
//	typeText =         (int) 0x04000, // typeText and typeBinary are
//	typeBinary =       (int) 0x08000, // used in derived classes only
//	osNoBuffer =       (int) 0x10000,
//	osWriteThrough =   (int) 0x20000,
//	osRandomAccess =   (int) 0x40000,
//	osSequentialScan = (int) 0x80000,
//};
/*
SEEK_CUR 
Current position of file pointer 
SEEK_END 
End of file 
SEEK_SET 
Beginning of file 
*/

class CFileEx
{
public:
	CFileEx();
	~CFileEx();

	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

	//打开文件,常用:ab(没有则创建,已有则在文件后添加数据(可能要先SeekToEnd),b是指二进制)
	BOOL Open(LPCTSTR pszPathName, TCHAR *pszOpenFlags);
	BOOL Open(LPCSTR pszPathName, CHAR *pszOpenFlags);
	BOOL Close();
	LONG Length();
	UINT Read(void* buffer, UINT size);
	BOOL Write(void* buffer, UINT size);
	void SeekToEnd();
	void SeekToBegin();
	int  Seek(LONG lOff, int nFrom);

	FILE* GetFileHandle(){ return m_pFileStream; }
protected:
	LONG _GetLength();


	FILE	*m_pFileStream;
	LONG	m_lFileLength;
};