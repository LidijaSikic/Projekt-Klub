﻿// Dialog_Prikaz_Natjecanja.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Klub.h"
#include "DialogClanovi.h"
#include "DialogClanarine.h"
#include "Dialog_Natjecanja.h"
#include "Dialog_Prikaz_Natjecanja.h"



// Dialog_Prikaz_Natjecanja dialog

IMPLEMENT_DYNAMIC(Dialog_Prikaz_Natjecanja, CDialog)

Dialog_Prikaz_Natjecanja::Dialog_Prikaz_Natjecanja(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_PRIKAZ_NATJECANJA, pParent)
	, m_rb_stanje(0)
{	
}

Dialog_Prikaz_Natjecanja::~Dialog_Prikaz_Natjecanja()
{
}

void Dialog_Prikaz_Natjecanja::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RD_NATJECATELJ, m_rd_natjecatelj);
	DDX_Control(pDX, IDC_RD_KLUB, m_rd_klub);
	DDX_Control(pDX, IDC_RD_NATJECANJE, m_rd_natjecanje);
	DDX_Radio(pDX, IDC_RD_NATJECATELJ, m_rb_stanje);
	DDX_Control(pDX, IDC_COMBO_NATJECATELJ, m_combo_natjecatelj);
	DDX_Control(pDX, IDC_DATE_OD, m_date_od);
	DDX_Control(pDX, IDC_DATE_DO, m_date_do);
	DDX_Control(pDX, IDC_COMBO_NATJECANJE, m_combo_natjecanje);
	DDX_Control(pDX, IDC_BTN_PRIKAZI, m_btn_prikazi);
	DDX_Control(pDX, IDC_LISTA, m_Lista);
	DDX_Control(pDX, IDC_EDIT_POM, m_edit_pom);
	DDX_Control(pDX, IDC_STATIC_POM, m_static_pom);
	DDX_Control(pDX, IDC_COMBO_POM, m_combo_pom);	
}


BEGIN_MESSAGE_MAP(Dialog_Prikaz_Natjecanja, CDialog)
	ON_BN_CLICKED(IDC_RD_NATJECANJE, &Dialog_Prikaz_Natjecanja::OnBnClickedRdNatjecanje)
	ON_BN_CLICKED(IDC_BTN_PRIKAZI, &Dialog_Prikaz_Natjecanja::OnBnClickedBtnPrikazi)	
	ON_BN_CLICKED(IDC_BTN_POCETNA5, &Dialog_Prikaz_Natjecanja::OnBnClickedBtnPocetna5)
	ON_BN_CLICKED(IDC_BTN_ZATVORI5, &Dialog_Prikaz_Natjecanja::OnBnClickedBtnZatvori5)
	ON_BN_CLICKED(IDC_BTN_CLANOVI5, &Dialog_Prikaz_Natjecanja::OnBnClickedBtnClanovi5)
	ON_BN_CLICKED(IDC_BTN_CLANARINE5, &Dialog_Prikaz_Natjecanja::OnBnClickedBtnClanarine5)
	ON_BN_CLICKED(IDC_RD_NATJECATELJ, &Dialog_Prikaz_Natjecanja::OnBnClickedRdNatjecatelj)
	ON_BN_CLICKED(IDC_RD_KLUB, &Dialog_Prikaz_Natjecanja::OnBnClickedRdKlub)
END_MESSAGE_MAP()


// Dialog_Prikaz_Natjecanja message handlers


