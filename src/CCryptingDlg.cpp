// CCryptingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "HelloCrypt.h"
#include "CryptingDlg.h"
#include "afxdialogex.h"


// CCryptingDlg 대화 상자

IMPLEMENT_DYNAMIC(CCryptingDlg, CDialogEx)

CCryptingDlg::CCryptingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CRYPTING_DIALOG, pParent)
	, crypt_password1(_T(""))
	, crypt_password2(_T(""))
{
}

CCryptingDlg::~CCryptingDlg()
{
}

void CCryptingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, crypt_list);
	DDX_Text(pDX, IDC_CRYPT_PASSWORD1, crypt_password1);
	DDV_MaxChars(pDX, crypt_password1, 16);
	DDX_Text(pDX, IDC_CRYPT_PASSWORD2, crypt_password2);
	DDV_MaxChars(pDX, crypt_password2, 16);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}


BEGIN_MESSAGE_MAP(CCryptingDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CCryptingDlg::OnNMCustomdrawProgress1)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, &CCryptingDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CCryptingDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK2, &CCryptingDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CCryptingDlg 메시지 처리기
