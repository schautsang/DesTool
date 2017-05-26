
// DesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Des.h"
#include "DesDlg.h"
#include "afxdialogex.h"
#include "DesProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDesDlg 对话框



CDesDlg::CDesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DES_DIALOG, pParent)
	, m_3desCheck(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT5, m_srcEdit);
	//DDX_Text(pDX, IDC_EDIT5, m_srcEdit);
	//  DDX_Control(pDX, IDC_EDIT6, m_dstEdit);
	//  DDX_Control(pDX, IDC_EDIT4, m_fileKey);
	DDX_Control(pDX, IDC_PROGRESS1, m_procBar);
	DDX_Check(pDX, IDC_CHECK1, m_3desCheck);
}

BEGIN_MESSAGE_MAP(CDesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CDesDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDesDlg::OnClickedButton2)
//	ON_EN_CHANGE(IDC_EDIT4, &CDesDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON3, &CDesDlg::OnClickedButton3)
//	ON_NOTIFY(BCN_DROPDOWN, IDC_BUTTON3, &CDesDlg::OnDropdownButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CDesDlg::OnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDesDlg::OnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CDesDlg::OnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK1, &CDesDlg::OnClickedCheck1)
//	ON_EN_CHANGE(IDC_EDIT1, &CDesDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDesDlg 消息处理程序

BOOL CDesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_hBrush.CreateSolidBrush(RGB(255, 255, 255));   //生成白色画刷

	m_pCDes = new CDes();

	memset(m_szPlaintext, 0, 1024 + 1);
	memset(m_szCiphertext, 0, 1024 + 1);
	memset(m_hexCiphertextAnyLength, 0, 1024 * 2 + 1);
	memset(m_bitsCiphertextAnyLength, 0, 1024 * 2 * 4 + 1);
	memset(m_szKey, 0, 8 + 1);

	SetBitmap(IDB_BITMAP1, IDC_STATIC_PIC);

	GetDlgItem(IDC_STATIC_EDITKEY2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDesDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDesDlg::SetBitmap(UINT uBmpResource, UINT uCtrlResource)
{
	HBITMAP hBitmap;
	CStatic *pStatic = (CStatic*)GetDlgItem(uCtrlResource);
	hBitmap = (HBITMAP)LoadImage(
		AfxGetInstanceHandle(),
		MAKEINTRESOURCE(uBmpResource),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADMAP3DCOLORS);
	pStatic->ModifyStyle(0xF, SS_BITMAP);
	pStatic->SetBitmap(hBitmap);
}


HBRUSH CDesDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;
	
	return m_hBrush;
}


void CDesDlg::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CDes *m_pCDes = new CDes();

	CString strKey, strPlaintext;

	GetDlgItemText(IDC_EDIT1, strKey);
	GetDlgItemText(IDC_EDIT2, strPlaintext);

	memset(m_szKey, 0, 8 + 1);
	memset(m_szPlaintext, 0, 1024 + 1);
	memcpy(m_szKey, strKey.GetBuffer(), strKey.GetLength() < 8 ? strKey.GetLength() : 8);
	memcpy(m_szPlaintext, strPlaintext.GetBuffer(), strPlaintext.GetLength());

	m_pCDes->InitializeKey(m_szKey, 0);
	SetDlgItemText(IDC_EDIT3, "");

	m_pCDes->EncryptAnyLength(m_szPlaintext, strlen(m_szPlaintext), 0);

	ConvertCiphertext2OtherFormat(strlen(m_szPlaintext) % 8 == 0 ? strlen(m_szPlaintext) << 3 : ((strlen(m_szPlaintext) >> 3) + 1) << 6, m_pCDes->GetCiphertextAnyLength());

	GetDlgItem(IDC_EDIT3)->SetWindowText(m_hexCiphertextAnyLength);
}


