#pragma once
#include "header.h"

class CRegistrationDialog
{
public:
	CRegistrationDialog(void);
public:
	~CRegistrationDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CRegistrationDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hRegPassword,hRegLogin,hRegName,hRegAge;
	static HWND hRegDialog; // дескриптор дополнительного диалога
};
