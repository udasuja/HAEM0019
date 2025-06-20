
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
#include "CDownSampleDlg.h"	//다운샘플링용 대화상자 사용을 위한 헤더 선언
#include "CUpSampleDlg.h"	//업샘플링용 대화상자 사용을 위한 헤더 선언
#include "CQuantizationDlg.h"//양자화용 대화상자 사용을 위한 헤더 선언
#include "math.h"
#include "CConstantDlg.h" //상수입력용 대화상자 사용을 위한 헤더 선언
#include "CStressTransformDlg.h"//범위 강조 대화상자를 위한 헤더 선언
#include "CTranslationDlg.h"//이동 범위 대화상자를 위한 헤더 선언

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_DOWN_SAMPLING, &CImageProcessingDoc::OnDownSampling)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessingDoc::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CImageProcessingDoc::OnQuantization)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingDoc::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingDoc::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessingDoc::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessingDoc::OnDivConstant)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessingDoc::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProcessingDoc::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingDoc::OnXorOperate)


	ON_COMMAND(ID_NOT_OPERATE, &CImageProcessingDoc::OnNotOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingDoc::OnNegaTransform)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessingDoc::OnBinarization)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CImageProcessingDoc::OnStressTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingDoc::OnGammaCorrection)
//	ON_UPDATE_COMMAND_UI(ID_STRESS_TRANSFORM, &CImageProcessingDoc::OnUpdateStressTransform)
ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingDoc::OnHistoStretch)
ON_COMMAND(ID_END_IN_SEARCH, &CImageProcessingDoc::OnEndInSearch)
ON_COMMAND(ID_HISTOGRAM, &CImageProcessingDoc::OnHistogram)
ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingDoc::OnHistoEqual)
ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingDoc::OnHistoSpec)

ON_COMMAND(ID_EMBOSSING, &CImageProcessingDoc::OnEmbossing)
ON_COMMAND(ID_BLURR, &CImageProcessingDoc::OnBlurr)
ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProcessingDoc::OnGaussianFilter)
ON_COMMAND(ID_SHARPENING, &CImageProcessingDoc::OnSharpening)
ON_COMMAND(ID_HPF_SHARP, &CImageProcessingDoc::OnHpfSharp)
ON_COMMAND(ID_LPF_SHARP, &CImageProcessingDoc::OnLpfSharp)
ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CImageProcessingDoc::OnDiffOperatorHor)
ON_COMMAND(ID_HOMOGEN_OPERATOR, &CImageProcessingDoc::OnHomogenOperator)
ON_COMMAND(ID_LAPLACIAN, &CImageProcessingDoc::OnLaplacian)
ON_COMMAND(ID_NEAREST, &CImageProcessingDoc::OnNearest)
ON_COMMAND(ID_BILINEAR, &CImageProcessingDoc::OnBilinear)
ON_COMMAND(ID_MEDIAN_SUB, &CImageProcessingDoc::OnMedianSub)
ON_COMMAND(ID_MEAN_SUB, &CImageProcessingDoc::OnMeanSub)
ON_COMMAND(ID_TRANSLATION, &CImageProcessingDoc::OnTranslation)
ON_COMMAND(ID_MIRROR_HOR, &CImageProcessingDoc::OnMirrorHor)
ON_COMMAND(ID_MIRROR_VER, &CImageProcessingDoc::OnMirrorVer)
ON_COMMAND(ID_ROTATION, &CImageProcessingDoc::OnRotation)
ON_COMMAND(ID_FRAME_SUM, &CImageProcessingDoc::OnFrameSum)
ON_COMMAND(ID_FRAME_SUB, &CImageProcessingDoc::OnFrameSub)
ON_COMMAND(ID_FRAME_MUL, &CImageProcessingDoc::OnFrameMul)
ON_COMMAND(ID_FRAME_DIV, &CImageProcessingDoc::OnFrameDiv)
ON_COMMAND(ID_FRAME_MEAN, &CImageProcessingDoc::OnFrameMean)
ON_COMMAND(ID_FRAME_AND, &CImageProcessingDoc::OnFrameAnd)
ON_COMMAND(ID_FRAME_OR, &CImageProcessingDoc::OnFrameOr)
ON_COMMAND(ID_FRAME_COMB, &CImageProcessingDoc::OnFrameComb)
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

	CFile File;	//파일 객체 선언

	//파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	
	//RAW 파일의 크기 결정 
	if (File.GetLength() == 256 * 256)	//선택한 파일이 256*256 크기일 때
	{
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512)	//선택한 파일이 512*512 크기일 때
	{
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) //선택한 파일이 640*480 크기일 때
	{
		m_height = 480;
		m_width = 640;
	}
	else
	{
		AfxMessageBox(L"지원하지 않는 이미지 크기입니다.");
		return 0;
	}

	m_size = m_width * m_height;	//영상의 전체 크기
	
	//입력 영상의 크기에 맞는 메모리 할당
	m_InputImage = new unsigned char[m_size];

	for (int i = 0;i < m_size;i++)	//영상의 모든 픽셀 값을 255로 초기화
		m_InputImage[i] = 255;

	//입력 영상 파일 읽기, 
	//File변수에 저장된 영상의 픽셀 값을 m_InputImage에 저장한다.
	File.Read(m_InputImage, m_size);
	File.Close();
	return TRUE;
}

//영상 데이터가 program에서 처리되어 1 혹은 2차원 배열 형태로 존재될 때 
//이 배열 데이터를 raw파일로 출력를 지원하는 함수
BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File;
	//raw파일을 다른 이름으로 저장하기 위한 대화상자 객체 선언
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);
	if (SaveDlg.DoModal() == IDOK)
	{
		//DoModal 맴버 함수에서 저장하기 수행
		
		//파일열기
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		//파일 쓰기
		File.Write(m_InputImage, m_size);
		File.Close();	
	}
	return TRUE;
}

//영상 축소, 이때 원본 영상의 값을 일정한 좌표 단위로 버린다.
//영상은 2차원이므로 수평축 샘플링과 수직축 샘플링이 모두 있어야한다.
void CImageProcessingDoc::OnDownSampling()
{
	//샘플링 비율로 다운 샘플링을 한다.
	//512*512일 때 샘플링 비율이 2이면 256*256 영상을 얻는다.
	int i, j;
	CDownSampleDlg dlg;	//대화상자에 접근
	if (dlg.DoModal() == IDOK)	//대화상자의 활성화 여부
	{
		//대화 상자로 얻은 다운 샘플링 비율로 축소 시킨 축소 영상의 세로 길이 계산
		m_Re_height = m_height / dlg.m_DownSampleRate;
		//대화 상자로 얻은 다운 샘플링 비율로 축소 시킨 축소 영상의 가로 길이 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		//대화 상자로 얻은 다운 샘플링 비율로 축소 시킨 축소 영상의 전체 크기 계산
		m_Re_size = m_Re_height * m_Re_width;

		//다운 샘플링 비율로 축소 시킨 축소 영상을 위한 메모리 할당
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0;i < m_Re_height;i++)
		{
			for (j = 0;j < m_Re_width;j++)
			{
				//축소 영상 생성
				//입력영상의 픽셀을 DownSampleRate만큼 열을 점프뛰면서 그 자리에 출력영상의 픽셀 업데이트
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
			}
		}
	}
}

