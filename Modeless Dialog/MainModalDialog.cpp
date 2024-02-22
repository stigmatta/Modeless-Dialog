#include "MainModalDialog.h"
#include "ModelessDlg.h"
#include "CAutorizationDialog.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
	static CRegistrationDialog dlg;
	static CAutorizationDialog autoDlg;
	if (id == IDC_REGISTRATION)
	{
		if (CRegistrationDialog::hRegDialog)
		{
			SetForegroundWindow(CRegistrationDialog::hRegDialog);	
		
			ShowWindow(CRegistrationDialog::hRegDialog, SW_RESTORE);
		
		
		return;
		}
		else
		{
			CRegistrationDialog::hRegDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CRegistrationDialog::DlgProc);

			ShowWindow(CRegistrationDialog::hRegDialog, SW_RESTORE);

	     return;
		}
	
	}
	else if (id == IDC_AUTORIZATION) {
		if (CAutorizationDialog::hAutoDialog) {
			SetForegroundWindow(CAutorizationDialog::hAutoDialog);

			ShowWindow(CAutorizationDialog::hAutoDialog, SW_RESTORE);

			return;
		}
		else {
			CAutorizationDialog::hAutoDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, CAutorizationDialog::DlgProc);

			ShowWindow(CAutorizationDialog::hAutoDialog, SW_RESTORE);

			return;
		}
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
