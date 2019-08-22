
// XlogDecodeDlg.h : 头文件
//

#pragma once
#include "def.h"
#include "misc.h"
#include "FileEx.h"
#include "zlib\zlib.h"
#include "afxwin.h"
#include "xlogfilescan.h"

// CXlogDecodeDlg 对话框
class CXlogDecodeDlg : public CDialog
{
// 构造
public:
	CXlogDecodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_XLOGDECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