//영상 확대, 이때는 일정한 배열 간격으로 재배열한다.
//단순히 업 샘플링을 사용하여 영상을 확대하면 영상 크기가 늘어나면서
//원본 영상에는 없던 픽셀들이 생겨난다. 이 픽셀들에게 어떤 값을 넣을 지를 결정하는 것이 보간 법이다.
void CImageProcessingDoc::OnUpSampling()
{
	int i, j;
	CUpSampleDlg dlg; //대화상자의 활성화 여부
	if (dlg.DoModal() == IDOK)	//DoModal 대화상자의 활성화 여부
	{
		//대화상자로 받은 업샘플링 비율로 세로 크기 업 샘플링
		m_Re_height = m_height * dlg.m_UpSampleRate;	
		//대화상자로 받은 업샘플링 비율로 가로 크기 업 샘플링
		m_Re_width = m_width * dlg.m_UpSampleRate;
		//확대 영상의 전체 크기 계산
		m_Re_size = m_Re_height * m_Re_width;
		
		//확대 영상을 위한 메모리 할당
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0;i < m_Re_size;i++)	//출력영상의 픽셀값들을 0으로 초기화
		{
			m_OutputImage[i] = 0;
		}
		for (i = 0;i < m_height;i++)
		{
			for (j = 0;j < m_width;j++)
			{
				//확대 영상 생성
				//출력영상의 픽셀을 DownSampleRate만큼 열을 점프뛰면서 그 자리에 입력영상의 픽셀 업데이트
				//이때는 보간법이 딱히 없으니 점프 뛰어지면서 스킵된 픽셀들의 값은 계속 0으로 남게된다.
				//이로 인해 업 샘플링 비율이 커질 수록 0값을 갖는 픽셀 수가 많아져 출력 영상이 어두워진다.
				m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width + dlg.m_UpSampleRate * j]
					= m_InputImage[i * m_width + j];
			}
		}
	}
}

/*
표본화된 각 화소의 밝기나 색상을 정해진 몇 단계의 값으로 근사화하는 과정으로
밝기나 색상이 몇 단계로 표현되느냐는 양자화 비트로 결정된다.
*/
void CImageProcessingDoc::OnQuantization()
{
	CQuantizationDlg dlg;
	if (dlg.DoModal() == IDOK)	//양자화 비트 수를 결정하는 대화상자의 활성화 여부
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;
		//출력 영상과 입력 영상의 크기는 차이가 없다. 
		// 양자화 비트에 의해 그저 밝기나 색상이 차이나는 것일 뿐
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		//양자화 처리된 영상을 출력하기 위한 메모리 할당
		m_OutputImage = new unsigned char[m_Re_size];

		//입력 영상 크기(m_size) 와 동일한 메모리 할당
		TEMP = new double[m_size];
		
		LEVEL = 256;	//입력 영상의 양자화 단계(2^8=256)
		HIGH = 256.;
		//양자화 단계 결정(예 : 2^4=16)
		value = (int)pow(2, dlg.m_QuantBit);
		for (i = 0;i < m_size;i++)
		{
			for (j = 0;j < value;j++)
			{
				if (m_InputImage[i] >= (LEVEL / value) * j && m_InputImage[i] < (LEVEL / value) * (j + 1))
					TEMP[i] = (double)(HIGH / value) * j;//양자화 수행
			}
		}
		for (i = 0;i < m_size;i++)
			m_OutputImage[i] = (unsigned char)TEMP[i];//결과 영상 생성
	}
}


//입력 영상의 각 픽셀마다 따로 입력된 상수값을 더한다.
//그러면 출력 영상은 입력 영상보다 전체적으로 밝아진 상태로 출력된다.
//Clamping기법을 사용한다. 
//즉 결과값이 최소값보다 작으면 최소값으로 
//결과값이 최대값보다 크면 최대값으로 한다.
void CImageProcessingDoc::OnSumConstant()
{
	CConstantDlg dlg;	//상수 값을 입력받는 대화상자 접근
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)	//입력 영상의 모든 픽셀을 하나하나 접근
		{
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;	//출력 값이 255보다 크면 255출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
				//상수 값과 원래의 pixel값을 덧셈한다.
		}
	}
}

//입력 영상의 각 픽셀마다 따로 입력된 상수값을 뺀다.
//그러면 출력 영상은 입력 영상보다 전체적으로 어두워진 상태로 출력된다.
//Clamping기법을 사용한다. 
//즉 결과값이 최소값보다 작으면 최소값으로 
//결과값이 최대값보다 크면 최대값으로 한다.
void CImageProcessingDoc::OnSubConstant()
{
	CConstantDlg dlg;	//상수 값을 입력받는 대화상자 접근
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0;	//출력 값이 255보다 크면 255를 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] - dlg.m_Constant);
				//상수 값과 원래의 pixel값을 뺀다.
		}
	}
}

//입력 영상의 모든 pixel들을 각각 사용자가 입력한 동일한 상수값으로 곱해준다.
void CImageProcessingDoc::OnMulConstant()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			if (m_InputImage[i] * dlg.m_Constant > 255)
				m_OutputImage[i] = 255;//곱의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] * dlg.m_Constant < 0)
				m_OutputImage[i] = 0;
			//상수값이 정수가 아닌 유리수 일 때 곱의 값이 0보다 작아질 수 있다.
			//그래서 곱의 값이 0보다 작으면 0을 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] * dlg.m_Constant);
				//상수 값과 pixel값를 곱한다.
		}
	}
}

//입력 영상의 모든 pixel들을 각각 사용자가 입력한 동일한 상수값으로 나눠준다.
void CImageProcessingDoc::OnDivConstant()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			if (m_InputImage[i] / dlg.m_Constant > 255)
				m_OutputImage[i] = 255;	//나눗셈의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] / dlg.m_Constant < 0)
				m_OutputImage[i] = 0;	//나눗셈의 값이 0보다 작으면 0을 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] / dlg.m_Constant);
				//상수 값과 pixel값 나눗셈
		}
	}
}

//원하는 비트를 선택적으로 0으로 만드는 기능이 있어서 mask연산이라고도 한다.
//두 피연산자 중 적어도 1개의 값이 0이면 0이 출력된다(이때 0은 검은색이다).
//두 피연산자 모두 값이 1이어야 1이 출력된다. 
void CImageProcessingDoc::OnAndOperate()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			//비트 단위 AND연산
			//이진수로 표현한 pixel값과 이진수로 표현한 입력값을 AND연산한다.
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
				m_OutputImage[i] = 255;
			else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i] & (unsigned char)dlg.m_Constant);
		}
	}
}

//OR연산은 특정 비트를 선택적으로 1로 구성할 수 있어 selective-set연산이라고도 한다.
void CImageProcessingDoc::OnOrOperate()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			//비트 단위 OR연산
			//이진수로 표현한 pixel값과 이진수로 표현한 입력값을 OR 연산한다.
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255)
				m_OutputImage[i] = 255;
			else if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i] | (unsigned char)dlg.m_Constant);
		}
	}
}

