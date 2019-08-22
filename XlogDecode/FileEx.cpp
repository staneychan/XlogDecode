#include "StdAfx.h"
#include "FileEx.h"



CFileEx::CFileEx()
{
	m_pFileStream = NULL;
	m_lFileLength = 0;
}


CFileEx::~CFileEx()
{
	Close();
}

BOOL CFileEx::Open(LPCTSTR pszPathName, TCHAR *pszOpenFlags)
{
	m_pFileStream = _wfopen(pszPathName, pszOpenFlags);
	if(NULL == m_pFileStream){
	//	wprintf(L">>>>>>>>>file does not exist");
		return FALSE;
	}
	m_lFileLength = _GetLength();

	return TRUE;
}

BOOL CFileEx::Open(LPCSTR pszPathName, CHAR *pszOpenFlags)
{
	m_pFileStream = fopen(pszPathName, pszOpenFlags);
	if(NULL == m_pFileStream){
	//	wprintf(L">>>>>>>>>file does not exist");
		return FALSE;
	}
	m_lFileLength = _GetLength();

	return TRUE;
}


BOOL CFileEx::Close()
{
	if(m_pFileStream){
		//0 indicate okay, nonzero indicate failure
		if(0 == fclose(m_pFileStream)){
			m_lFileLength = 0;
			m_pFileStream = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

LONG CFileEx::_GetLength()
{
	LONG lCurPos = 0, lFileLength = 0;

	//Save current pos
	lCurPos = ftell(m_pFileStream);
	//Calculate file size
	fseek(m_pFileStream, 0L, SEEK_END);
	lFileLength = ftell(m_pFileStream);
	//Restore to original pos
	fseek(m_pFileStream, lCurPos, SEEK_SET);

	return lFileLength;
}

LONG CFileEx::Length()//public function
{
	return m_lFileLength;
}

UINT CFileEx::Read(void* buffer, UINT size)
{
	UINT nRead = 0;

	if(m_pFileStream){
		LONG lCurPos = ftell(m_pFileStream);
		if(fread(buffer, size, 1, m_pFileStream)){
			nRead = size;
		}
		else{
			LONG lFileEnd = ftell(m_pFileStream);
			nRead = lFileEnd - lCurPos;
		}
	}

	return nRead;
}

BOOL CFileEx::Write(void* buffer, UINT size)
{
	if(m_pFileStream){
		size_t count = fwrite(buffer, size, 1, m_pFileStream);
		if(count)
			return 1;
	}
	return 0;
}

void CFileEx::SeekToEnd()
{
	if(m_pFileStream){
		fseek(m_pFileStream, 0, SEEK_END);
	}
}

void CFileEx::SeekToBegin()
{
	if(m_pFileStream){
		fseek(m_pFileStream, 0, SEEK_SET);
	}
}

int CFileEx::Seek(LONG lOff, int nFrom)
{
	if(m_pFileStream){
		return fseek(m_pFileStream, lOff, nFrom);
	}
	return -1;
}

void CFileEx::SeekOffset(LONG lOffset)
{
	if(m_pFileStream){
		fseek(m_pFileStream, lOffset, SEEK_CUR);
	}
}