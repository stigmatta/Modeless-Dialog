#include "ModelessDlg.h"
#include <fstream>
using namespace std;
CRegistrationDialog* CRegistrationDialog::ptr = NULL;
HWND CRegistrationDialog::hRegDialog = NULL;

CRegistrationDialog::CRegistrationDialog(void)
{
	ptr = this;
}

CRegistrationDialog::~CRegistrationDialog(void)
{
	
}

void CRegistrationDialog::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd); 
	hRegDialog = NULL;
}


BOOL CRegistrationDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hRegLogin = GetDlgItem(hwnd,IDC_REGLOGIN);
	hRegPassword = GetDlgItem(hwnd, IDC_REGPASSWORD);
	hRegName = GetDlgItem(hwnd, IDC_NAME);
	hRegAge = GetDlgItem(hwnd, IDC_AGE);
	return TRUE;
}


void CRegistrationDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    wofstream textFile("registration_info.txt", ios::out | ios::trunc);


    if (id == IDREGOK)
    {
        if (textFile.is_open()) {
            textFile << "";
            TCHAR bufferLogin[40], bufferPassword[40], bufferName[40], bufferAge[3];
            SendMessage(hRegLogin, WM_GETTEXT, 40, LPARAM(bufferLogin));
            SendMessage(hRegPassword, WM_GETTEXT, 40, LPARAM(bufferPassword));
            SendMessage(hRegName, WM_GETTEXT, 40, LPARAM(bufferName));
            SendMessage(hRegAge, WM_GETTEXT, 3, LPARAM(bufferAge));
            textFile << bufferLogin << endl;
            textFile<< bufferPassword << endl;
            textFile << bufferName << endl;
            textFile << bufferAge << endl;
            textFile.close();
        }
        DestroyWindow(hwnd);
        hRegDialog = NULL;
        return;
    }
    else if (id == IDCANCEL)
    {
        DestroyWindow(hwnd);
        hRegDialog = NULL;
        return;
    }
}


BOOL CALLBACK CRegistrationDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
