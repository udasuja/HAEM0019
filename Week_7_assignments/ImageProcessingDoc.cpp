﻿
// ImageProcessingDoc.cpp: CImageProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"

#include <propkey.h>
#include "CDownSampleDlg.h"
#include "CUpSampleDlg.h"
#include "CQuantizationDlg.h" // 대화상자 사용을 위한 헤더 선언
#include "math.h" // 수학 함수 사용을 위한 헤더 선언
#include "CConstantDl.h"
#include "CStressTransformDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
//	ON_COMMAND(AFX_TIMER_ID_TIMER_WAIT, &CImageProcessingDoc::OnOpenDocument)
//ON_COMMAND(IDR_ImageProcessingTYPE, &CImageProcessingDoc::OnIdrImageprocessingtype)
ON_COMMAND(ID_DOWN_SAMPLING, &CImageProcessingDoc::OnDownSampling)
ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingDoc::OnUpSampling)
ON_COMMAND(ID_SUM_CONSANT, &CImageProcessingDoc::OnSumConsant)
ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingDoc::OnSubConstant)
ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessingDoc::OnMulConstant)
ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessingDoc::OnDivConstant)
ON_COMMAND(ID_AND_OPERATE, &CImageProcessingDoc::OnAndOperate)
ON_COMMAND(ID_OR_OPERATE, &CImageProcessingDoc::OnOrOperate)
ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingDoc::OnXorOperate)
ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingDoc::OnNegaTransform)
ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingDoc::OnGammaCorrection)
ON_COMMAND(ID_BINARIZATION, &CImageProcessingDoc::OnBinarization)
ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingDoc::OnStressTransform)
ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingDoc::OnHistoStretch)
ON_COMMAND(ID_END_IN_SEARCH, &CImageProcessingDoc::OnEndInSearch)
ON_COMMAND(ID_HISTOGRAM, &CImageProcessingDoc::OnHistogram)
ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingDoc::OnHistoEqual)
ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingDoc::OnHistoSpec)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령



BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	if (File.GetLength() == 256 * 256)
	{
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512)
	{
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480)
	{
		m_height = 480;
		m_width = 640;
	}
	else
	{
		AfxMessageBox("Not Support Image Size");
		return 0;
	}
	m_size = m_width * m_height;
	m_InputImage = new unsigned char[m_size];
	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255;
	File.Read(m_InputImage, m_size);
	File.Close();
	return TRUE;
}


BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File;
	CFileDialog SaveDlg(FALSE, "raw", NULL, OFN_HIDEREADONLY);
	if (SaveDlg.DoModal() == IDOK)
	{
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		File.Write(m_InputImage, m_size);
		File.Close();
	}
	return TRUE;
}



void CImageProcessingDoc::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// 축소 영상의 세로 길이를 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// 축소 영상의 가로 길이를 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 축소 영상의 크기를 계산

		m_OutputImage = new unsigned char[m_Re_size];
		// 축소 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
				// 축소 영상을 생성
			}
		}
	}

}




void CImageProcessingDoc::OnUpSampling()
{
	int i, j;

	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal 대화상자의 활성화 여부
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// 확대 영상의 세로 길이 계산
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// 확대 영상의 가로 길이 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 확대 영상의 크기 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 확대 영상을 위한 메모리 할당

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0; // 초기화

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
					dlg.m_UpSampleRate * j] = m_InputImage[i * m_width + j];
			} // 재배치하여 영상 확대
		}
	}

}


void CImageProcessingDoc::OnQuantization()
{
	CQuantizationDlg dlg;
	if (dlg.DoModal() == IDOK)
		// 양자화 비트 수를 결정하는 대화상자의 활성화 여부
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];
		// 양자화 처리된 영상을 출력하기 위한 메모리 할당

		TEMP = new double[m_size];
		// 입력 영상 크기(m_size)와 동일한 메모리 할당

		LEVEL = 256; // 입력 영상의 양자화 단계(28=256)
		HIGH = 256.;

		value = (int)pow(2, dlg.m_QuantBit);
		// 양자화 단계 결정(예 : 24=16)

		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value) * j &&
					m_InputImage[i] < (LEVEL / value) * (j + 1)) {
					TEMP[i] = (double)(HIGH / value) * j; // 양자화 수행
				}
			}
		}
		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
			// 결과 영상 생성
		}
	}

}


void CImageProcessingDoc::OnSumConsant()
{
	CConstantDl dlg; // 상수 값을 입력받는 대화상자

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;
			// 출력 값이 255보다 크면 255 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
			// 상수 값과 화소 값과의 덧셈
		}
	}

}


void CImageProcessingDoc::OnSubConstant()
{
	CConstantDl dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0; // 출력 값이 255보다 크면 255를 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] - dlg.m_Constant);
			// 상수 값과 화소 값과의 뺄셈
		}
	}

}


