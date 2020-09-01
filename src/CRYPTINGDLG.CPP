#include "pch.h"
#include "CryptingDlg.h"
#include "ariaMode.h"
#include "resource.h"

void CCryptingDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	*pResult = 0;
}


void CCryptingDlg::OnDropFiles(HDROP hDropInfo)
{
	int fileNum = 0;
	char filePath[MAX_PATH];

	fileNum = DragQueryFileA(hDropInfo, 0xFFFFFFFF, filePath, MAX_PATH);

	for (int i = 0; i < fileNum; i++) {
		DragQueryFileA(hDropInfo, i, filePath, MAX_PATH);

		CString path = CString(filePath);
				
		int file_exist = crypt_list.FindStringExact(-1, path);

		//이미 추가되어 있지 않아야하며 확장자를 포함한 파일만 추가
		if (file_exist == LB_ERR && path.Find('.') != -1) { 
			crypt_list.AddString(path);
		}
	}

	CDialogEx::OnDropFiles(hDropInfo);
}


void CCryptingDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_Progress.SetRange(0, 100);


	int fileNum = crypt_list.GetCount();
	if (fileNum == 0) {
		CDialogEx::OnOK();
		return;
	}

	if (crypt_password1.GetLength() < 4) {
		MessageBox(_T("비밀번호는 4자리 이상이어야 합니다."));
	}
	else if (crypt_password1 != crypt_password2) {
		MessageBox(_T("비밀번호를 확인해 주십시오."));
	}
	else if (crypt_password1 == crypt_password2) {
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		CString filePath;
		//crypt_list.GetText(0, str);
		
		
		for (int i = 0; i < fileNum; i++) {
			crypt_list.GetText(i, filePath);
			//MessageBox(str);
			std::string ptPath = CT2CA(filePath);
			std::string password = CT2CA(crypt_password1);
			fileEnc(ptPath, password, 128);
			m_Progress.SetPos((i+1)*100/fileNum);
		}

		//GetDlgItem(IDOK)->EnableWindow(TRUE);

		GetDlgItem(IDOK)->ShowWindow(FALSE);
		GetDlgItem(IDOK2)->ShowWindow(TRUE);
		GetDlgItem(IDOK2)->SetFocus();
		MessageBox(_T("완료"));
	}
}


void CCryptingDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCryptingDlg::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