void CDesDlg::ConvertCiphertext2OtherFormat(int iBitsLen, char *szCipherInBytes)
{
	memset(m_hexCiphertextAnyLength, 0, 1024 * 2 + 1);
	memset(m_bitsCiphertextAnyLength, 0, 1024 * 2 * 4 + 1);

	m_pCDes->Bytes2Bits(szCipherInBytes, m_bitsCiphertextAnyLength, iBitsLen);
	m_pCDes->Bits2Hex(m_hexCiphertextAnyLength, m_bitsCiphertextAnyLength, iBitsLen);

	for (int i = 0; i < iBitsLen; i++)
	{
		m_bitsCiphertextAnyLength[i] += '0';
	}
}


void CDesDlg::OnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	CDes *m_pCDes = new CDes();

	CString strKey, strCiphertext;

	GetDlgItem(IDC_EDIT1)->GetWindowText(strKey);
	GetDlgItem(IDC_EDIT3)->GetWindowText(strCiphertext);

	memset(m_szKey, 0, 8 + 1);
	memcpy(m_szKey, strKey.GetBuffer(), strKey.GetLength() < 8 ? strKey.GetLength() : 8);

	m_pCDes->InitializeKey(m_szKey, 0);
	GetDlgItem(IDC_EDIT2)->SetWindowText("");

	memset(m_szPlaintext, 0, 1024 + 1);
	m_pCDes->DecryptAnyLength(m_szCiphertext, ConvertOtherFormat2Ciphertext(strCiphertext.GetBuffer()), 0);

	GetDlgItem(IDC_EDIT2)->SetWindowText(m_pCDes->GetPlaintextAnyLength());
}


int CDesDlg::ConvertOtherFormat2Ciphertext(char *szCipher)
{
	int iLen = 0;

	iLen = ((strlen(szCipher) >> 2) + (strlen(szCipher) % 4 == 0 ? 0 : 1)) << 4;

	// hex data
	memset(m_hexCiphertextAnyLength, 0, 1024 * 2 + 1);
	memcpy(m_hexCiphertextAnyLength, szCipher, strlen(szCipher));

	// bin data
	memset(m_bitsCiphertextAnyLength, 0, 1024 * 2 * 4 + 1);
	m_pCDes->Hex2Bits(m_hexCiphertextAnyLength, m_bitsCiphertextAnyLength, iLen);

	// byte data
	memset(m_szCiphertext, 0, 1024 + 1);
	m_pCDes->Bits2Bytes(m_szCiphertext, m_bitsCiphertextAnyLength, iLen);

	return iLen >> 3;
}


//void CDesDlg::OnEnChangeEdit4()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CDesDlg::OnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	CDes *m_pCDes = new CDes();

	FILE *fpSrc, *fpDst;

	CString srcFilePath, dstFilePath, strFileKey;

	char buff[8] = { 0 };

	long fileSize = 0, hasDone = 0;


	GetDlgItemText(IDC_EDIT4, strFileKey);
	GetDlgItemText(IDC_EDIT5, srcFilePath);
	GetDlgItemText(IDC_EDIT6, dstFilePath);

	if ((fpSrc = fopen(srcFilePath.GetBuffer(), "rb")) == NULL)
	{
		MessageBox("源文件打不开!", "错误", MB_OK | MB_ICONERROR);
		return;
	}
	if ((fpDst = fopen(dstFilePath.GetBuffer(), "wb")) == NULL)
	{
		MessageBox("目的文件打不开!", "错误", MB_OK | MB_ICONERROR);
		return;
	}

	fseek(fpSrc, 0, SEEK_SET);
	fseek(fpSrc, 0, SEEK_END);
	fileSize = ftell(fpSrc);
	rewind(fpSrc);

	m_procBar.SetRange(0, 100);
	m_procBar.ShowWindow(SW_SHOW);

	memset(m_szKey, 0, 8 + 1);
	memcpy(m_szKey, strFileKey.GetBuffer(), strFileKey.GetLength() < 8 ? strFileKey.GetLength() : 8);
	m_pCDes->InitializeKey(m_szKey, 0);

	while (!feof(fpSrc))
	{
		memset(buff, 0, 8);
		fread(buff, sizeof(char), 8, fpSrc);
		m_pCDes->EncryptData(buff, 0);
		fwrite(m_pCDes->GetCiphertextInBytes(), sizeof(char), 8, fpDst);
		hasDone += 8;

		m_procBar.SetPos((int)(hasDone * 100 / fileSize));
	}

	fclose(fpSrc);
	fclose(fpDst);
	m_procBar.SetPos(100);
	MessageBox("加密完成!", "提示", MB_OK | MB_ICONINFORMATION);
	m_procBar.ShowWindow(SW_HIDE);
}


