#pragma once
#include "afxdialogex.h"


// CTranslationDlg 대화 상자

class CTranslationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslationDlg)

public:
	CTranslationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTranslationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int t_height;	//이동할 높이 값
	int t_width;	//이동할 너비 값
};
