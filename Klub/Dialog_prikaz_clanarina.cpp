// Dialog_prikaz_clanarina.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Klub.h"
#include "DialogClanovi.h"
#include "DialogClanarine.h"
#include "Dialog_prikaz_clanarina.h"
#include "Dialog_Natjecanja.h"


// Dialog_prikaz_clanarina dialog

IMPLEMENT_DYNAMIC(Dialog_prikaz_clanarina, CDialog)

Dialog_prikaz_clanarina::Dialog_prikaz_clanarina(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_PRIKAZ_CLANARINA, pParent)
	, m_rb_stanje(0)
	, m_rb_stanje_datumi(0)
{	
}

Dialog_prikaz_clanarina::~Dialog_prikaz_clanarina()
{
}

void Dialog_prikaz_clanarina::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RD_CLAN, m_rd_clan);
	DDX_Control(pDX, IDC_RD_KLUB, m_rd_klub);
	DDX_Radio(pDX, IDC_RD_CLAN, m_rb_stanje);
	DDX_Control(pDX, IDC_DATE_OD, m_date_od);
	DDX_Control(pDX, IDC_DATE_DO, m_date_do);
	DDX_Control(pDX, IDC_BTN_PRIKAZI, m_btn_prikazi);
	DDX_Control(pDX, IDC_LIST1, m_lista);
	DDX_Control(pDX, IDC_COMBO, m_combo);
	DDX_Control(pDX, IDC_RD_SVE_UPLATE, m_rd_sve_uplate);
	DDX_Control(pDX, IDC_RD_RAZDOBLJE, m_rd_razdoblje);
	DDX_Radio(pDX, IDC_RD_SVE_UPLATE, m_rb_stanje_datumi);
	DDX_Control(pDX, IDC_EDIT_POM, m_edit_pom);
}


BEGIN_MESSAGE_MAP(Dialog_prikaz_clanarina, CDialog)
	ON_BN_CLICKED(IDC_BTN_PRIKAZI, &Dialog_prikaz_clanarina::OnBnClickedBtnPrikazi)
	ON_BN_CLICKED(IDC_BTN_ISPISI_PRIKAZ, &Dialog_prikaz_clanarina::OnBnClickedBtnIspisiPrikaz)
	ON_BN_CLICKED(IDC_BTN_ZATVORI_APLIKACIJU1, &Dialog_prikaz_clanarina::OnBnClickedBtnZatvoriAplikaciju1)
	ON_BN_CLICKED(IDC_BTN_POCETNA, &Dialog_prikaz_clanarina::OnBnClickedBtnPocetna)
	ON_BN_CLICKED(IDC_BTN_CLANOVI1, &Dialog_prikaz_clanarina::OnBnClickedBtnClanovi1)
	ON_BN_CLICKED(IDC_BTN_NATJECANJA1, &Dialog_prikaz_clanarina::OnBnClickedBtnNatjecanja1)
END_MESSAGE_MAP()


// Dialog_prikaz_clanarina message handlers


BOOL Dialog_prikaz_clanarina::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, FALSE);

	m_date_od.SetFormat(_T("dd.MM.yyyy"));
	m_date_do.SetFormat(_T("dd.MM.yyyy"));

	RClanovi = new CClanoviSet;
	RClanarine = new CClanarineSet;

	if (!RClanovi->IsOpen())
		RClanovi->Open();

	if (RClanovi->IsBOF() && RClanovi->IsEOF())
	{
		MessageBox(_T("U bazi nema podataka"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);		
	}
	else
	{
		while (!RClanovi->IsEOF()) {
			m_combo.AddString(RClanovi->m_ImePrezime);
			RClanovi->MoveNext();
		}
	}
	RClanovi->Close();
	m_combo.SetCurSel(0);

	popuni_naslove();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE	
}


void Dialog_prikaz_clanarina::popuni_naslove()
{
	m_lista.InsertColumn(0, _T("Ime"), LVCFMT_LEFT, 180);         
	m_lista.InsertColumn(1, _T("Datum uplate"), LVCFMT_CENTER, 120);
	m_lista.InsertColumn(2, _T("Iznos"), LVCFMT_CENTER, 80);
	m_lista.InsertColumn(3, _T("Svrha"), LVCFMT_LEFT, 200);
}