BOOL Dialog_Prikaz_Natjecanja::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, FALSE);

	RClanovi = new CClanoviSet;
	RNatjecanja = new CNatjecanjaSet;
	RRezultati = new CRezultatiSet;

	m_date_od.SetFormat(_T("dd.MM.yyyy"));
	m_date_do.SetFormat(_T("dd.MM.yyyy"));

	m_date_od.EnableWindow(FALSE);
	m_date_do.EnableWindow(FALSE);
	m_combo_natjecanje.EnableWindow(FALSE);

	CString Ime;
	
	if (!RClanovi->IsOpen())
		RClanovi->Open();
	while (!RClanovi->IsEOF()) {
		Ime = RClanovi->m_ImePrezime;
		m_combo_natjecatelj.AddString(Ime);
		RClanovi->MoveNext();
	}
	RClanovi->Close();
	m_combo_natjecatelj.SetCurSel(0);

	CString Naziv;

	if (!RNatjecanja->IsOpen())
		RNatjecanja->Open();
	while (!RNatjecanja->IsEOF()) {
		Naziv = RNatjecanja->m_NazivNatjecanja;
		CTime datum = RNatjecanja->m_DatumNatjecanja;
		CString strDatum = datum.Format("%d.%m.%Y");

		m_combo_natjecanje.AddString(Naziv + _T(",  ") + strDatum);
		RNatjecanja->MoveNext();
	}
	RNatjecanja->Close();
	m_combo_natjecanje.SetCurSel(-1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



void Dialog_Prikaz_Natjecanja::OnBnClickedBtnPrikazi()
{
	m_Lista.DeleteAllItems();
	while (m_Lista.DeleteColumn(0));
	m_combo_pom.ResetContent();
	m_edit_pom.SetWindowTextW(_T(""));

	int nIndex;
	CString podaci, ime, naziv, datum, kategorija, rezultat;
	
	if (m_rd_natjecatelj.GetCheck() == 1)
	{
		int nSel = m_combo_natjecatelj.GetCurSel();
		if (nSel != LB_ERR)
		{
			m_combo_natjecatelj.GetLBText(nSel, ime);
		}
		m_Lista.InsertColumn(0, ime, LVCFMT_LEFT, 150);          
		m_Lista.InsertColumn(1, _T("Datum natjecanja"), LVCFMT_CENTER, 140);
		m_Lista.InsertColumn(2, _T("Naziv natjecanja"), LVCFMT_CENTER, 220);
		m_Lista.InsertColumn(3, _T("Kategorija"), LVCFMT_LEFT, 150);
		m_Lista.InsertColumn(4, _T("Rezultat"), LVCFMT_CENTER, 100);		

		CString strIDclana;
		strIDclana.Format(_T("%ld"), NadiIDnatjecatelja());
		
		RRezultati->m_strFilter = _T("IDclana = ") + strIDclana + _T("");		

			if (!RRezultati->IsOpen())
				RRezultati->Open();

			if (RRezultati->IsBOF() && RRezultati->IsEOF())
			{
				MessageBox(_T("Član ")+ ime + _T(" nema zabilježenih rezultata"), _T("Obavijest"), MB_ICONINFORMATION | MB_OK);
			}
			else
			{
				while (!RRezultati->IsEOF())
				{
					NadiNatjecanje(RRezultati->m_IDnatjecanja);
					m_edit_pom.GetWindowTextW(podaci);
					naziv = podaci.Left(podaci.Find(_T(',')));
					
					datum= podaci.Mid(podaci.ReverseFind(_T(',')) + 3);

					nIndex = m_Lista.InsertItem(0, _T(""));
					m_Lista.SetItemText(nIndex, 1, datum);
					m_Lista.SetItemText(nIndex, 2, naziv);
					m_Lista.SetItemText(nIndex, 3, RRezultati->m_Kategorija);
					m_Lista.SetItemText(nIndex, 4, RRezultati->m_Rezultat);

					RRezultati->MoveNext();
				}
			}
			RRezultati->m_strFilter = _T("");
			RRezultati->Close();
	}
	else if (m_rd_klub.GetCheck() == 1)
	{
		m_Lista.InsertColumn(0, _T("Datum natjecanja"), LVCFMT_CENTER, 140);
		m_Lista.InsertColumn(1, _T("Naziv natjecanja"), LVCFMT_LEFT, 220);
		m_Lista.InsertColumn(2, _T("Natjecatelj"), LVCFMT_CENTER, 150);
		m_Lista.InsertColumn(3, _T("Kategorija"), LVCFMT_LEFT, 150);
		m_Lista.InsertColumn(4, _T("Rezultat"), LVCFMT_CENTER, 100);

		CTime DateOd, DateDo;
		m_date_od.GetTime(DateOd);
		CString strDateOd = DateOd.Format(_T("%m/%d/%y"));

		m_date_do.GetTime(DateDo);
		CString strDateDo = DateDo.Format(_T("%m/%d/%y"));

		RNatjecanja->m_strFilter =_T("DatumNatjecanja between #") + strDateOd + _T("#") + _T(" and #") + strDateDo + _T("#");
		RNatjecanja->m_strSort= _T("DatumNatjecanja DESC");

		if (!RNatjecanja->IsOpen())
			RNatjecanja->Open();

		if (RNatjecanja->IsBOF() && RNatjecanja->IsEOF())
		{
			MessageBox(_T("U zadanom razdoblju nije bilo natjecanja"), _T("Obavijest"), MB_ICONINFORMATION | MB_OK);	
		}
		else
		{
			while (!RNatjecanja->IsEOF())
			{
				m_combo_pom.ResetContent();
				CTime dat = RNatjecanja->m_DatumNatjecanja;
				datum = dat.Format(_T("%d.%m.%Y"));

				naziv = RNatjecanja->m_NazivNatjecanja;
				
				m_edit_pom.SetWindowTextW(naziv);

				NadiRezultate(RNatjecanja->m_IDnatjecanja);

				if (m_combo_pom.GetCount() == 0)
				{
					nIndex = m_Lista.InsertItem(0, datum);
					m_Lista.SetItemText(nIndex, 1, naziv);
					m_Lista.SetItemText(nIndex, 2, _T(""));
					m_Lista.SetItemText(nIndex, 3, _T(""));
					m_Lista.SetItemText(nIndex, 4, _T(""));									
				}
				else 
				{
					for (int n = 0; n<m_combo_pom.GetCount(); n++)
					{
						if (n == (m_combo_pom.GetCount() - 1))
						{
							m_combo_pom.GetLBText(n, podaci);				
							ime = podaci.Left(podaci.Find(_T(",")));
							kategorija = podaci.Mid(podaci.Find(_T(',')) + 1, (podaci.ReverseFind(_T(',')) - 1 - (podaci.Find(_T(',')) + 1)));
							rezultat = podaci.Mid(podaci.ReverseFind(_T(',')) + 1);

							nIndex = m_Lista.InsertItem(0, datum);
							m_Lista.SetItemText(nIndex, 1, naziv);
							m_Lista.SetItemText(nIndex, 2, ime);
							m_Lista.SetItemText(nIndex, 3, kategorija);
							m_Lista.SetItemText(nIndex, 4, rezultat);
						}
						else
						{
							m_combo_pom.GetLBText(n, podaci);
							ime = podaci.Left(podaci.Find(_T(",")));
							kategorija = podaci.Mid(podaci.Find(_T(',')) + 1, (podaci.ReverseFind(_T(',')) - 1 - (podaci.Find(_T(',')) + 1)));
							rezultat = podaci.Mid(podaci.ReverseFind(_T(',')) + 1);

							nIndex = m_Lista.InsertItem(0, _T(""));
							m_Lista.SetItemText(nIndex, 1, _T(""));
							m_Lista.SetItemText(nIndex, 2, ime);
							m_Lista.SetItemText(nIndex, 3, kategorija);
							m_Lista.SetItemText(nIndex, 4, rezultat);
						}
					}					
				}		
				RNatjecanja->MoveNext();
			}			
		}
		RNatjecanja->m_strFilter = _T("");
		RNatjecanja->Close();
	}
	else if (m_rd_natjecanje.GetCheck() == 1)
	{
		int nSel = m_combo_natjecanje.GetCurSel();
		if (nSel != LB_ERR)
		{
			m_combo_natjecanje.GetLBText(nSel, naziv);
		}		
		m_Lista.InsertColumn(0, naziv, LVCFMT_LEFT, 320);
		m_Lista.InsertColumn(1, _T("Natjecatelj"), LVCFMT_LEFT, 150);
		m_Lista.InsertColumn(2, _T("Kategorija"), LVCFMT_LEFT, 150);
		m_Lista.InsertColumn(3, _T("Rezultat"), LVCFMT_CENTER, 100);

		naziv.Delete(naziv.Find(_T(",")), 16);
		CString strIDnatjecanja;
		strIDnatjecanja.Format(_T("%ld"), NadiIDnatjecanja());

		RRezultati->m_strFilter = _T("IDnatjecanja = ") + strIDnatjecanja + _T("");

		if (!RRezultati->IsOpen())
			RRezultati->Open();

		if (RRezultati->IsBOF() && RRezultati->IsEOF())
		{
			MessageBox(_T("Za natjecanje ")+ naziv + _T(" nema upisanih rezultata "), _T("Obavijest"), MB_ICONINFORMATION | MB_OK);
		}
		else
		{
			while (!RRezultati->IsEOF())
			{
				NadiIme(RRezultati->m_IDclana);
				m_static_pom.GetWindowTextW(ime);

				nIndex = m_Lista.InsertItem(0, _T(""));
				m_Lista.SetItemText(nIndex, 1, ime);
				m_Lista.SetItemText(nIndex, 2, RRezultati->m_Kategorija);
				m_Lista.SetItemText(nIndex, 3, RRezultati->m_Rezultat);

				RRezultati->MoveNext();
			}			
		}
		RRezultati->m_strFilter = _T("");
		RRezultati->Close();
	}
}


void Dialog_Prikaz_Natjecanja::NadiIme(long IDclana)
{
	CString strIDclana;
	strIDclana.Format(_T("%ld"), IDclana);
	RClanovi->m_strFilter = (_T("[IDclana] = ") + strIDclana + _T(""));
	if(!RClanovi->IsOpen())
	RClanovi->Open();

	CString ime = RClanovi->m_ImePrezime;
	RClanovi->m_strFilter = _T("");
	RClanovi->Close();

	m_static_pom.SetWindowTextW(ime);
}

void Dialog_Prikaz_Natjecanja::NadiNatjecanje(long IDnatjecanja)
{
	CString strIDnatjecanja;
	strIDnatjecanja.Format(_T("%ld"), IDnatjecanja);
	RNatjecanja->m_strFilter = (_T("[IDnatjecanja] = ") + strIDnatjecanja + _T(""));
	if(!RNatjecanja->IsOpen())
	RNatjecanja->Open();

	CString naziv = RNatjecanja->m_NazivNatjecanja;
	CTime datum = RNatjecanja->m_DatumNatjecanja;

	RNatjecanja->m_strFilter = _T("");
	RNatjecanja->Close();
	CString natjecanje = naziv + _T(",  ") + datum.Format(_T("%d.%m.%Y"));

	m_edit_pom.SetWindowTextW(natjecanje);
}

long Dialog_Prikaz_Natjecanja::NadiIDnatjecanja()
{
	CString naziv;
	long IDnatjecanja;

	int nSel = m_combo_natjecanje.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_natjecanje.GetLBText(nSel, naziv);
	}
	naziv.Delete(naziv.Find(_T(",")), 16);

	RNatjecanja->m_strFilter = _T("NazivNatjecanja = '") + naziv + _T("'");
	if(!RNatjecanja->IsOpen())
	RNatjecanja->Open();

	IDnatjecanja = RNatjecanja->m_IDnatjecanja;
	RNatjecanja->m_strFilter = _T("");
	RNatjecanja->Close();

	return IDnatjecanja;
}


