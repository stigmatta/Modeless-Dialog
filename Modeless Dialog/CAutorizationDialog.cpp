#include <fstream>
#include <iostream>
#include <string>
#include "CAutorizationDialog.h"

using namespace std;

CAutorizationDialog* CAutorizationDialog::ptr = NULL;
HWND CAutorizationDialog::hAutoDialog = NULL;

CAutorizationDialog::CAutorizationDialog(void)
{
    ptr = this;
}

CAutorizationDialog::~CAutorizationDialog(void)
{

}

void CAutorizationDialog::Cls_OnClose(HWND hwnd)
{
    DestroyWindow(hwnd);
    hAutoDialog = NULL;
}


BOOL CAutorizationDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    hAutoLogin = GetDlgItem(hwnd, IDC_AUTOLOGIN);
    hAutoPassword = GetDlgItem(hwnd, IDC_AUTOPASSWORD);
    return TRUE;
}


void  CAutorizationDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    ifstream inputFile("registration_info.txt");
    TCHAR bufferLogin[40], bufferPassword[40];
    string line;
    if (id == IDAUTOOK) {
        if (inputFile.is_open()) {
            SendMessage(hAutoLogin, WM_GETTEXT, 40, LPARAM(bufferLogin));
            SendMessage(hAutoPassword, WM_GETTEXT, 40, LPARAM(bufferPassword));

            string line;
            getline(inputFile, line);
            wstring wideLine(line.begin(), line.end());

            if (_tcscmp(bufferLogin, wideLine.c_str()) == 0) {
                getline(inputFile, line);
                wstring wideLine2(line.begin(), line.end());
                if (_tcscmp(bufferPassword, wideLine2.c_str()) == 0) {
                    MessageBox(hwnd, L"Autorized!", L"Congratulations", 0);
                }
                else
                    MessageBox(hwnd, L"Not Autorized!", L"Try again", 0);
                
            }
            else
                MessageBox(hwnd, L"Not Autorized!", L"Try again", 0);
            
        }
        DestroyWindow(hwnd);
        hAutoDialog = NULL;
        return;
    }
    else if (id == IDCANCEL)
    {
        DestroyWindow(hwnd);
        hAutoDialog = NULL;
        return;
    }
}


BOOL CALLBACK CAutorizationDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
        HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
    }
    return FALSE;
}
