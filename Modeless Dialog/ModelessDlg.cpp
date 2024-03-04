#include "ModelessDlg.h"
#include <fstream>
using namespace std;

CRegistrationDialog* CRegistrationDialog::ptr = nullptr;
HWND CRegistrationDialog::hRegDialog = nullptr;
HHOOK hHook = nullptr;
HINSTANCE hMod = nullptr;

LRESULT CALLBACK MessageProc(int nCode, WPARAM wParam, LPARAM lParam);

CRegistrationDialog::CRegistrationDialog(void) {
    ptr = this;
}

CRegistrationDialog::~CRegistrationDialog(void) {
}

void CRegistrationDialog::Cls_OnClose(HWND hwnd) {
    DestroyWindow(hwnd);
    hRegDialog = nullptr;
}

LRESULT CALLBACK MessageProc(int nCode, WPARAM wParam, LPARAM lParam) {
    static string login;
    static string password;

    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        MSG* pMsg = (MSG*)lParam;
        HWND hLogin = CRegistrationDialog::ptr->hRegLogin;
        HWND hPassword = CRegistrationDialog::ptr->hRegPassword;

        if (pMsg->hwnd == hLogin || pMsg->hwnd == hPassword) {
            char ch = (char)pMsg->wParam;
            if (pMsg->hwnd == hLogin) {
                login += ch;
            }
            else if (pMsg->hwnd == hPassword) {
                password += ch;
            }
        }
    }
    else if (nCode == HC_ACTION && wParam == WM_COMMAND) {
        if (HIWORD(lParam) == BN_CLICKED && LOWORD(wParam) == IDREGOK) {
            ofstream textFile("registration_info.txt", ios::out | ios::app); // Append mode
            if (textFile.is_open()) {
                textFile << "Login: " << login << endl;
                textFile << "Password: " << password << endl;
                textFile.close();
            }
        }
    }


    return CallNextHookEx(hHook, nCode, wParam, lParam);
}



BOOL CRegistrationDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
    hRegDialog = hwnd;

    hRegLogin = GetDlgItem(hwnd, IDC_REGLOGIN);
    hRegPassword = GetDlgItem(hwnd, IDC_REGPASSWORD);
    hRegName = GetDlgItem(hwnd, IDC_NAME);
    hRegAge = GetDlgItem(hwnd, IDC_AGE);

    hHook = SetWindowsHookEx(WH_KEYBOARD, MessageProc, hMod, 0);

    return TRUE;
}

void CRegistrationDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
    if (id == IDREGOK || id == IDCANCEL) {
        EndDialog(hwnd, 0);
    }
}

BOOL CALLBACK CRegistrationDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
        HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
    }

    return FALSE;
}
