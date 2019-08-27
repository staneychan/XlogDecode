
// XlogDecodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XlogDecode.h"
#include "XlogDecodeDlg.h"

#include "BytesUtils.h"
#include "xlogdef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CXlogDecodeDlg 对话框




CXlogDecodeDlg::CXlogDecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXlogDecodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXlogDecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RECURSE, m_chk_recurse);
	DDX_Control(pDX, IDC_CHECK_SKIP_ERROR_BLOCK, m_chk_skip_error_block);
}

BEGIN_MESSAGE_MAP(CXlogDecodeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_DECODE, &CXlogDecodeDlg::OnBnClickedBtnDecode)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CXlogDecodeDlg 消息处理程序

BOOL CXlogDecodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_chk_skip_error_block.SetCheck(TRUE);

	// TODO: 在此添加额外的初始化代码

	//Xlog参考：http://blog.csdn.net/linuxfu/article/details/61915473
	//zlib参考：http://zlib.net/zlib_how.html
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CXlogDecodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXlogDecodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CXlogDecodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void CXlogDecodeDlg::OnDropFiles(HDROP hDropInfo)
{
	//清空所有
	m_listFile.RemoveAll();

	int DropCount = DragQueryFile(hDropInfo,-1,NULL,0);//取得被拖动文件的数目  
    for(int i=0;i< DropCount;i++)  
    {  
        WCHAR wcStr[MAX_PATH];  
        DragQueryFile(hDropInfo,i,wcStr,MAX_PATH);//获得拖曳的第i个文件的文件名  
        m_listFile.Add(wcStr);  
		OutputDebugString(wcStr);
    }   
    DragFinish(hDropInfo);  //拖放结束后,释放内存

	SetDlgItemText(IDC_EDIT_PATH, m_listFile.GetAt(0));

	CDialog::OnDropFiles(hDropInfo);
}


int CXlogDecodeDlg::decode(){
	CFileEx file;
	file.Open(L"F:\\project_ms\\XlogDecode\\1.xlog", L"rb");
	TRACE1("GET file len:%d\r\n", file.Length());
	byte *header = new byte[GetHeaderLen()];
	file.Read(header, GetHeaderLen());
	CString szHead = dump(header, GetHeaderLen());
	OutputDebugString(szHead + L"\r\n");
	xlogHead sHead;
	memcpy(&sHead , header, sizeof(xlogHead));
	TRACE("DEBUG_GET BODY length:%d start=>%d:%d\r\n", sHead.length, sHead.beginHour, sHead.endHour);

	//body
	byte *out = new byte[sHead.length];
	file.Read(out, sHead.length);
	//TRACE("last :%x %x\r\n", out[sHead.length-2],out[sHead.length-1]);

	CFileEx writer;
	if(writer.Open(L"F:\\project_ms\\XlogDecode\\_1.log", L"wb")){
		inflateToFile(out, sHead.length, writer);
		writer.Close();
	}


#if 0
	byte decodeBuf[128];
	DWORD bytesDecoded;
	DWORD testlen = 100;
	byte *testDest = new byte[testlen];
	memset(testDest,0,100);
	byte *testSrc = new byte[20];
	memcpy(testSrc, "123abc", 6);
	compress(testDest, &testlen, testSrc, 6);

	if(Z_OK == uncompress(decodeBuf, &bytesDecoded, testDest, 100)){
		decodeBuf[bytesDecoded] = 0;
	}
#endif

	delete []header;

	return 1;
}

int skipToNextBlock(CFileEx &reader, xlogHead &sHead){
	int skipCount = 0;
	byte endFlag,startFlag;
	byte *header = new byte[GetHeaderLen()];
	UINT readCount = 0;
	do{
		readCount = reader.Read(&endFlag, 1);
		skipCount++;
		if(endFlag == 0x00){
			reader.Read(&startFlag, 1);
			skipCount++;
			if(startFlag == 0x09){//kMagicAsyncNoCryptStart
				reader.SeekOffset(-1);
				reader.Read(header, GetHeaderLen());
				memcpy(&sHead , header, sizeof(xlogHead));
			}
		}
	}while(sHead.length > 65535 && readCount > 0);
	delete header;
	return skipCount;
}

