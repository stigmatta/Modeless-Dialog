#pragma once
#include "header.h"

class CAutorizationDialog
{
public:
	CAutorizationDialog(void);
public:
	~CAutorizationDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CAutorizationDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hAutoPassword, hAutoLogin;
	static HWND hAutoDialog; // дескриптор дополнительного диалога
};
