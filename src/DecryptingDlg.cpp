// DecryptingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "HelloCrypt.h"
#include "DecryptingDlg.h"
#include "afxdialogex.h"
#include "ariaMode.h"

// CDecryptingDlg 대화 상자

IMPLEMENT_DYNAMIC(CDecryptingDlg, CDialogEx)

CDecryptingDlg::CDecryptingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DECRYPTING_DIALOG, pParent)
	, password_dec(_T(""))
{

}

CDecryptingDlg::~CDecryptingDlg()
{
}

void CDecryptingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, decrypt_list);
	DDX_Text(pDX, IDC_EDIT1, password_dec);
	DDV_MaxChars(pDX, password_dec, 16);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}


BEGIN_MESSAGE_MAP(CDecryptingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDecryptingDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDecryptingDlg::OnLbnSelchangeList1)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK2, &CDecryptingDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CDecryptingDlg 메시지 처리기


void CDecryptingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
	UpdateData(TRUE);
	m_Progress.SetRange(0, 100);

	int fileNum = decrypt_list.GetCount();

	if (fileNum == 0) {
		CDialogEx::OnOK();
		return;
	}

	if (password_dec.GetLength() < 4) {
		MessageBox(_T("비밀번호는 4자리 이상이어야 합니다."));
	}
	else if (TRUE) { //추후 조건 추가 필요
		GetDlgItem(IDOK)->EnableWindow(FALSE);

		CString filePath;
		//crypt_list.GetText(0, str);
		

		for (int i = 0; i < fileNum; i++) {
			decrypt_list.GetText(i, filePath);
			//MessageBox(str);
			std::string ctPath = CT2CA(filePath);
			std::string password = CT2CA(password_dec);
			fileDec(ctPath, password, 128);
			m_Progress.SetPos((i + 1) * 100 / fileNum);
		}
		GetDlgItem(IDOK)->ShowWindow(FALSE);
		GetDlgItem(IDOK2)->ShowWindow(TRUE);
		GetDlgItem(IDOK2)->SetFocus();

		MessageBox(_T("완료"));
	}
}


void CDecryptingDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDecryptingDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	int fileNum = 0;
	char filePath[MAX_PATH];

	fileNum = DragQueryFileA(hDropInfo, 0xFFFFFFFF, filePath, MAX_PATH);

	for (int i = 0; i < fileNum; i++) {
		DragQueryFileA(hDropInfo, i, filePath, MAX_PATH);

		CString path = CString(filePath);
		
		int file_exist = decrypt_list.FindStringExact(-1, path);

		//중복되지 않은 파일, 확장자가 enc여야한다.
		if (file_exist == LB_ERR && path.Right(4) == _T(".enc")) { 
			decrypt_list.AddString(path);
		}
	}

	CDialogEx::OnDropFiles(hDropInfo);
}


void CDecryptingDlg::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
