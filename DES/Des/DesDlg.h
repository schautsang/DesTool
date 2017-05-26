
// DesDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "DesProc.h"
#include "afxcmn.h"


// CDesDlg 对话框
class CDesDlg : public CDialogEx
{
// 构造
public:
	CDesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DES_DIALOG };
#endif

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
	void SetBitmap(UINT uBmpResource, UINT uCtrlResource);
	CBrush m_hBrush;
	CDes *m_pCDes;
	char m_szKey[8 + 1];
	char m_szPlaintext[1024 + 1];
	char m_szCiphertext[1024 + 1];
	char m_hexCiphertextAnyLength[1024 * 2 + 1];
	char m_bitsCiphertextAnyLength[1024 * 2 * 4 + 1];
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedButton1();
	void ConvertCiphertext2OtherFormat(int iBitsLen, char *szCipherInBytes);
	afx_msg void OnClickedButton2();
	int ConvertOtherFormat2Ciphertext(char *szCipher);
//	afx_msg void OnEnChangeEdit4();
	afx_msg void OnClickedButton3();
//	afx_msg void OnDropdownButton3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButton5();
	afx_msg void OnClickedButton6();
	afx_msg void OnClickedButton4();
//	CEdit m_srcEdit;
	//CString m_srcEdit;
//	CEdit m_dstEdit;
//	CEdit m_fileKey;
	CProgressCtrl m_procBar;
	afx_msg void OnClickedCheck1();
	BOOL m_3desCheck;
//	afx_msg void OnEnChangeEdit1();
};
