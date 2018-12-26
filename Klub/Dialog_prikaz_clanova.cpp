// Dialog_prikaz_clanova.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Klub.h"
#include "DialogClanovi.h"
#include "Dialog_prikaz_clanova.h"
#include "DialogClanarine.h"
#include "Dialog_Natjecanja.h"


// Dialog_prikaz_clanova dialog

IMPLEMENT_DYNAMIC(Dialog_prikaz_clanova, CDialog)

Dialog_prikaz_clanova::Dialog_prikaz_clanova(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_PRIKAZ_CLANOVA, pParent)
	, m_rb_stanje(0)
{	
}


Dialog_prikaz_clanova::~Dialog_prikaz_clanova()
{
}

void Dialog_prikaz_clanova::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLANOVI, m_Lista_Clanovi);
	DDX_Control(pDX, IDC_RD_AKTIVNI, m_rd_aktivni);
	DDX_Control(pDX, IDC_RD_NEAKTIVNI, m_rd_neaktivni);
	DDX_Control(pDX, IDC_RD_SVI, m_rd_svi);
	DDX_Radio(pDX, IDC_RD_AKTIVNI, m_rb_stanje);
	DDX_Control(pDX, IDC_BTN_PRIKAZI, m_btn_prikazi);
}


BEGIN_MESSAGE_MAP(Dialog_prikaz_clanova, CDialog)
	ON_BN_CLICKED(IDC_BTN_PRIKAZI, &Dialog_prikaz_clanova::OnBnClickedBtnPrikazi)	
	ON_BN_CLICKED(IDC_BTN_ISPISI_PRIKAZ, &Dialog_prikaz_clanova::OnBnClickedBtnIspisiPrikaz)
	ON_BN_CLICKED(IDC_BTN_ZATVORI_APLIKACIJU, &Dialog_prikaz_clanova::OnBnClickedBtnZatvoriAplikaciju)
	ON_BN_CLICKED(IDC_BTN_POCETNA4, &Dialog_prikaz_clanova::OnBnClickedBtnPocetna4)
	ON_BN_CLICKED(IDC_BTN_CLANARINE4, &Dialog_prikaz_clanova::OnBnClickedBtnClanarine4)
	ON_BN_CLICKED(IDC_BTN_NATJECANJA4, &Dialog_prikaz_clanova::OnBnClickedBtnNatjecanja4)
END_MESSAGE_MAP()


// Dialog_prikaz_clanova message handlers


BOOL Dialog_prikaz_clanova::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, FALSE);

	RClanovi = new CClanoviSet;
	popuni_naslove();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_prikaz_clanova::popuni_naslove()
{
	m_Lista_Clanovi.InsertColumn(0, _T("Ime"), LVCFMT_LEFT, 150); 
	m_Lista_Clanovi.InsertColumn(1, _T("Datum roðenja"), LVCFMT_CENTER, 120);
	m_Lista_Clanovi.InsertColumn(2, _T("Telefon"), LVCFMT_CENTER, 100);
	m_Lista_Clanovi.InsertColumn(3, _T("Adresa"), LVCFMT_LEFT, 180);
	m_Lista_Clanovi.InsertColumn(4, _T("Mail"), LVCFMT_LEFT, 150);
	m_Lista_Clanovi.InsertColumn(5, _T("Aktivnost"), LVCFMT_LEFT, 80);
}

