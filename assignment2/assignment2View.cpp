
// assignment2View.cpp: Cassignment2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "assignment2.h"
#endif

#include "assignment2Doc.h"
#include "assignment2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cassignment2View

IMPLEMENT_DYNCREATE(Cassignment2View, CView)

BEGIN_MESSAGE_MAP(Cassignment2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_UP_SAMPLING, &Cassignment2View::OnUpSampling)
	ON_COMMAND(ID_DOWN_SAMPLING, &Cassignment2View::OnDownSampling)
END_MESSAGE_MAP()

// Cassignment2View 생성/소멸

Cassignment2View::Cassignment2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cassignment2View::~Cassignment2View()
{
}

BOOL Cassignment2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cassignment2View 그리기

void Cassignment2View::OnDraw(CDC* pDC)
{
	Cassignment2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i, j;
	unsigned char R, G, B;

	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}


}


// Cassignment2View 인쇄

BOOL Cassignment2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cassignment2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cassignment2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cassignment2View 진단

#ifdef _DEBUG
void Cassignment2View::AssertValid() const
{
	CView::AssertValid();
}

void Cassignment2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cassignment2Doc* Cassignment2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cassignment2Doc)));
	return (Cassignment2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cassignment2View 메시지 처리기


void Cassignment2View::OnUpSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Cassignment2Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신

}


void Cassignment2View::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Cassignment2Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출

	Invalidate(TRUE); // 화면 갱신
}
