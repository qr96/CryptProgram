#pragma once


// CDecryptingDlg 대화 상자

class CDecryptingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDecryptingDlg)

public:
	CDecryptingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDecryptingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DECRYPTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox decrypt_list;
	CString password_dec;
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedOk2();
};