void Dialog_prikaz_clanova::popuni_listu()
{
	int nIndex;
	if (m_rd_aktivni.GetCheck() == 1)
	{		
		RClanovi->m_strFilter = _T("Aktivnost = 'aktivan'");
	}
	else if (m_rd_neaktivni.GetCheck() == 1)
	{		
		RClanovi->m_strFilter = _T("Aktivnost = 'neaktivan' or Aktivnost = 'ispisan'");
	}

	m_Lista_Clanovi.DeleteAllItems();

	if (!RClanovi->IsOpen())
		RClanovi->Open();

	if (RClanovi->IsBOF() && RClanovi->IsEOF())
	{
		MessageBox(_T("U bazi nema podataka"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	else
	{
		while (!RClanovi->IsEOF())
		{
			nIndex = m_Lista_Clanovi.InsertItem(0, RClanovi->m_ImePrezime);

			CTime dat = RClanovi->m_DatumRodenja;
			CString strDat = dat.Format(_T("%d.%m.%Y"));

			m_Lista_Clanovi.SetItemText(nIndex, 1, strDat);
			m_Lista_Clanovi.SetItemText(nIndex, 2, RClanovi->m_Tel);
			m_Lista_Clanovi.SetItemText(nIndex, 3, RClanovi->m_Adresa);
			m_Lista_Clanovi.SetItemText(nIndex, 4, RClanovi->m_Mail);
			m_Lista_Clanovi.SetItemText(nIndex, 5, RClanovi->m_Aktivnost);
			RClanovi->MoveNext();
		}		
		RClanovi->m_strFilter = "";
		RClanovi->Close();
	}
}


void Dialog_prikaz_clanova::OnBnClickedBtnPrikazi()
{
	popuni_listu();
}


void Dialog_prikaz_clanova::OnBnClickedBtnIspisiPrikaz()
{
	// TODO: Add your control notification handler code here
	int z = m_Lista_Clanovi.GetItemCount();
	if (z == 0)
	{
		MessageBox(_T("Nema podataka za ispis"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	else
	{
		Print();
	}
}



void Dialog_prikaz_clanova::OnBnClickedBtnZatvoriAplikaciju()
{
	PostQuitMessage(0);
}



void Dialog_prikaz_clanova::OnBnClickedBtnPocetna4()
{
	DialogClanovi *pPar = (DialogClanovi*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();
}


void Dialog_prikaz_clanova::OnBnClickedBtnClanarine4()
{
	DialogClanarine* DClanarine;
	DClanarine = new DialogClanarine;

	DialogClanovi *pPar = (DialogClanovi*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();

	DClanarine->DoModal();
}


void Dialog_prikaz_clanova::OnBnClickedBtnNatjecanja4()
{
	Dialog_Natjecanja* DNatjecanja;
	DNatjecanja = new Dialog_Natjecanja;

	DialogClanovi *pPar = (DialogClanovi*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();

	DNatjecanja->DoModal();
}


void Dialog_prikaz_clanova::OnBeginPrinting(CDC *pDC, CPrintInfo* pInfo)
{
	ASSERT(m_pFntData == 0);
	ASSERT(m_pFntHeader1 == 0);
	ASSERT(m_pFntHeader2 == 0);
	
	// Create the normal font used for the fields. Arial, normal is used.
	m_pFntData = new CFont;
	ASSERT(m_pFntData);
	m_pFntData->CreateFont(50,
		0,
		0,
		0,
		FW_NORMAL, 
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_ROMAN,
		_T("Arial"));
	// Create the normal font used for the Headline banner.
	// TimesRoman is used.
	m_pFntHeader1 = new CFont;
	ASSERT(m_pFntHeader1);
	m_pFntHeader1->CreateFont(210,
		0,
		0,
		0,
		FW_NORMAL,
		TRUE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_ROMAN,
		_T("Times Roman"));
	// Create the normal font used for the Headline highlight.
	// This is the text used under the headline banner, Arial is used.
	m_pFntHeader2 = new CFont;
	ASSERT(m_pFntHeader2);
	m_pFntHeader2->CreateFont(60,
		0,
		0,
		0,
		FW_BOLD,
		TRUE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_ROMAN,
		_T("Arial"));

	INT brIt = m_Lista_Clanovi.GetItemCount();
	FLOAT brStr;
	if (brIt % 16 == 0)
		brStr = brIt / 16;
	else
		brStr = brIt / 16 + 1;
	
	pInfo->SetMaxPage(brStr);
}

void Dialog_prikaz_clanova::OnPrint(CDC *pDC, CPrintInfo* pInfo)
{	
	CString s;
	int sirina_p = pDC->GetDeviceCaps(HORZRES);
	int visina_p = pDC->GetDeviceCaps(VERTRES);
	CSize font = pDC->GetTextExtent(_T("A"));
	int x1 = sirina_p / 10;
	int y1 = font.cy * 10;//4;

	CString text;

	TEXTMETRIC tm;
	PrintHeader(pDC, pInfo);
	
	CFont* pOldFont = pDC->SelectObject(m_pFntData);
	pDC->GetTextMetrics(&tm);
	
	int flag = pInfo->m_nCurPage;
	CString rb;
		for (int red = 1+16*(flag-1); red < m_Lista_Clanovi.GetItemCount() && red<=16*flag; red++)
		{
			rb.Format(_T("%ld"), red);
			pDC->TextOut(x1, y1 += 100, rb +_T("."));
			pDC->TextOut(x1*1.5, y1, m_Lista_Clanovi.GetItemText(red, 0));
			pDC->TextOut(x1*3.8, y1, m_Lista_Clanovi.GetItemText(red, 1));
			pDC->TextOut(x1*5.2, y1, m_Lista_Clanovi.GetItemText(red, 5));
			pDC->TextOut(x1 * 2, y1 += 70, m_Lista_Clanovi.GetItemText(red, 3));
			pDC->TextOut(x1 * 4.5, y1, m_Lista_Clanovi.GetItemText(red, 4));
			pDC->TextOut(x1 * 7, y1, m_Lista_Clanovi.GetItemText(red, 2));
		}	
}

void Dialog_prikaz_clanova::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	delete m_pFntData;
	delete m_pFntHeader1;
	delete m_pFntHeader2;
	
	m_pFntData = 0;
	m_pFntHeader1 = 0;
	m_pFntHeader2 = 0;	
}

void Dialog_prikaz_clanova::Print()
{
	CDC pDC;
	CPrintDialog printDlg(FALSE);

	if (printDlg.DoModal() == IDCANCEL)     // Get printer settings from user
		return;

	pDC.Attach(printDlg.GetPrinterDC());     // Get and attach a printer DC

	pDC.m_bPrinting = TRUE;

	CString strTitle;                       // Get the application title
	strTitle.LoadString(AFX_IDS_APP_TITLE);

	DOCINFO di;                             // Initialize print document details

	::ZeroMemory(&di, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;

	BOOL bPrintingOK = pDC.StartDoc(&di);    // Begin a new print job
						// Get the printing extents and store in the m_rectDraw field of a 
						// CPrintInfo object
	CPrintInfo pInfo;

	pInfo.m_rectDraw.SetRect(0, 0,
		pDC.GetDeviceCaps(HORZRES),
		pDC.GetDeviceCaps(VERTRES));

	OnBeginPrinting(&pDC, &pInfo);            // Call your "Init printing" function
	
	for (UINT page = pInfo.GetMinPage();
		page <= pInfo.GetMaxPage() && bPrintingOK;
		page++)
	{
		pDC.StartPage();                     // begin new page
		
		pInfo.m_nCurPage = page;

		OnPrint(&pDC, &pInfo);                // Call your "Print page" function

		bPrintingOK = (pDC.EndPage() > 0);   // end page
	}
	OnEndPrinting(&pDC, &pInfo);              // Call your "Clean up" function

	if (bPrintingOK)
		pDC.EndDoc();                        // end a print job

	else
		pDC.AbortDoc();                      // abort job.

	pDC.DeleteDC();                          // delete the printer DC

}


void Dialog_prikaz_clanova::PrintHeader(CDC* pDC, CPrintInfo *pInfo)
{
	ASSERT(pDC);
	TEXTMETRIC tm;
	CPoint pt(0, 0);
	// Select the Header font, and print the headline.
	CFont* pOldFont = pDC->SelectObject(m_pFntHeader1);
	ASSERT(pOldFont);
	pDC->GetTextMetrics(&tm);
	int cyText =  tm.tmHeight*0.5 + tm.tmExternalLeading;
	pt.y += cyText;
	pDC->TextOut(pt.x+170, pt.y, _T("KARATE  KLUB  \"RONIN\""));
	// Move down one line, and print and underline bar. This is the same
	// pen used to draw black lines in the control. 
	CPen* pOldPen = pDC->SelectObject(&m_penBlack);
	ASSERT(pOldPen);
	pt.y += cyText*2;
	pDC->MoveTo(pt);
	pDC->LineTo(10000, pt.y);
	
	VERIFY(pDC->SelectObject(m_pFntHeader2));
	
	pt.y += (cyText / 4);

	CString clanovi;
	if (m_rd_aktivni.GetState() == 1)
		clanovi = _T("Aktivni članovi kluba ");
	else if(m_rd_neaktivni.GetState() == 1)
		clanovi = _T("Neaktivni članovi kluba ");
	else if (m_rd_svi.GetState() == 1)
		clanovi = _T("Popis članova kluba ");

	CTime dat = CTime::GetCurrentTime();
	CString datum = dat.Format(_T("%d.%m.%Y"));

	UINT st = pInfo->m_nCurPage;
	UINT uk = pInfo->GetMaxPage();
	CString str, ukStr;
	str.Format(_T("%u"), st);
	ukStr.Format(_T("%u"), uk);

	pDC->TextOut(pt.x+300, pt.y, clanovi + _T("na dan:   ")+datum + _T("             str.  ")+str + _T("/")+ukStr);
	// Restore GDI objects.
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}