void CImageProcessingDoc::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] * dlg.m_Constant > 255)
				m_OutputImage[i] = 255;
			// 곱의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] * dlg.m_Constant < 0)
				m_OutputImage[i] = 0;
			// 곱의 값이 0보다 작으면 0을 출력
			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
			// 상수 값과 화소 값 곱셈
		}
	}
}


void CImageProcessingDoc::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] / dlg.m_Constant > 255)
				m_OutputImage[i] = 255;
			// 나눗셈의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] / dlg.m_Constant < 0)
				m_OutputImage[i] = 0;
			// 나눗셈의 값이 0보다 작으면 0을 출력
			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
			// 상수 값과 화소 값 나눗셈
		}
	}

}


void CImageProcessingDoc::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 AND 연산
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i]
					& (unsigned char)dlg.m_Constant);
			}
		}
	}

}


void CImageProcessingDoc::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 OR 연산
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255) {
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0) {
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i] |
					(unsigned char)dlg.m_Constant);
			}
		}
	}

}


void CImageProcessingDoc::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 XOR 연산
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255) {
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0) {
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i]
					^ (unsigned char)dlg.m_Constant);
			}
		}
	}

}


void CImageProcessingDoc::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i]; // 영상 반전을 수행

}


void CImageProcessingDoc::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;

	int i;
	double temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
			// 감마 값 계산
			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}

}


void CImageProcessingDoc::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CConstantDl dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255; // 임계 값보다 크면 255 출력
			else
				m_OutputImage[i] = 0; // 임계 값보다 작으면 0 출력
		}
	}

}


void CImageProcessingDoc::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CStressTransformDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 입력 값이 강조 시작 값과 강조 종료 값 사이에 위치하면 255 출력
			if (m_InputImage[i] >= dlg.m_StartPoint &&
				m_InputImage[i] <= dlg.m_EndPoint)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
}


void CImageProcessingDoc::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0]; // 최소값을 찾기 위한 초기값
	MAX = m_InputImage[0]; // 최대값을 찾기 위한 초기값

	// 입력 영상의 최소값 찾기
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	// 입력 영상의 최대값 찾기
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	// 히스토그램 stretch
	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN) * HIGH / (MAX - MIN));

}


void CImageProcessingDoc::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_size; i++) {
		// 원본 영상의 최소값보다 작은 값은 0
		if (m_InputImage[i] <= MIN) {
			m_OutputImage[i] = 0;
		}

		// 원본 영상의 최대값보다 큰 값은 255
		else if (m_InputImage[i] >= MAX) {
			m_OutputImage[i] = 255;
		}
		else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
				MIN) * HIGH / (MAX - MIN));
	}

}


void CImageProcessingDoc::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 히스토그램의 값은 0~255
   // 히스토그램의 크기 값을 MAX=255로 정규화하여 출력
   // 히스트그램의 크기 : 256*256 지정

	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}

	for (i = 0; i < 256; i++) {
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];
	}
	DIF = MAX - MIN;

	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	// 정규화된 히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];

	for (i = 0; i < m_Re_size; i++)
		m_OutputImage[i] = 255;

	// 정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현
	for (i = 0; i < 256; i++) {
		for (j = 0; j < m_Scale_HIST[i]; j++) {
			m_OutputImage[m_Re_width * (m_Re_height - j - 1) + i] = 0;
		}
	}

	// 히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시
	for (i = m_Re_height; i < m_Re_height + 5; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}

	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}

	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height * m_Re_width;

}


void CImageProcessingDoc::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	m_OutputImage = new unsigned char[m_Re_size];

	// 입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}

}


void CImageProcessingDoc::OnHistoSpec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP = nullptr, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, * m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;

	top = 255;
	bottom = top - 1;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];

	CFile File;
	CFileDialog OpenDlg(TRUE);

	// 원하는 히스토그램이 있는 영상을 입력받음
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {
			m_DTEMP = new unsigned char[m_size];
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox("Image size not matched");
			// 같은 크기의 영상을 대상으로 함
			return;
		}
	}
	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}
	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}
	// 누적 히스토그램 조사
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}
	// 원본 영상의 평활화
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// 누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];
	// 원하는 영상을 평활화
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i]
			- DMIN) * HIGH / (DMAX - DMIN));
	}
	// 룩업테이블을 이용한 명세화
	for (; ; ) {
		for (i = m_Sum_Of_ScHIST[bottom];
			i <= m_Sum_Of_ScHIST[top]; i++) {
			m_TABLE[i] = top;
		}
		top = bottom;
		bottom = bottom - 1;
		if (bottom < -1)
			break;
	}
	for (i = 0; i < m_size; i++) {
		DADD = (int)m_Org_Temp[i];
		m_OutputImage[i] = m_TABLE[DADD];
	}


}
