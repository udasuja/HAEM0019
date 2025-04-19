// CConstantDl.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "CConstantDl.h"


// CConstantDl 대화 상자

IMPLEMENT_DYNAMIC(CConstantDl, CDialogEx)

CConstantDl::CConstantDl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_Constant(0)
{

}

CConstantDl::~CConstantDl()
{
}

void CConstantDl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDV_MinMaxDouble(pDX, m_Constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstantDl, CDialogEx)
END_MESSAGE_MAP()


// CConstantDl 메시지 처리기
