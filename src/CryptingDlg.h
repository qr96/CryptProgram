#pragma once


// CCryptingDlg 대화 상자

class CCryptingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCryptingDlg)

public:
	CCryptingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCryptingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRYPTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox crypt_list;
	afx_msg void OnBnClickedOk();
private:
	CString crypt_password1;
	CString crypt_password2;
public:
	afx_msg void OnLbnSelchangeList1();
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedOk2();
};