long Dialog_Prikaz_Natjecanja::NadiIDnatjecatelja()
{
	CString ime;
	long IDclana;

	int nSel = m_combo_natjecatelj.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_natjecatelj.GetLBText(nSel, ime);
	}
	RClanovi->m_strFilter = _T("ImePrezime = '") + ime + _T("'");
	if(!RClanovi->IsOpen())
	RClanovi->Open();
	IDclana = RClanovi->m_IDclana;
	RClanovi->m_strFilter = _T("");
	RClanovi->Close();

	return IDclana;
}

void Dialog_Prikaz_Natjecanja::NadiRezultate(long IDnatjecanja)
{
	CString ime, kategorija, rezultat;
	CString strIDnatjecanja;
	int brojac = 0;
	long natjecanjeID= IDnatjecanja;
	strIDnatjecanja.Format(_T("%ld"), natjecanjeID);

	RRezultati->m_strFilter = _T("IDnatjecanja = ") + strIDnatjecanja + _T("");
	RRezultati->m_strSort = _T("IDrezultata ASC");
	if (!RRezultati->IsOpen())
		RRezultati->Open();
	
		while (!RRezultati->IsEOF())
		{		
			brojac += 1;

			NadiIme(RRezultati->m_IDclana);
			m_static_pom.GetWindowTextW(ime);

			kategorija = RRezultati->m_Kategorija;
			rezultat = RRezultati->m_Rezultat;

			m_combo_pom.AddString(ime + _T(" , ") + kategorija + _T(" , ") + rezultat);
			RRezultati->MoveNext();
		}
	RRezultati->m_strFilter = _T("");
	RRezultati->Close();
}


