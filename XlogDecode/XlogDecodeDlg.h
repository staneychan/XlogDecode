
// XlogDecodeDlg.h : ͷ�ļ�
//

#pragma once
#include "def.h"
#include "misc.h"
#include "FileEx.h"
#include "zlib\zlib.h"
#include "afxwin.h"
#include "xlogfilescan.h"

// CXlogDecodeDlg �Ի���
class CXlogDecodeDlg : public CDialog
{
// ����
public:
	CXlogDecodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XLOGDECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDecode();
	afx_msg void OnDropFiles(HDROP hDropInfo);

	int decode();//test function
	void decodeFile(CString srcFilePath, CString savePath);
	int inflateToFile(byte *_inBlock, DWORD _inSize, CFileEx &_writer);

	CButton m_chk_recurse;
	CStringArray m_listFile;
	CButton m_chk_skip_error_block;
	BOOL m_bSkipErrorBlock;
};