void Dialog_prikaz_clanarina::OnBnClickedBtnPrikazi()
{
	m_lista.DeleteAllItems();
	while (m_lista.DeleteColumn(0));
	
	int nIndex;
	CString ime;

	if (m_rd_clan.GetCheck() == 1)
	{			
		int nSel=m_combo.GetCurSel();
		if( nSel != LB_ERR)
		{
			m_combo.GetLBText(nSel, ime);
		}

		m_lista.InsertColumn(0, ime, LVCFMT_LEFT, 180);
		m_lista.InsertColumn(1, _T("Datum uplate"), LVCFMT_CENTER, 120);
		m_lista.InsertColumn(2, _T("Iznos"), LVCFMT_CENTER, 80);
		m_lista.InsertColumn(3, _T("Svrha"), LVCFMT_LEFT, 200);

		CString strIDclana;
		strIDclana.Format(_T("%ld"), NadiIDclana());
		if (m_rd_sve_uplate.GetCheck() == 1)
		{
			RClanarine->m_strFilter = _T("IDclana = ") + strIDclana + _T("");
			RClanarine->m_strSort = _T("DatumUplate DESC");
		}
		else if (m_rd_razdoblje.GetCheck() == 1)
		{
			CTime DateOd, DateDo;
			m_date_od.GetTime(DateOd);
			CString strDateOd = DateOd.Format(_T("%m/%d/%y"));

			m_date_do.GetTime(DateDo);
			CString strDateDo = DateDo.Format(_T("%m/%d/%y"));

			RClanarine->m_strFilter = _T("IDclana = ") + strIDclana + _T(" ") + _T(" and ") + _T("(DatumUplate between #") + strDateOd + _T("#") + _T(" and #") + strDateDo + _T("#)");
			RClanarine->m_strSort = _T("DatumUplate DESC");
		}
		if (!RClanarine->IsOpen())
			RClanarine->Open();

		if (RClanarine->IsBOF() && RClanarine->IsEOF())
		{
			MessageBox(_T("Èlan ") + ime + _T(" nema zabilježenih uplata"), _T("Obavijest"), MB_ICONINFORMATION | MB_OK);
		}
		else
		{
			while (!RClanarine->IsEOF())
			{
				if (m_rd_klub.GetCheck() == 1)
				{
					NadiIme(RClanarine->m_IDclana);
					m_edit_pom.GetWindowTextW(ime);
				}
				CTime dat = RClanarine->m_DatumUplate;
				CString strDat = dat.Format(_T("%d.%m.%Y"));

				nIndex = m_lista.InsertItem(0, _T(""));
				m_lista.SetItemText(nIndex, 1, strDat);
				m_lista.SetItemText(nIndex, 2, RClanarine->m_IznosUplate);
				m_lista.SetItemText(nIndex, 3, RClanarine->m_SvrhaUplate);

				RClanarine->MoveNext();
			}
		}
	}
	else if (m_rd_klub.GetCheck() == 1)
	{
		m_lista.InsertColumn(0, _T("Ime"), LVCFMT_LEFT, 180);
		m_lista.InsertColumn(1, _T("Datum uplate"), LVCFMT_CENTER, 120);
		m_lista.InsertColumn(2, _T("Iznos"), LVCFMT_CENTER, 80);
		m_lista.InsertColumn(3, _T("Svrha"), LVCFMT_LEFT, 200);

		if (m_rd_sve_uplate.GetCheck() == 1)
		{
			RClanarine->m_strSort = _T("DatumUplate DESC");
		}
		else if (m_rd_razdoblje.GetCheck() == 1)
		{
			CTime DateOd, DateDo;
			m_date_od.GetTime(DateOd);
			CString strDateOd = DateOd.Format(_T("%m/%d/%y"));

			m_date_do.GetTime(DateDo);
			CString strDateDo = DateDo.Format(_T("%m/%d/%y"));

			RClanarine->m_strFilter = _T("(DatumUplate between #") + strDateOd + _T("#") + _T(" and #") + strDateDo + _T("#)");
			RClanarine->m_strSort = _T("DatumUplate DESC");
		}
		if (!RClanarine->IsOpen())
			RClanarine->Open();

		if (RClanarine->IsBOF() && RClanarine->IsEOF())
		{			
				MessageBox(_T("U izabranom razdoblju nema zabilježenih uplata"), _T("Obavijest"), MB_ICONINFORMATION | MB_OK);
		}
		else
		{
			while (!RClanarine->IsEOF())
			{
				if (m_rd_klub.GetCheck() == 1)
				{
					NadiIme(RClanarine->m_IDclana);
					m_edit_pom.GetWindowTextW(ime);
				}
				CTime dat = RClanarine->m_DatumUplate;
				CString strDat = dat.Format(_T("%d.%m.%Y"));

				nIndex = m_lista.InsertItem(0, ime);
				m_lista.SetItemText(nIndex, 1, strDat);
				m_lista.SetItemText(nIndex, 2, RClanarine->m_IznosUplate);
				m_lista.SetItemText(nIndex, 3, RClanarine->m_SvrhaUplate);

				RClanarine->MoveNext();
			}
		}
	}
		
		RClanarine->m_strFilter = _T("");
		RClanarine->Close();	
}


long Dialog_prikaz_clanarina::NadiIDclana()
{
	CString ime;
	long IDclana;
	m_combo.GetWindowTextW(ime);
	RClanovi->m_strFilter = _T("ImePrezime = '") + ime + _T("'");
	RClanovi->Open();
	IDclana = RClanovi->m_IDclana;
	RClanovi->Close();

	return IDclana;
}

void Dialog_prikaz_clanarina::NadiIme(long IDclana)
{
	CString strIDclana;
	strIDclana.Format(_T("%ld"), IDclana);
	RClanovi->m_strFilter = (_T("[IDclana] = ") + strIDclana + _T(""));

	if(!RClanovi->IsOpen());
	RClanovi->Open();	
	CString ime = RClanovi->m_ImePrezime;
	RClanovi->Close();
	
	m_edit_pom.SetWindowTextW(ime);
}


void Dialog_prikaz_clanarina::OnBnClickedBtnIspisiPrikaz()
{
	// TODO: Add your control notification handler code here
}



void Dialog_prikaz_clanarina::OnBnClickedBtnZatvoriAplikaciju1()
{
	PostQuitMessage(0);
}


void Dialog_prikaz_clanarina::OnBnClickedBtnPocetna()
{
	DialogClanarine *pPar = (DialogClanarine*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();
}


void Dialog_prikaz_clanarina::OnBnClickedBtnClanovi1()
{
	DialogClanovi* DClanovi;
	DClanovi = new DialogClanovi;

	DialogClanarine *pPar = (DialogClanarine*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();

	DClanovi->DoModal();
}


void Dialog_prikaz_clanarina::OnBnClickedBtnNatjecanja1()
{
	Dialog_Natjecanja* DNatjecanja;
	DNatjecanja = new Dialog_Natjecanja;

	DialogClanarine *pPar = (DialogClanarine*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();

	DNatjecanja->DoModal();
}