//입력이 서로 다를 때만 1을 출력하는 연산으로, 두 데이터를 비교하므로 compare연산이라 부른다.
//XOR연산은 일반 영상에서 특정 화소 값을 찾는 데 이용한다.
//왜냐, 입력 값과 동일한 화소 값은 0으로 출력되기 때문이다.
void CImageProcessingDoc::OnXorOperate()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for(i=0;i<m_size;i++)
		{
			//비트 단위 XOR연산
			//이진수로 표현한 pixel값과 이진수로 표현한 입력값을 XOR 연산한다.
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255)
				m_OutputImage[i] = 255;
			else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i] ^ (unsigned char)dlg.m_Constant);
		}
	}
}

//not연산으로 입력영상의 모든 픽셀의 각 이진수 값을 bit단위로 반전시킴
void CImageProcessingDoc::OnNotOperate()
{
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0;i < m_size;i++)
	{	
		//비트 단위로 not연산하므로 ~ 연산자 사용
		m_OutputImage[i] = ~m_InputImage[i];
	}
}

//사진학적 역변환을 말한다. 즉 각 화소의 값이 영상 내에 대칭이 되는 값으로 변환된다.
//EX> 0->255, 1->254, 10->245
void CImageProcessingDoc::OnNegaTransform()
{
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0;i < m_size;i++)
		m_OutputImage[i] = 255 - m_InputImage[i];	//영상 반전을 수행한다.
}

//영상의 화소값을 경계 값을 이용해 값이 두 개만 있는 영상으로 변환해준다.
//즉 출력 영상은 이진 영상이고, 명암 대비가 매우 낮은 영상에서는 배경과 물체 구분을 쉽도록 해준다.
void CImageProcessingDoc::OnBinarization()
{
	CConstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255;	//사용자가 입력한 임계 값 보다 크면 255출력
			else
				m_OutputImage[i] = 0; //사용자가 입력한 임계 값 보다 작으면 0출력
		}
	}
}

//영상에서 한 부분의 화소는 원 상태를 그대로 유지한 채 일정 범위의 화소만 강조하는 변환
//원하는 부분의 화소 값이 더 커지거나 작아져 다른 부분과 비교해서 더욱 도드라져 보인다.
void CImageProcessingDoc::OnStressTransform()
{
	CStressTransformDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			//입력 값이 강조 시작 값과 강조 종료 값 사이에 위치하면 255 출력
			if (m_InputImage[i] >= dlg.m_StartPoint && m_InputImage[i] <= dlg.m_EndPoint)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
}

//입출력 관계가 선형적이지 못할 때 보정이 필요하다. 
//Gamma Correction은 입력 값을 조정하여 출력을 제대로 만드는 과정이다. 
//감마 값에 따라 영상을 밝게 하거나 흐르게 조절할 수 있다.
//감마 값이 1보다 크면 영상이 어두워지고, 1보다 작으면 영상이 밝아진다.
void CImageProcessingDoc::OnGammaCorrection()
{
	CConstantDlg dlg;
	int i;
	double temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
	{
		for (i = 0;i < m_size;i++)
		{
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
			//감마 값 계산
			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
}

//입력 영상의 명암 대비를 향상시키는 연산이다. -> 낮은 명암 대비를 보이는 영상의 품질 향상
//특정 부분이나 가운데에 집중된 흐스토그램을 모든 영역으로 확장시켜 디지털 영상이 모든 범위의 화소 값을 포함하게 한다.
//NEW PIXEL=(old pixel-low)*255/(high-low) 이 것이 Stretching공식이다.
//old pixel은 원본 영상 화소의 명도값, new pixel은 결과 영상 화소의 명도 값
//high는 원본 영상의 히스토그램의 최고 명도 값, low는 원본 영상의 히스토그램의 최저 명도값
//255는 8bit gray level 영상의 최고 명도 값
void CImageProcessingDoc::OnHistoStretch()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	MIN = m_InputImage[0];	//최소값을 찾기 위한 초기값
	MAX = m_InputImage[0]; //최대값을 찾기 위한 초기값

	//입력 영상의 최소값 찾기 -> LOW찾기
	for (i = 0;i < m_size;i++)
	{
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	//입력 영상의 최대값 찾기 -> HIGH찾기
	for (i = 0;i < m_size;i++)
	{
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}
	m_OutputImage = new unsigned char[m_Re_size];

	//histogram stretch
	for (i = 0;i < m_size;i++)
	{
		//NEW PIXEL=(old pixel-low)*255/(high-low)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * 255 / (MAX - MIN));
	}
}

//영상의 히스토그램의 기둥이 전 구간에 분포하나 특정 부분에만 집중된 경우의 스트레칭
//new pixel=0, old pixel<=low
//new pixel=(old pixel-low)*255/(high-low), low<=old pixel<=high
//new pixel=255, high<=old pixel
//end_in search방식의 histogram stretch 공식은 위와 같다.
//low는 최저 명도 값쪽의 임계 값으로 최저 명도인 검정색의 양을 결정하도록 사용자가 지정,
//high는 최고 명도 값쪽의 임계 값으로 최고 명도인 흰색의 양을 결정하도록 사용자가 지정한다.
void CImageProcessingDoc::OnEndInSearch()
{
	int i;
	unsigned char MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	//입력 영상의 최저값 찾기 -> LOW찾기
	for (i = 0;i < m_size;i++)
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];

	//입력 영상의 최고값 찾기 -> HIGH찾기
	for (i = 0;i < m_size;i++)
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];

	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0;i < m_size;i++)
	{
		//원본 영상의 최소값보다 작은 값은 0이다.
		////new pixel=0, old pixel<=low
		if (m_InputImage[i] <= MIN)
			m_OutputImage[i] = 0;
		//원본 영상의 최대값보다 큰 값은 255이다.
		//new pixel=255, high<=old pixel
		else if (m_InputImage[i] >= MAX)
			m_OutputImage[i] = 255;
		//new pixel=(old pixel-low)*255/(high-low), low<=old pixel<=high
		else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN) * 255 / (MAX - MIN));
	}
}

//가로 축은 PIXEL이 갖을 수 있는 값, 세로 축은 그 값을 갖는 PIXEL의 빈도수를 나타냄
void CImageProcessingDoc::OnHistogram()
{
	//히스토그램의 값은 0~255	x축의 범위	
	//히스토그램의 크기 값은 MAX=255로 정규화하여 출력한다.	y축의 범위
		//입력 영상의 크기가 256*256일 떄 pixel의 개수는 65,536이다.
		//이때 정규화를 하지 않으면 어떤 pixel의 빈도 수는 15일 때 
		//어떤 pixel의 빈도수는 40,000와 같이 큰 차이가 날 수 있기 때문에 정규화 과정을 거친다.
	//히스토그램의 크기: 256*256로 지정
	int i, j, value;
	double MAX, MIN, DIF;
	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;
	//초기화
	for (i = 0;i < 256;i++)
		m_HIST[i] = 0;
	//빈도 수 조사, 어느 pixel값이 얼마나 있나 조사-> pixel에 대한 빈도수는 m_HIST에 저장
	for (i = 0;i < m_size;i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];
	for (i = 0;i < 256;i++)	//1. 빈도수가 가장 높은 pixel값 찾기
	{
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}
	for (i = 0;i < 256;i++)	//2. 빈도수가 가장 낮은 pixel값 찾기
	{
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];
	}
	DIF = MAX - MIN;
	//정규화된 히스토그램
	for (i = 0;i < 256;i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * 255 / DIF);

	//정규화된 히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];
	for (i = 0;i < m_Re_size;i++)
		m_OutputImage[i] = 255;
	//정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현한다.
	for (i = 0;i < 256;i++)
		for (j = 0;j < m_Scale_HIST[i];j++)
			m_OutputImage[m_Re_width * (m_Re_height - j - 1) + i] = 0;
	//히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시한다.
	for (i = m_Re_height;i < m_Re_height + 5;i++)
		for (j = 0;j < 256;j++)
			m_OutputImage[m_Re_height * i + j] = 255;
	for (i = m_Re_height + 5;i < m_Re_height + 20;i++)
		for (j = 0;j < 256;j++)
			m_OutputImage[m_Re_height * i + j] = j;
	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height * m_Re_width;
}