//void CDesDlg::OnDropdownButton3(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


void CDesDlg::OnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	CDes *m_pCDes = new CDes();

	FILE *fpSrc, *fpDst;

	CString srcFilePath, dstFilePath, strFileKey;

	char buff[8] = { 0 };

	long fileSize = 0, hasDone = 0;

	GetDlgItemText(IDC_EDIT4, strFileKey);
	GetDlgItemText(IDC_EDIT5, srcFilePath);
	GetDlgItemText(IDC_EDIT6, dstFilePath);

	if ((fpSrc = fopen(srcFilePath.GetBuffer(), "rb")) == NULL)
	{
		MessageBox("打不开源文件!", "错误", MB_OK | MB_ICONERROR);
		return;
	}
	if ((fpDst = fopen(dstFilePath.GetBuffer(), "wb")) == NULL)
	{
		MessageBox("打不开目的文件!", "错误", MB_OK | MB_ICONERROR);
		return;
	}

	fseek(fpSrc, 0, SEEK_SET);
	fseek(fpSrc, 0, SEEK_END);
	fileSize = ftell(fpSrc);
	rewind(fpSrc);

	m_procBar.SetRange(0, 100);
	m_procBar.ShowWindow(SW_SHOW);

	memset(m_szKey, 0, 8 + 1);
	memcpy(m_szKey, strFileKey.GetBuffer(), strFileKey.GetLength() < 8 ? strFileKey.GetLength() : 8);
	m_pCDes->InitializeKey(m_szKey, 0);

	while (!feof(fpSrc))
	{
		memset(buff, 0, 8);
		fread(buff, sizeof(char), 8, fpSrc);
		m_pCDes->DecryptData(buff, 0);
		fwrite(m_pCDes->GetPlaintext(), sizeof(char), 8, fpDst);
		hasDone += 8;

		m_procBar.SetPos((int)(hasDone * 100 / fileSize));
	}

	fclose(fpSrc);
	fclose(fpDst);
	m_procBar.SetPos(100);
	MessageBox("解密完成!", "提示", MB_OK | MB_ICONINFORMATION);
	m_procBar.ShowWindow(SW_HIDE);
}


void CDesDlg::OnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog *save_file = new CFileDialog(FALSE, "*.*", NULL, OFN_OVERWRITEPROMPT, "All Files(*.*)|*.*|", NULL, 0, 0);
	
	if (save_file->DoModal() == IDOK)
	{
		SetDlgItemText(IDC_EDIT6, save_file->GetPathName());
	}
}


void CDesDlg::OnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog *open_file = new CFileDialog(TRUE, "*.*", NULL, NULL, "All Files(*.*)|*.*|", NULL, 0, 0);

	if (open_file->DoModal() == IDOK)
	{
		//UpdateData(TRUE);
		//m_srcEdit = open_file->GetPathName();
		//UpdateData(FALSE);

		SetDlgItemText(IDC_EDIT5, open_file->GetPathName());
	}
}


void CDesDlg::OnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码

	//if (((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
	//{
	//	MessageBox("使能3DES");
	//}
	//else
	//{	
	//	MessageBox("不使能3DES");
	//}

	UpdateData(TRUE);
	if (m_3desCheck == TRUE)
	{
		GetDlgItem(IDC_STATIC_EDITKEY2)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_EDIT7)->ShowWindow(SW_NORMAL);
		
	}
	else
	{
		SetDlgItemText(IDC_EDIT7, "");
		GetDlgItem(IDC_STATIC_EDITKEY2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
	}
}


//void CDesDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
