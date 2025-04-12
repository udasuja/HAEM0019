﻿#pragma once
#include "afxdialogex.h"


// CConstantDl 대화 상자

class CConstantDl : public CDialogEx
{
	DECLARE_DYNAMIC(CConstantDl)

public:
	CConstantDl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
