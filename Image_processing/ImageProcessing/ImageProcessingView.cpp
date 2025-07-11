﻿
// ImageProcessingView.cpp: CImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DOWN_SAMPLING, &CImageProcessingView::OnDownSampling)

	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingView::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CImageProcessingView::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingView::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingView::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessingView::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessingView::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingView::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProcessingView::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingView::OnXorOperate)
	ON_COMMAND(ID_NOT_OPERATE, &CImageProcessingView::OnNotOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingView::OnNegaTransform)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingView::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingView::OnStressTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingView::OnGammaCorrection)
//	ON_UPDATE_COMMAND_UI(ID_STRESS_TRANSFORM, &CImageProcessingView::OnUpdateStressTransform)
ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingView::OnHistoStretch)
ON_COMMAND(ID_END_IN_SEARCH, &CImageProcessingView::OnEndInSearch)
ON_COMMAND(ID_HISTOGRAM, &CImageProcessingView::OnHistogram)
ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingView::OnHistoEqual)
ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingView::OnHistoSpec)
ON_COMMAND(ID_EMBOSSING, &CImageProcessingView::OnEmbossing)
ON_COMMAND(ID_BLURR, &CImageProcessingView::OnBlurr)
ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProcessingView::OnGaussianFilter)
ON_COMMAND(ID_SHARPENING, &CImageProcessingView::OnSharpening)
ON_COMMAND(ID_HPF_SHARP, &CImageProcessingView::OnHpfSharp)
ON_COMMAND(ID_LPF_SHARP, &CImageProcessingView::OnLpfSharp)
ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CImageProcessingView::OnDiffOperatorHor)
ON_COMMAND(ID_HOMOGEN_OPERATOR, &CImageProcessingView::OnHomogenOperator)
ON_COMMAND(ID_LAPLACIAN, &CImageProcessingView::OnLaplacian)
ON_COMMAND(ID_NEAREST, &CImageProcessingView::OnNearest)
ON_COMMAND(ID_BILINEAR, &CImageProcessingView::OnBilinear)
ON_COMMAND(ID_MEDIAN_SUB, &CImageProcessingView::OnMedianSub)
ON_COMMAND(ID_MEAN_SUB, &CImageProcessingView::OnMeanSub)
ON_COMMAND(ID_TRANSLATION, &CImageProcessingView::OnTranslation)
ON_COMMAND(ID_MIRROR_HOR, &CImageProcessingView::OnMirrorHor)
ON_COMMAND(ID_MIRROR_VER, &CImageProcessingView::OnMirrorVer)
ON_COMMAND(ID_ROTATION, &CImageProcessingView::OnRotation)
ON_COMMAND(ID_FRAME_SUM, &CImageProcessingView::OnFrameSum)
ON_COMMAND(ID_FRAME_SUB, &CImageProcessingView::OnFrameSub)
ON_COMMAND(ID_FRAME_MUL, &CImageProcessingView::OnFrameMul)
ON_COMMAND(ID_FRAME_DIV, &CImageProcessingView::OnFrameDiv)
ON_COMMAND(ID_FRAME_MEAN, &CImageProcessingView::OnFrameMean)
ON_COMMAND(ID_FRAME_AND, &CImageProcessingView::OnFrameAnd)
ON_COMMAND(ID_FRAME_OR, &CImageProcessingView::OnFrameOr)
ON_COMMAND(ID_FRAME_COMB, &CImageProcessingView::OnFrameComb)
END_MESSAGE_MAP()

// CImageProcessingView 생성/소멸

CImageProcessingView::CImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView 그리기

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();	//ImageProcessingDoc를 접근
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//입력받은 영상을 화면에 출력
	int i, j;
	unsigned char R, G, B;
	for (i = 0;i < pDoc->m_height;i++)	//세로
	{
		for (j = 0;j < pDoc->m_width;j++)	//가로
		{
			//m_InputImage는 2차원 영상를 1차원으로 표현한 것이다.
			//다음은 행은 고정하고, 열을 이동하면서 각 픽셀 값을 R, G, B에 저장
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];	

			//SetPixel은 오른쪽에서 왼쪽으로, 위에서 아래로 화면의 화소 단위로
			//data값에 맞는 색을 나타내며 인수 R, G, B는 화소의 색을 표현한다.
			//R, G, B 값이 모두 같으면 색 값은 없고 명도 값만 있도록 표현된다.
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	//축소된 영상 출력
	for (i = 0;i < pDoc->m_Re_height;i++)
	{
		for (j = 0;j < pDoc->m_Re_width;j++)
		{
			//doc클래스에 있는 출력영상에 대한 픽셀에 접근
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CImageProcessingView 인쇄

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingView 진단

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 메시지 처리기


void CImageProcessingView::OnDownSampling()
{
	CImageProcessingDoc* pDoc = GetDocument();	//Doc클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDownSampling();	//Doc클래스에 OnDownSampling함수 호출
	Invalidate(TRUE);	//화면 갱신
}


void CImageProcessingView::OnUpSampling()
{
	CImageProcessingDoc* pDoc = GetDocument();	//Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnUpSampling();//Doc클래스에 OnUpSampling함수 호출
	Invalidate(TRUE);	//화면 갱신
}


void CImageProcessingView::OnQuantization()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnQuantization();	//Doc클래스에 OnQuantization함수 호출
	Invalidate(TRUE);
}


void CImageProcessingView::OnSumConstant()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSumConstant();
	Invalidate(TRUE);
}


void CImageProcessingView::OnSubConstant()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSubConstant();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMulConstant()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMulConstant();
	Invalidate(TRUE);
}


void CImageProcessingView::OnDivConstant()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnDivConstant();
	Invalidate(TRUE);
}


void CImageProcessingView::OnAndOperate()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnAndOperate();
	Invalidate(TRUE);
}


void CImageProcessingView::OnOrOperate()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnOrOperate();
	Invalidate(TRUE);
}


void CImageProcessingView::OnXorOperate()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnXorOperate();
	Invalidate(TRUE);
}


void CImageProcessingView::OnNotOperate()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNotOperate();
	Invalidate(TRUE);
}


void CImageProcessingView::OnNegaTransform()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBinarization()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization();
	Invalidate(TRUE);
}


void CImageProcessingView::OnStressTransform()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnStressTransform();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGammaCorrection()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoStretch()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEndInSearch()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistogram()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoEqual()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoSpec()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoSpec();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEmbossing()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEmbossing();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBlurr()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGaussianFilter()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CImageProcessingView::OnSharpening()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSharpening();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHpfSharp()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingView::OnLpfSharp()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingView::OnDiffOperatorHor()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHomogenOperator()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHomogenOperator();
	Invalidate(TRUE);
}


void CImageProcessingView::OnLaplacian()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian();
	Invalidate(TRUE);
}


void CImageProcessingView::OnNearest()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNearest();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBilinear()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBilinear();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMedianSub()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMedianSub();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMeanSub()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMeanSub();
	Invalidate(TRUE);
}


void CImageProcessingView::OnTranslation()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnTranslation();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMirrorHor()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorHor();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMirrorVer()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorVer();
	Invalidate(TRUE);
}


void CImageProcessingView::OnRotation()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRotation();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameSum()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameSum();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameSub()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameSub();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameMul()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameMul();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameDiv()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameDiv();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameMean()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameMean();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameAnd()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameAnd();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameOr()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameOr();
	Invalidate(TRUE);
}


void CImageProcessingView::OnFrameComb()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnFrameComb();
	Invalidate(TRUE);
}