void Dialog_Prikaz_Natjecanja::OnBnClickedBtnPocetna5()
{
	Dialog_Natjecanja *pPar = (Dialog_Natjecanja*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();
}


void Dialog_Prikaz_Natjecanja::OnBnClickedBtnZatvori5()
{
	PostQuitMessage(0);
}


void Dialog_Prikaz_Natjecanja::OnBnClickedBtnClanovi5()
{
	DialogClanovi* DClanovi;
	DClanovi = new DialogClanovi;

	Dialog_Natjecanja *pPar = (Dialog_Natjecanja*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();

	DClanovi->DoModal();
}


void Dialog_Prikaz_Natjecanja::OnBnClickedBtnClanarine5()
{
	DialogClanarine* DClanarine;
	DClanarine = new DialogClanarine;

	Dialog_Natjecanja *pPar = (Dialog_Natjecanja*)GetParent();
	pPar->EndDialog(IDOK);
	OnCancel();

	DClanarine->DoModal();
}


void Dialog_Prikaz_Natjecanja::OnBnClickedRdNatjecatelj()
{
	m_combo_natjecatelj.SetCurSel(0);
	m_combo_natjecatelj.EnableWindow(TRUE);
	m_date_od.EnableWindow(FALSE);
	m_date_do.EnableWindow(FALSE);
	m_combo_natjecanje.EnableWindow(FALSE);
}


void Dialog_Prikaz_Natjecanja::OnBnClickedRdKlub()
{
	m_combo_natjecatelj.EnableWindow(FALSE);
	m_date_od.EnableWindow(TRUE);
	m_date_do.EnableWindow(TRUE);
	m_combo_natjecanje.EnableWindow(FALSE);
}

void Dialog_Prikaz_Natjecanja::OnBnClickedRdNatjecanje()
{
	m_combo_natjecanje.SetCurSel(0);
	m_combo_natjecatelj.EnableWindow(FALSE);
	m_date_od.EnableWindow(FALSE);
	m_date_do.EnableWindow(FALSE);
	m_combo_natjecanje.EnableWindow(TRUE);
}