void CXlogDecodeDlg::decodeFile(CString srcFilePath, CString savePath){
	CFileEx writer;
	CFileEx reader;
	if(!reader.Open(srcFilePath, L"rb")){
		TRACE("@@@@@@@FILE not exist!!!\r\n");
		ASSERT(0);
		return;
	}
	if(!writer.Open(savePath, L"wb+")){
		TRACE("@@@@@@@create FILE ERROR!!!\r\n");
		ASSERT(0);
		return;
	}
	UINT fileLength = reader.Length();
	TRACE1("GET file len:%d\r\n", fileLength);
	byte *header = new byte[GetHeaderLen()];
	UINT readPos = 0;
	while(readPos < fileLength){
		//header
		reader.Read(header, GetHeaderLen());
		readPos += GetHeaderLen();
		//打印header
	//	CString szHead = dump(header, GetHeaderLen());
	//	OutputDebugString(szHead + L"\r\n");

		xlogHead sHead;
		memcpy(&sHead , header, sizeof(xlogHead));
		TRACE("GET BODY start FLAG:%02x ->seq:%d\r\n", sHead.start, sHead.seq);

		TRACE("GET BODY length:%d start=>%d:%d\r\n", sHead.length, sHead.beginHour, sHead.endHour);

		if(m_bSkipErrorBlock && sHead.length > 65535){
			readPos += skipToNextBlock(reader, sHead);
		}
		if(sHead.length == 0 || sHead.length > 65535){
			continue;
		}
		//body
		byte *body = new byte[sHead.length];
		reader.Read(body, sHead.length);
		//TRACE("last :%x %x\r\n", out[sHead.length-2],out[sHead.length-1]);

		//write to file
		inflateToFile(body, sHead.length, writer);
		
		//END tag
		reader.Read(body, 1);

		readPos += sHead.length + 1;
		delete []body;
	}
	writer.Close();
	delete []header;
}

int CXlogDecodeDlg::inflateToFile(byte *_inBlock, DWORD _inSize, CFileEx &_writer){

#define CHUNK 1024
	int ret;
    unsigned int have;
    z_stream strm;
  //  unsigned char in[CHUNK];
    unsigned char out[CHUNK];


    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm,-MAX_WBITS);
    if (ret != Z_OK)
        return ret;

	/* decompress until deflate stream ends or end of file */
	strm.avail_in = _inSize;//fread(in, 1, CHUNK, source);
	strm.next_in  = _inBlock;
	/* run inflate() on input until output buffer not full */
	do {
		strm.avail_out = CHUNK;
		strm.next_out = out;
		ret = inflate(&strm, Z_NO_FLUSH);
		ASSERT(ret != Z_STREAM_ERROR);  /* state not clobbered */
		switch (ret) {
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;     /* and fall through */
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return ret;
		}
		have = CHUNK - strm.avail_out;
		if(!_writer.Write(out, have)){
			(void)inflateEnd(&strm);
			return Z_ERRNO;
		}
	} while (strm.avail_out == 0);



	 /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}



#if 0
int unzip(unsigned char * pDest, unsigned long * ulDestLen, unsigned char *  pSource, int iSourceLen)
{
	int ret = 0;
	unsigned int uiUncompressedBytes = 0; // Number of uncompressed bytes returned from inflate() function
	unsigned char * pPositionDestBuffer = pDest; // Current position in dest buffer
	unsigned char * pLastSource = &pSource[iSourceLen]; // Last position in source buffer
	z_stream strm;

	// Skip over local file header
	SLocalFileHeader * header = (SLocalFileHeader *) pSource;
	pSource += sizeof(SLocalFileHeader) + header->sFileNameLen + header->sExtraFieldLen;


	// We should now be at the beginning of the stream data
	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit2(&strm, -MAX_WBITS);
	if (ret != Z_OK)
	{
		return -1;
	}

	// Uncompress the data
	strm.avail_in = header->iCompressedSize; //iSourceLen;
	strm.next_in = pSource;

	do {
		strm.avail_out = *ulDestLen;
		strm.next_out = pPositionDestBuffer;
		ret = inflate(&strm, Z_NO_FLUSH);
		assert(ret != Z_STREAM_ERROR);  /* state not clobbered */

		switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return -2;
		}
		uiUncompressedBytes = *ulDestLen - strm.avail_out;
		*ulDestLen -= uiUncompressedBytes; // ulDestSize holds number of free/empty bytes in buffer
		pPositionDestBuffer += uiUncompressedBytes;
	} while (strm.avail_out == 0);

	// Close the decompression stream
	inflateEnd(&strm);
	ASSERT(ret == Z_STREAM_END);

	return 0;
}
#endif
void CXlogDecodeDlg::OnBnClickedBtnDecode()
{
	m_bSkipErrorBlock = m_chk_skip_error_block.GetCheck();
//	decode();

	XlogFileScan scaner;
	for(int xx = 0;xx < m_listFile.GetCount();xx++){
		int count = scaner.scan(m_listFile.GetAt(xx), m_chk_recurse.GetCheck());
		if(count > 0){
			CStringArray &outXlogs = scaner.getList();
			TRACE("=======GET file: %d\r\n", outXlogs.GetCount());
			for(int jj = 0;jj < outXlogs.GetCount();jj++){
				OutputDebugString(outXlogs.GetAt(jj)+L"\r\nnew FILE:");
				CString newFile;
				XlogFileScan::genDecodeFileName(outXlogs.GetAt(jj), newFile);
				OutputDebugString(newFile+L"\r\n");
				decodeFile(outXlogs.GetAt(jj), newFile);
			}
		}
	}
	MessageBox(L"完成");
}