//어둡게 촬영된 영상의 히스토그램을 조절하여 명암 분포가 빈약한 영상을 균일하게 만든다.
//원본 영상의 히스토그램과 개략적인 모습은 비슷하면서 명암도 분포는 좀더 균일화하게 한다.
void CImageProcessingDoc::OnHistoEqual()
{
	int i, value;
	unsigned char Temp;
	double SUM = 0.0;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	//초기화
	for (i = 0;i < 256;i++)
		m_HIST[i] = 0;
	//빈도수 조사
	for (i = 0;i < m_size;i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//누적 히스토그램 생성 -> 가로축의 값인 0부터 255까지 
	//						  그 가로축에 대한 세로축의 값을 순서대로 더한다.
	//누적 빈도수를 계산한다.
	for (i = 0;i < 256;i++)
	{
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;	
		//i=0부터i=n까지의 빈도수의 값이 m_Sum_Of_HIST[n]에 저장되어 있다. 
	}
	m_OutputImage = new unsigned char[m_Re_size];
	//입력 영상을 평활화된 영상으로 출력 ->빈도수의 누적합에서 정규화를 거친다.
	for (i = 0;i < m_size;i++)
	{
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * 255 / m_size);
	}
}

//특정 모양의 히스토그램을 입력 영상의 히스토그램에 포함하여 영상의 일부 영역의 명암 대비를 개선
//입력 영상을 원하는 히스토그램으로 평활화하여 역히스토그램 평활화를 수행한다.
//그 뒤 Lookup Table을 생성하고 평활화된 원본 영상을 역변환하여 원하는 히스토그램을 얻는다.
//특정 부분을 향상시키려고 원하는 히스토그램을 이용한 정합으로 일부 영역에서만 명암 대비를 개선한다.
void CImageProcessingDoc::OnHistoSpec()
{
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
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
	m_DTEMP = new unsigned char[m_size];
	//원하는 히스토그램이 있는 영상을 입력받는다. 이 영상을 B라 하겠다(이 영상이 아닌 영상을 A라 하겠다).
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead );
		if (File.GetLength() == (unsigned)m_size)
		{
			//입력 영상 파일 읽기, 
			//File변수에 저장된 영상의 모든 픽셀 값을 m_DTEMP에 저장한다.
			File.Read(m_DTEMP, m_size);	
			File.Close();
		}
		else//같은 크기의 영상을 대상으로 하기 때문이다.
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
	LOW = 0;
	HIGH = 255;
	//초기화
	for (i = 0;i < 256;i++)
	{
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
	}
	//두 입력 영상의 pixel값에 대한 빈도 수를 각각 조사
	for (i = 0;i < m_size;i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}
	//두 입력 영상의 누적 히스토그램를 각각 조사
	for (i = 0;i < 256;i++)
	{
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}
	//A영상의 평활화를 진행한다.
	for (i = 0;i < m_size;i++)
	{
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	//B영상의 누적 히스토그램에서 최소값과 최대값을 지정한다.
	//누적 히스토그램 같은 경우는 누적합을 하므로 가로축이 255에 가까워 질 수록 값이 커진다.
	DMIN = m_Sum_Of_DHIST[0];	//누적합의 최소값
	DMAX = m_Sum_Of_DHIST[255];	//누적합의 최대값
	//B영상의 평활화를 진행한다.
	for (i = 0;i < 256;i++)
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i] - DMIN) * HIGH / (DMAX - DMIN));
	//룩업테이블을 이용한 명세화
	for (;;)
	{
		for (i = m_Sum_Of_ScHIST[bottom];i <= m_Sum_Of_ScHIST[top];i++)
			m_TABLE[i] = top;
		top = bottom;
		bottom = bottom - 1;
		if (bottom < -1)
			break;
	}
	for (i = 0;i < m_size;i++)
	{
		DADD = (int)m_Org_Temp[i];
		m_OutputImage[i] = m_TABLE[DADD];
	}

}


