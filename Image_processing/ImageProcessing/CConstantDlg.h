#pragma once
#include "afxdialogex.h"


// CConstantDlg 대화 상자

class CConstantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConstantDlg)

public:
	CConstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;// 상수 입력 대화상자에 입력된 값을 저장하는 변수이다.
};
