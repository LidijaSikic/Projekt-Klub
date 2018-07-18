
// KlubView.cpp : implementation of the CKlubView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Klub.h"
#endif

#include "KlubSet.h"
#include "KlubDoc.h"
#include "KlubView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKlubView

IMPLEMENT_DYNCREATE(CKlubView, CRecordView)

BEGIN_MESSAGE_MAP(CKlubView, CRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BTN_CLANOVI, &CKlubView::OnBnClickedBtnClanovi)
	ON_BN_CLICKED(IDC_BTN_CLANARINE, &CKlubView::OnBnClickedBtnClanarine)
	ON_BN_CLICKED(IDC_BTN_NATJECANJA, &CKlubView::OnBnClickedBtnNatjecanja)
END_MESSAGE_MAP()

// CKlubView construction/destruction

CKlubView::CKlubView()
	: CRecordView(IDD_KLUB_FORM)
{
	m_pSet = NULL;
	// TODO: add construction code here

}

CKlubView::~CKlubView()
{
}

void CKlubView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// See MSDN and ODBC samples for more information
}

BOOL CKlubView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CKlubView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_KlubSet;
	CRecordView::OnInitialUpdate();

}


// CKlubView printing

BOOL CKlubView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKlubView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKlubView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKlubView diagnostics

#ifdef _DEBUG
void CKlubView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CKlubView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CKlubDoc* CKlubView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKlubDoc)));
	return (CKlubDoc*)m_pDocument;
}
#endif //_DEBUG


// CKlubView database support
CRecordset* CKlubView::OnGetRecordset()
{
	return m_pSet;
}



// CKlubView message handlers





void CKlubView::OnBnClickedBtnClanovi()
{
	DClanovi = new DialogClanovi;
	DClanovi->DoModal();
}


void CKlubView::OnBnClickedBtnClanarine()
{
	DClanarine = new DialogClanarine;
	DClanarine->DoModal();
}


void CKlubView::OnBnClickedBtnNatjecanja()
{
	DNatjecanja = new Dialog_Natjecanja;
	DNatjecanja->DoModal();
}
