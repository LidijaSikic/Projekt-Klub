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