//convolution processing을 이용한 영상처리 방법으로 영상에서 특정 부분이 볼록해 보인다.
//이로인해 적절하게 구분된 경계선으로 영상이 볼록한 느낌을 갖게 된다.
void CImageProcessingDoc::OnEmbossing()
{
	int i, j;
	//convolution mask선택
	double EmboMask[3][3] = {
		{-1.,0.,0.},
		{0.,0.,0.},
		{0.,0.,1.}
	};
	/*
	double EmboMask[3][3] = {
		{0.,0.,0.},
		{0.,1.,0.},
		{0.,0.,0.}
	};
	double EmboMask[3][3] = {
		{1.,1.,1.},
		{1.,-8.,1.},
		{1.,1.,1.}
	};
	*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//OnMaskProcess 함수를 호출하여 convolution processing를 한다.
	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);
	//convolution processing 결과가 0~255사이 값이 되도록 한다.
	for (i = 0;i < m_Re_height;i++)
	{
		for (j = 0;j < m_Re_width;j++)
		{
			m_tempImage[i][j] += 128;//convolution processing 결과 +128
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//정규화 함수를 사용할 때
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//convolution processing 결과나 정규화 처리 결과는 2차원 배열 값이 되므로
	//2차원 배열을 1차원 배열로 바꾸어 출력하도록 한다.
	for (i = 0;i < m_Re_height;i++)
		for (j = 0;j < m_Re_width;j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}


//convolution process가 일어나는 함수
double** CImageProcessingDoc::OnMaskProcess(unsigned char* Target, double Mask[3][3])
{
	int i, j, n, m;
	double** tempInputImage, ** tempOutputImage, S = 0.0;
	int mask_size=3;
	//입력 값을 위한 메모리 할당
	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	//출력 값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);

	//1차원 입력 영상의 값을 2차원 배열에 할당한다.
	for (i = 0;i < m_height;i++)
		for (j = 0;j < m_width;j++)
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
	//convolution processing
	for (i = 0;i < m_height;i++)
	{
		for (j = 0;j < m_width;j++)
		{
			for (n = 0;n < mask_size;n++)	//convolution mask의 크기만큼 이동하면서 값을 누적
				for (m = 0;m < mask_size;m++)
					S += Mask[n][m] * tempInputImage[i + n][j + m];
			//누적된 값을 출력 메모리에 저장
			tempOutputImage[i][j] = S;
			//다음 블록으로 이동하면 누적 값을 초기화
			S = 0.0;
		}
	}
	return tempOutputImage;	//결과 값 반환
}

//정규화를 위한 함수
double** CImageProcessingDoc::OnScale(double** Target, int height, int width)
{
	int i, j;
	double min, max;
	min = max = Target[0][0];
	for (i = 0;i < height;i++)
		for (j = 0;j < width;j++)
			if (Target[i][j] <= min)
				min = Target[i][j];
	for (i = 0;i < height;i++)
		for (j = 0;j < width;j++)
			if (Target[i][j] >= max)
				max = Target[i][j];
	max = max - min;
	for (i = 0;i < height;i++)
		for (j = 0;j < width;j++)
			Target[i][j] = (Target[i][j] - min) * (255. / max);
	return Target;
}

//2차원 메모리 할당을 위한 함수, height가 row의 개수, width가 column의 개수를 나타낸다.
double** CImageProcessingDoc::Image2DMem(int height, int width)
{
	double** temp;
	int i, j;
	temp = new double* [height];
	//2차원 메모리 할당
	for (i = 0;i < height;i++)
		temp[i] = new double[width];
	//할당된 2차원 메모리 초기화
	for (i = 0;i < height;i++)
		for (j = 0;j < width;j++)
			temp[i][j] = 0.0;
	return temp;
}

//영상을 흐리게 하거나 배경을 어둡게 만드는 기법
//영상의 경계 부분에 해당하는 세세한 부분(고주파에 해당)을 제거하면 블러링 효과를 얻을 수 있다.
//세세한 부분은 화소 값이 극단적인 값에 속한다. 이를 제거하기 위해 평균값으로 대체한다. 
//BLURRING CONVOLUTION MASK의 계수는 평균을 구하는데 사용되므로 모두 값이 같다. 모든 계수의 합은 항상 1이다.
//이 mask로 이웃 pixel간의 평균 결과를 생성하게 된다. mask의 크기가 크면 클수록 blurring의 효과는 커진다.
void CImageProcessingDoc::OnBlurr()
{
	int i, j;

// /*
	double BlurrMask[3][3] = {
		{1. / 9.,1. / 9.,1. / 9.},
		{1. / 9.,1. / 9.,1. / 9.},
		{1. / 9.,1. / 9.,1. / 9.}
	};
//*/
	// 5*5convolution mask
	/*
	double BlurrMask[5][5]={
		{1./25.,1./25.,1./25.,1./25.,1./25.},
		{1./25.,1./25.,1./25.,1./25.,1./25.},
		{1./25.,1./25.,1./25.,1./25.,1./25.},
		{1./25.,1./25.,1./25.,1./25.,1./25.},
		{1./25.,1./25.,1./25.,1./25.,1./25.}
	};
	*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//blurring processing
	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	
	//mask 적용한 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//blurring processing와 같이 세세한 부분을 제거하여 부드럽게 하는 image processing기법이다.
//이는 가우시안 함수에서 얻은 gaussian filter를 사용한다.
//gaussian filter는 gaussian function를 표본화하여 mask의 계수를 결정한다. 이 mask도 모든 계수는 양의 값으로 합이 1이다.
void CImageProcessingDoc::OnGaussianFilter()
{
	int i, j;
	double GaussianMask[3][3] =
	{
		{1. / 16.,1. / 8.,1. / 16.},
		{1. / 8.,1. / 4.,1. / 8.},
		{1. / 16.,1. / 8.,1. / 16.}
	};
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//gaussian filter processing
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//mask적용한 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//blurring과는 달리 고주파에 해당하는 상세한 부분을 더욱 강조하여 대비 효과를 증가시킨다.
//흐린 영상을 개선하여 선명한 영상을 생성하는 데 주로 사용된다.
//mask의 한 가운데는 양의 값, 바깥 경계에는 음의 값이 있으며, 전체 합은 1이 된다.
//mask의 이러한 구조로 인해 경계선을 더욱 두드러지게 해서 영상의 고주파 성분을 강조한다.
void CImageProcessingDoc::OnSharpening()
{
	int i, j;
/*
	double SharpeningMask[3][3] = {
		{-1.,-1.,-1.},
		{-1.,9.,-1.},
		{-1.,-1.,-1.}
	}
*/
///*
	double SharpeningMask[3][3] = {
		{0.,-1.,0.},
		{-1.,5.,-1.},
		{0.,-1.,0.}
	};
//*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//Sharpening processing
	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//변환 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//고주파 필터는 고주파 성분만 통과시키고 저주파 성분은 차단한다. 이 필터 계수의 합은 0으로, sharpening mask하고는 다르다.
//그렇지만 경계선을 더욱 두드러지게 하는 나머지 동작 특성은 동일하다. 
//sharpening mask보다 더 많은 저주파 성분이 제거되어 단지 경계 부분만 확인할 수 있다.
void CImageProcessingDoc::OnHpfSharp()
{
	int i, j;
	double HpfSharpMask[3][3] = {
		{-1. / 9.,-1. / 9.,-1. / 9.},
		{-1. / 9.,8. / 9.,-1. / 9.},
		{-1. / 9.,-1. / 9.,-1. / 9.}
	};
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//HPF sharpening processing
	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	//변환 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//HPF를 통과한 결과 영상은 LPF를 활용하여 얻을 수도 있다.
//원본 영상에서 LPF를 통과한 결과 영상을 뺄셈하여 얻는다. -> (원본영상)-(LPF 결과 영상)=HFP
//이때 sharpening때와 같은 결과를 내고 싶으면 저주파 성분의 손실을 어느 정도 보상받을 수 있어야 하므로 원본 영상의 밝기를 증가시킨 뒤 저주파 영상을 뺀다.
//->ALPHA*(원본영상)-(LPF결과 영상)=sharpenning convolution mask
void CImageProcessingDoc::OnLpfSharp()
{
	CConstantDlg dlg;	//ALPHA를 입력받기 위한 대화상자
	int i, j, alpha;
	double LpfSharpMask[3][3] = {
		{1. / 9.,1. / 9.,1. / 9.},
		{1. / 9.,1. / 9.,1. / 9.},
		{1. / 9.,1. / 9.,1. / 9.}
	};
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK)
		//대화상자를 이용하여 상수를 입력받는다.
		alpha = (int)dlg.m_Constant;
	//LpfSharpening processing
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);
	for (i = 0; i < m_height; i++)
		for (j = 0; j < m_width; j++)
			m_tempImage[i][j] = (alpha * m_InputImage[i * m_width + j]) - (unsigned char)m_tempImage[i][j];
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	//변환 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//EDGE: 영상의 밝기가 낮은 값에서 높은 값으로 또는 높은 값에서 낮은 값으로 변하는 지점을 말한다.
//화소 간의 차이를 이용하여 egde를 검출한다.
//영상 화소의 위치를 위쪽, 아래쪽, 왼쪽, 오른쪽으로 하나씩 이동시킨 뒤 원래 화소에서 이동 위치의 화소를 빼서 edge를 얻을 수 있다.
void CImageProcessingDoc::OnDiffOperatorHor()
{
	int i, j;
	//중심 화소에서 위쪽으로 하나 이동한 화소를 빼서 수평 edge를 검출하는 mask이다.
	double DiffHorMask[3][3] = {
		{0.,-1.,0.},
		{0.,1.,0.},
		{0.,0.,0.}
	};
	//중심 화소에서 왼쪽으로 하나 이동한 화소를 빼서 수직 edge를 검출하는 mask이다.
/*
	double DiffHorMask[3][3] = {
		{0.,0.,0.},
		{-1.,1.,0.},
		{0.,0.,0.}
	};
*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//edge detection processing
	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	//변환 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//화소를 감산한 값에서 (절대값 중)최대값을 결정하여 edge를 검출한다. 이 과정에서 뺄셈연산이 여러 번 수행되므로 계산 시간이 많이 소요됨
void CImageProcessingDoc::OnHomogenOperator()
{
	int i, j, n, m;
	double max, ** tempOutputImage;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//입력 값을 위한 메모리 할당
	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	//출력 값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);

	//입력 영상을 2차원 배열로 변환한다. 이때 영상의 크기를 가로, 세로 1 pixel정도 더 키운다.
	for (i = 0; i < m_height; i++)
		for (j = 0; j < m_width; j++)
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];

	for (i = 0; i < m_height; i++)
	{
		for (j = 0; j < m_width; j++)
		{
			max = 0.0;	//입력영상내 mask과 연산할 pixel들을 모은 block이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++)
				for (m = 0; m < 3; m++)
					//"블록의 가운데 값 - 블록의 주변 픽셀 값의 절대값" 중에서 최대값을 찾는다.
					if (DoubleABS(m_tempImage[i + 1][j + 1] - m_tempImage[i + n][j + m]) >= max)
						max = DoubleABS(m_tempImage[i + 1][j + 1] - m_tempImage[i + n][j + m]);
			tempOutputImage[i][j] = max;//찾은 최대값을 출력 값으로 지정
		}
	}
	//변환 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)tempOutputImage[i][j];
}


double CImageProcessingDoc::DoubleABS(double X)
{
	//실수의 절대 값 연산 함수
	if (X >= 0)
		return X;
	else
		return -X;
}

//Laplacian연산자는 대표적인 2차 미분 edge detection이다.
//2차 미분을 이용한 edge detection의 장점은 검출된 edge를 끊거나 하지 않고 연결된 폐곡선을 형성한다는 것이다.
//그러나 고립된 잡음에 민감하고, 윤곽의 강도만 검출하지 방향은 구하지 못한다. 
//디지털 데이터의 미분은 간단하게 이웃 데이터와의 차이 값으로 표현되므로, 디지털 영상의 미분은 각 방향의 변화율을 나타낸다.
//2차 미분은 1차 미분을 이용한 edge detection에 미분을 한 번 더 수행하여 얻는다.
void CImageProcessingDoc::OnLaplacian()
{
	int i, j;
	double LaplacianMask[3][3] = {
		{0.,1.,0.},
		{1.,-4.,1.},
		{0.,1.,0.}
	};
/*
	double LaplacianMask[3][3] = {
		{1.,1.,1.},
		{1.,-8.,1.},
		{1.,1.,1.}
	};
*/
/*
	double LaplacianMask[3][3] = {
		{-1.,-1.,-1.},
		{-1.,8.,-1.},
		{-1.,-1.,-1.}
	};
*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//Laplacian processing
	m_tempImage = OnMaskProcess(m_InputImage, LaplacianMask);
	//정규화
	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

	//변환 영상내의 pixel값 정상화
	for (i = 0; i < m_Re_height; i++)
	{
		for (j = 0; j < m_Re_width; j++)
		{
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
	for (i = 0; i < m_Re_height; i++)
		for (j = 0; j < m_Re_width; j++)
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
}

//UpScaling을 하면 출력 영상의 크기는 원본 영상의 크기보다 커지므로 당연히 빈 화소가 생긴다.
//이 빈 화소는 어떻게 채워야 하는가?
//이때는 빈 화소와 인접한 화소의 값으로 빈 화소를 채운다.
void CImageProcessingDoc::OnNearest()
{
	int i, j;
	CUpSampleDlg dlg; //UpScaling 대화상자의 활성화 여부
	if (dlg.DoModal() == IDOK)	//DoModal 대화상자의 활성화 여부
	{
		int ZoomRate = dlg.m_UpSampleRate;//영상 확대 배율, UpScaling 대화상자의 입력값을 받아서 그 배율로 확대
		double** tempArray;
		m_Re_height = int(m_height * ZoomRate);	//ZoomRate배 확대된 출력 영상의 높이
		m_Re_width = int(m_width * ZoomRate);		//ZoomRate배 확대된 출력 영상의 너비
		m_Re_size = m_Re_height * m_Re_width;
		//1차원 배열 형태인 입력 영상을 2차원 배열 형태로 변환
		m_tempImage = Image2DMem(m_height, m_width);
		//출력 영상을 위한 메모리 할당
		tempArray = Image2DMem(m_Re_height, m_Re_width);
		m_OutputImage = new unsigned char[m_Re_size];
		//1차원 배열에 저장된 입력영상을 2차원 배열로 변환
		for (i = 0;i < m_height;i++)
			for (j = 0;j < m_width;j++)
				m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		//이웃한 화소를 이용해 보간을 진행한다.
		for (i = 0;i < m_Re_height;i++)
			for (j = 0;j < m_Re_width;j++)
				tempArray[i][j] = m_tempImage[i / ZoomRate][j / ZoomRate];

		//그 변환 영상내의 모든 pixel를 출력 영상 배열에 넣어 출력 준비를 한다. 즉 2차원 배열을 1차원 배열로 변환
		for (i = 0; i < m_Re_height; i++)
			for (j = 0; j < m_Re_width; j++)
				m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];
	}
}


//보간을 할 때 역방향 사상으로 보간을 할 pixel이 원본 영상에서는 어느 위치에 있는지 확인하고
//만약 위치 좌표가 정수가 아니라면 그 좌표는 바둑판에 바둑돌을 넣는 위치 처럼 4개의 pixel들의 중앙에 위치하기에
//4개의 pixel값을 이용하여 보간을 한다.
void CImageProcessingDoc::OnBilinear()
{
	int i, j, point, i_H, i_W;
	unsigned char newValue;
	double r_H, r_W, s_H, s_W;
	double c1, c2, c3, c4;
	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		double ZoomRate = dlg.m_UpSampleRate;
		m_Re_height = (int)(m_height * ZoomRate);	//사용자가 입력한 배율만큼 확대된 영상의 높이
		m_Re_width = (int)(m_width * ZoomRate);		//사용자가 입력한 배율만큼 확대된 영상의 너비
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];
		//1차원 배열로 저장된 입력 영상을 2차원 배열로 변환
		m_tempImage = Image2DMem(m_height, m_width);
		for (i = 0;i < m_height;i++)
			for (j = 0;j < m_width;j++)
				m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];

		//up_scaling 및 보간
		for(i=0;i<m_Re_height;i++)
			for (j = 0;j < m_Re_width;j++)
			{
				r_H = i / ZoomRate;
				r_W = j / ZoomRate;
				i_H = (int)floor(r_H); //floor는 입력받은 숫자보다 작거나 같은 정수 중에서 가장 큰 값을 반환하는 함수
				i_W = (int)floor(r_W);
				s_H = r_H - i_H;	//높이의 소숫점 값
				s_W = r_W - i_W;	//너비의 소숫점 값
				if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0 || i_W >= (m_width - 1))
				{
					point = i * m_Re_width + j;
					m_OutputImage[point] = 255;
				}
				else
				{
					c1 = (double)m_tempImage[i_H][i_W];	//4개의 pixel값 중 가장 작은 pixel값
					c2 = (double)m_tempImage[i_H][i_W+1];	//c1 오른쪽에 존재하는 pixel
					c3 = (double)m_tempImage[i_H+1][i_W+1];	//c1 오른쪽 밑에 존재하는 pixel
					c4 = (double)m_tempImage[i_H+1][i_W];	//c1 밑에 존재하는 pixel

					//보간 수행(보간을 해야하는 pixel를 기준 x축 방향으로 보간을 2번 수행-> 그들을 더한다)
					newValue = (unsigned char)((c1 * (1 - s_H) * (1 - s_W) + c2 * s_W * (1 - s_H))+ (c3 * s_W * s_H + c4 * (1 - s_W) * s_H));
					point = i * m_Re_width + j;
					m_OutputImage[point] = newValue;
				}
			}
	}
}

//pixel를 smapling하여 축소를 수행하는 Down scaling이다.
//입력 영상의 임의의 화소 영역을 추출하여 그 화소 영역내 모든 pixel값을 오름차순으로 나열한뒤
//중간 값으로 화소 영역을 대치한 뒤 이 값을 smapling하여 축소 영상(출력 영상)의 pixel로 사용한다.
void CImageProcessingDoc::OnMedianSub()
{
	int i, j, n, m, index = 0;	
	double* Mask, Value;
	CDownSampleDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		int M = dlg.m_DownSampleRate;	//M은 서브 샘플링 비율을 나타낸다.
		Mask = new double[M * M];	//마스크의 크기 결정
		//축소 영상의 높이
		m_Re_height = (m_height + 1) / M;
		//축소 영상의 너비
		m_Re_width = (m_width + 1) / M;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		//1차원 배열로 저장된 입력 영상을 2차원 배열로 표현
		m_tempImage = Image2DMem(m_height + 1, m_width + 1);
		for (i = 0;i < m_height;i++)
			for (j = 0;j < m_width;j++)
				m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];

		for(i=0;i<m_height-1;i=i+M)
			for (j = 0;j < m_width - 1;j = j + M)
			{
				//입력 영상내 화소를 임의의 크기의 영역으로 잘라 마스크 배열에 저장
				for (n = 0;n < M;n++)
					for (m = 0;m < M;m++)
						Mask[n * M + m] = m_tempImage[i + n][j + m];
				OnBubleSort(Mask, M * M);//마스크에 저장된 값을 정렬
				Value = Mask[(int)(M * M / 2)];//정렬된 값 중 가운데 값을 선택
				m_OutputImage[index] = (unsigned char)Value;//가운데 값을 출력
				index++;
			}
		
	}
}

//data를 정렬하는 함수
void CImageProcessingDoc::OnBubleSort(double* A, int MAX)
{
	int i, j;
	for (i = 0;i < MAX;i++)
		for (j = 0;j < MAX - 1;j++)
			if (A[j] > A[j + 1])
				OnSwap(&A[j], &A[j + 1]);
}

//data 교환 함수
void CImageProcessingDoc::OnSwap(double* a, double* b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//pixel를 smapling하여 축소를 수행하는 Down scaling이다.
//입력 영상내 임의의 화소 영역을 영역 내 화소의 평균값으로 대치하는 방법이다. 
//이렇게 얻은 평균값이 해당 축소 영상의 화소 값으로 사용된다.
//평균은 LPF의 역할을 수행하므로 스무딩한 영상을 출력한다.
void CImageProcessingDoc::OnMeanSub()
{
	int i, j, n, m, index = 0, k;
	double* Mask, Value, Sum = 0.0;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int M = dlg.m_DownSampleRate;
		Mask = new double[M * M];
		//축소 영상의 높이를 나타냄
		m_Re_height = (m_height + 1) / M;
		//축소 영상의 너비를 나타냄
		m_Re_width = (m_width + 1) / M;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		m_tempImage = Image2DMem(m_height + 1, m_width + 1);
		for (i = 0;i < m_height;i++)
			for (j = 0;j < m_width;j++)
				m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		
		for(i=0;i<m_height-1;i=i+M)
			for (j = 0;j < m_width - 1;j = j + M)
			{
				//입력 영상내 화소를 임의의 크기의 영역으로 잘라 마스크 배열에 저장
				for (n = 0;n < M;n++)
					for (m = 0;m < M;m++)
						Mask[n * M + m] = m_tempImage[i + n][j + m];
				
				//마스크에 저장된 값을 누적
				for (k = 0;k < M * M;k++)
					Sum = Sum + Mask[k];
				//그에 대한 평균을 계산
				Value = (Sum / (M * M));
				m_OutputImage[index] = (unsigned char)Value;	//평균값 출력
				index++;
				Sum = 0.0;
			}
	}
}

//원본 영상내의 각 화소의 좌변 변환으로 전체적으로 영상의 이동이 발생한다.
void CImageProcessingDoc::OnTranslation()
{
	int i, j;
	double** tempArray;
	CTranslationDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int h_pos = dlg.t_height, w_pos = dlg.t_width;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		m_tempImage = Image2DMem(m_height, m_width);
		tempArray = Image2DMem(m_Re_height, m_Re_width);
		for (i = 0;i < m_height;i++)
			for (j = 0;j < m_width;j++)
				m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];

		//입력영상을 h_pos, w_pos만큼 이동
		for (i = 0;i < m_height - h_pos;i++)
			for (j = 0;j < m_width - w_pos;j++)
				tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];

		for (i = 0;i < m_Re_height;i++)
			for (j = 0;j < m_Re_width;j++)
				m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];

		delete[] m_tempImage;
		delete[] tempArray;
	}
}

//영상을 세로축을 중심으로 단순히 뒤집는다. -> 한 수직선을 중심으로 왼쪽 화소와 오른쪽 화소를 서로 교환
void CImageProcessingDoc::OnMirrorHor()
{
	int i, j;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	//입력 영상의 행을 기준으로 그 행 맨 끝에 있는 pixel값은 출력 영상의 같은 순서의 행에 맨 처음에 있는 pixel에 들어간다.
	//이렇게 영상의 중심을 기준으로 영상을 대칭 이동 시킨다.
	for (i = 0;i < m_height;i++)
		for (j = 0;j < m_width;j++)
			m_OutputImage[i * m_width + m_width - j - 1] = m_InputImage[i * m_width + j];
}

//영상 내의 한 수평선을 중심으로 위쪽의 화소와 아래쪽으 화소를 단순히 교환한다.
void CImageProcessingDoc::OnMirrorVer()
{
	int i, j;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	//입력 영상의 열을 기준으로 그 열 맨 끝에 있는 pixel값은 출력 영상의 같은 순서의 열에 맨 처음에 있는 pixel에 들어간다.
	for (i = 0;i < m_height;i++)
		for (j = 0;j < m_width;j++)
			m_OutputImage[(m_height - i - 1) * m_width + j] = m_InputImage[i * m_width + j];
}

//영상 회전은 많은 부분을 고려해야한다. 그렇기에 이에 대한 부분은 교과서를 한 번 살펴보기 바란다(p.332).
void CImageProcessingDoc::OnRotation()
{
	int i, j, CenterH, CenterW, newH, newW;
	double Radian, PI, ** tempArray, Value;
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int degree = dlg.m_Constant;	//degree는 회전할 각도이다.
		PI = 3.14159265358979;			//회전각을 위한 PI값
		Radian = (double)degree * PI / 180.0;	//회전할 각도를 radian으로 변경
		m_Re_height = m_height;					//회전된 영상의 높이
		m_Re_width = m_width;		//회전된 영상의 너비
		m_Re_size = m_Re_height * m_Re_width;
		CenterH = m_height / 2;			//영상의 중심 좌표의 높이
		CenterW = m_width / 2;			//영상의 중심 좌표의 너비
		m_tempImage = Image2DMem(m_height, m_width);
		tempArray = Image2DMem(m_Re_height, m_Re_width);
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0;i < m_height;i++)
			for (j = 0;j < m_width;j++)
				m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];

		for(i=0;i<m_height;i++)
			for (j = 0;j < m_width;j++)
			{
				//회전 변환 행렬을 이용하여 회전하게 될 좌표 값 계산
				newH = (int)((i - CenterH) * cos(Radian) - (j - CenterW) * sin(Radian) + CenterH);
				newW = (int)((i - CenterH) * sin(Radian) + (j - CenterW) * sin(Radian) + CenterW);

				//회전된 좌표가 출력 영상을 위한 배열 값을 넘어가 짤릴 때
				if (newH < 0 || newH >= m_height)
					Value = 0;
				else if (newW < 0 || newW >= m_width)
					Value = 0;
				else	//짤림 현상이 없을 때
					Value = m_tempImage[newH][newW];
				tempArray[i][j] = Value;
			}
		
		for (i = 0;i < m_Re_height;i++)
			for (j = 0;j < m_Re_width;j++)
				m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];

		delete[] m_tempImage;
		delete[] tempArray;
	}
}

//서로 다른 두 영상의 같은 위치에 있는 화소를 더한다.
//두 영상을 합성하는데 응용할 수도 있다.
void CImageProcessingDoc::OnFrameSum()
{
	CFile File;	//덧셈할 영상을 입력받기 위한 변수
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char* temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (OpenDlg.DoModal() == IDOK)
	{
		//덧셈연산을 수행할 새로운 영상을 얻기 위해 열기 대화상자를 이용해 영상을 입력
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			//입력 값 저장을 위한 배열 선언
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);	//선택된 파일을 읽어 배열에 저장
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 덧셈 연산 실행
			for (i = 0;i < m_size;i++)
			{
				if (m_InputImage[i] + temp[i] > 255)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = m_InputImage[i] + temp[i];
			}
		}
		else
		{
			//영상의 크기가 서로 다를 때는 처리하지 않음
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}

//한 영상에서 다른 영상의 값을 빼서 두 영상 사이의 차이를 결정하는 FRAME processing이다.
//영상의 변화를 검출하는 데 효율적으로 사용된다.	-> 두 영상이 서로 다른 부분만 출력될 것이므로
void CImageProcessingDoc::OnFrameSub()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 뺄셈연산 실행
			for (i = 0;i < m_size;i++)
			{
				if (m_InputImage[i] - temp[i] < 0)
					m_OutputImage[i] = 0;
				else
					m_OutputImage[i] = m_InputImage[i] - temp[i];

			}
		}
		else
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}

//한 영상에서 다른 영상의 값을 곱해서 두 영상를 합성하는 FRAME processing이다.
//덧셈과 마찬가지로 영상을 합성하는 역할을 한다.
void CImageProcessingDoc::OnFrameMul()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	
	m_OutputImage = new unsigned char[m_Re_size];
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 곱셈연산 실행
			for (i = 0;i < m_size;i++)
			{
				if (m_InputImage[i] * temp[i] > 255)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = m_InputImage[i] * temp[i];
			}
		}
		else
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}

//한 영상에서 다른 영상의 값을 나누는 FRAME processing이다.
void CImageProcessingDoc::OnFrameDiv()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 나눗셈 연산 실행
			for (i = 0;i < m_size;i++)
			{
				//나뉘는 값이 0이면 출력은 영상에서의 최소값
				if (m_InputImage[i] == 0)
					m_OutputImage[i] = 0;
				//나누는 값이 0이면 출력은 영상에서의 최대값
				else if (temp[i] == 0)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = (unsigned char)(m_InputImage[i] / temp[i]);
			}
		}
		else
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}

//같은 영상 여러장을 다른 종류의 잡음으로 훼손하였다면 모두 영상의 평균을 구해서 자연스럽게 잡음을 제거하면 된다.
//서로 다른 두 영상의 같은 위치의 화소값을 더하고 더한 값을 2로 나눈다.
void CImageProcessingDoc::OnFrameMean()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char* temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 평균연산 실행
			for (i = 0;i < m_size;i++)
			{
				if (m_InputImage[i] + temp[i] > 255)
					m_OutputImage[i] = (unsigned char)(255 / 2);
				else
					m_OutputImage[i] = (unsigned char)((m_InputImage[i] + temp[i]) / 2);
			}
		}
		else
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}

//영상 합성을 위해 AND연산 사용
//이것은 영상의 특정 부분을 상쇄하는 데 사용된다. 상쇄된 부분에는 새로운 영상을 추가한다.
void CImageProcessingDoc::OnFrameAnd()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 AND연산 실행
			for (i = 0;i < m_size;i++)
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] & temp[i]);
			}
		}
		else
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}

//영상 합성을 위해 OR연산 사용
//영상 하나에 다른 영상의 특정 부분을 추가할 때 사용된다.
void CImageProcessingDoc::OnFrameOr()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (OpenDlg.DoModal() == IDOK)
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height)
		{
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			//프레임 간에 픽셀 대 픽셀로 OR연산 실행
			for (i = 0;i < m_size;i++)
			{
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] | temp[i]);
			}
		}
		else
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CImageProcessingDoc::OnFrameComb()
{
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char* temp, * masktemp, maskvalue;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	AfxMessageBox(L"합성할 영상을 입력하시오");

	temp = new unsigned char[m_size];
	if (OpenDlg.DoModal() == IDOK)	//합성할 영상을 입력
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		File.Read(temp, m_size);
		if ((unsigned)m_width * m_height != File.GetLength())
		{
			AfxMessageBox(L"Image size not matched");
			return;
		}
		File.Close();
	}
	//입력 영상, 합성할 영상, 마스크 영상의 크기가 같아야 한다.
	AfxMessageBox(L"입력 영상의 마스크 영상을 입력하시오");

	masktemp = new unsigned char[m_size];
	if (OpenDlg.DoModal() == IDOK)	//입력 영상의 마스크 영상
	{
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		File.Read(masktemp, m_size);
		File.Close();
	}

	for (i = 0;i < m_size;i++)
	{
		maskvalue = 255 - masktemp[i];	//영상의 최대값에서 마스크 영상의 값을 뺀다.
		
		//입력 영상과 마스크 영상은 AND 연산을 하고, 합성할 영상은 (255-마스크 영상) 값과 AND연산을 실행한 후 두 값을 더한다.
		m_OutputImage[i] = (m_InputImage[i] & masktemp[i]) | (temp[i] & maskvalue);
	}
}
