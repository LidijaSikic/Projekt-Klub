// Dialog_Natjecanja.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Klub.h"
#include "DialogClanovi.h"
#include "DialogClanarine.h"
#include "Dialog_Natjecanja.h"



// Dialog_Natjecanja dialog

IMPLEMENT_DYNAMIC(Dialog_Natjecanja, CDialog)

Dialog_Natjecanja::Dialog_Natjecanja(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_NATJECANJA, pParent)
	, m_rb_natjecanja_val(FALSE)
	, m_rb_rezultat_val(FALSE)
	, m_rb_promjena_rez_za_natjecanje_val(FALSE)
{
	RClanovi = new CClanoviSet;
	RNatjecanja = new CNatjecanjaSet;
	RRezultati = new CRezultatiSet;
}

Dialog_Natjecanja::~Dialog_Natjecanja()
{
}

void Dialog_Natjecanja::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAZIV_NATJECANJA, m_edit_naziv_natjecanja);
	DDX_Control(pDX, IDC_DAT_ODRZAVANJA, m_dat_odrzavanja);
	DDX_Control(pDX, IDC_EDIT_KOEFICIJENT, m_edit_koeficijent);
	DDX_Control(pDX, IDC_COMBO_LISTA_NATJECANJA, m_combo_lista_natjecanja);
	DDX_Control(pDX, IDC_RD_UNOS_NATJECANJA, m_rd_unos_natjecanja);
	DDX_Control(pDX, IDC_RD_PROMJENA_UNOSA, m_rd_promjena_unosa);
	DDX_Radio(pDX, IDC_RD_UNOS_NATJECANJA, m_rb_natjecanja_val);
	DDX_Control(pDX, IDC_COMBO_NATJECANJE_REZ, m_combo_natjecanje_rez);
	DDX_Control(pDX, IDC_COMBO_NATJECATELJ, m_combo_natjecatelj);
	DDX_Control(pDX, IDC_EDIT_KATEGORIJA, m_edit_kategorija);
	DDX_Control(pDX, IDC_RD_UNOS_REZULTATA, m_rd_unos_rezultata);
	DDX_Radio(pDX, IDC_RD_UNOS_REZULTATA, m_rb_rezultat_val);
	DDX_Control(pDX, IDC_RD_PROMJENA_REZULTATA, m_rd_promjena_rezultata);
	DDX_Control(pDX, IDC_BTN_SPREMI_NATJ, m_btn_spremi_natjecanja);
	DDX_Control(pDX, IDC_BTN_ODUSTANI_NATJ, m_btn_odustani_natjecanja);
	DDX_Control(pDX, IDC_BTN_SPREMI_REZ, m_btn_spremi_rez);
	DDX_Control(pDX, IDC_BTN_ODUSTANI_REZ, m_btn_odustani_rez);
	DDX_Control(pDX, IDC_BTN_PRIKAZI, m_btn_prikazi);
	DDX_Control(pDX, IDC_RD_PROMJENA_REZ_ZA_NATJECANJE, m_rd_promjena_unosa_rez_za_natjecanje);
	DDX_Radio(pDX, IDC_RD_PROMJENA_REZ_ZA_NATJECANJE, m_rb_promjena_rez_za_natjecanje_val);
	DDX_Control(pDX, IDC_RD_PROMJENA_UNOSA_REZ_ZA_NATJECATELJA, m_rd_promjena_unosa_rez_za_natjecatelja);
	DDX_Control(pDX, IDC_COMBO_REZULRAT, m_combo_rezultat);
	DDX_Control(pDX, IDC_EDIT_POM, m_edit_pom);
	DDX_Control(pDX, IDC_LIST_PODACI, m_list_podaci);
	DDX_Control(pDX, IDC_COMBO_REZULTAT, m_combo_rezultat);
}


BEGIN_MESSAGE_MAP(Dialog_Natjecanja, CDialog)
	ON_BN_CLICKED(IDC_RD_UNOS_NATJECANJA, &Dialog_Natjecanja::OnBnClickedRdUnosNatjecanja)
	ON_BN_CLICKED(IDC_RD_PROMJENA_UNOSA, &Dialog_Natjecanja::OnBnClickedRdPromjenaUnosa)	
	ON_BN_CLICKED(IDC_RD_UNOS_REZULTATA, &Dialog_Natjecanja::OnBnClickedRdUnosRezultata)
	ON_BN_CLICKED(IDC_RD_PROMJENA_REZULTATA, &Dialog_Natjecanja::OnBnClickedRdPromjenaRezultata)
	ON_BN_CLICKED(IDC_BTN_SPREMI_NATJ, &Dialog_Natjecanja::OnBnClickedBtnSpremiNatj)
	ON_BN_CLICKED(IDC_BTN_ODUSTANI_NATJ, &Dialog_Natjecanja::OnBnClickedBtnOdustaniNatj)
	ON_BN_CLICKED(IDC_BTN_SPREMI_REZ, &Dialog_Natjecanja::OnBnClickedBtnSpremiRez)
	ON_BN_CLICKED(IDC_BTN_ODUSTANI_REZ, &Dialog_Natjecanja::OnBnClickedBtnOdustaniRez)	
	ON_BN_CLICKED(IDC_RD_NATJECANJA, &Dialog_Natjecanja::OnBnClickedRdNatjecanja)		
	ON_CBN_SELCHANGE(IDC_COMBO_LISTA_NATJECANJA, &Dialog_Natjecanja::OnCbnSelchangeComboListaNatjecanja)
	ON_BN_CLICKED(IDC_RD_PROMJENA_REZ_ZA_NATJECANJE, &Dialog_Natjecanja::OnBnClickedRdPromjenaRezZaNatjecanje)
	ON_BN_CLICKED(IDC_RD_PROMJENA_UNOSA_REZ_ZA_NATJECATELJA, &Dialog_Natjecanja::OnBnClickedRdPromjenaUnosaRezZaNatjecatelja)
	ON_CBN_SELCHANGE(IDC_COMBO_NATJECATELJ, &Dialog_Natjecanja::OnCbnSelchangeComboNatjecatelj)
	ON_CBN_SELCHANGE(IDC_COMBO_NATJECANJE_REZ, &Dialog_Natjecanja::OnCbnSelchangeComboNatjecanjeRez)
	ON_LBN_SELCHANGE(IDC_LIST_PODACI, &Dialog_Natjecanja::OnLbnSelchangeListPodaci)
	ON_BN_CLICKED(IDC_BTN_PRIKAZI, &Dialog_Natjecanja::OnBnClickedBtnPrikazi)
	ON_BN_CLICKED(IDC_BTN_ZATVORI3, &Dialog_Natjecanja::OnBnClickedBtnZatvori3)
	ON_BN_CLICKED(IDC_BTN_POCETNA3, &Dialog_Natjecanja::OnBnClickedBtnPocetna3)
	ON_BN_CLICKED(IDC_BTN_CLANOVI3, &Dialog_Natjecanja::OnBnClickedBtnClanovi3)
	ON_BN_CLICKED(IDC_BTN_CLANARINE3, &Dialog_Natjecanja::OnBnClickedBtnClanarine3)
END_MESSAGE_MAP()


// Dialog_Natjecanja message handlers


BOOL Dialog_Natjecanja::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, FALSE);

	m_dat_odrzavanja.SetFormat(_T("dd.MM.yyyy"));
	
	m_combo_lista_natjecanja.ShowWindow(FALSE);
	UcitajNatjecanje_rez();
	UcitajNatjecatelje_rez();
	m_combo_rezultat.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////// NATJECANJA  ///////////////////////


void Dialog_Natjecanja::OnBnClickedRdUnosNatjecanja()
{
	OcistiNatjecanja();
	m_combo_lista_natjecanja.ShowWindow(FALSE);
}

void Dialog_Natjecanja::OnBnClickedRdPromjenaUnosa()
{
	OcistiNatjecanja();
	m_combo_lista_natjecanja.ShowWindow(TRUE);

	CString natjecanje;
	if (!RNatjecanja->IsOpen())
		RNatjecanja->Open();

	while (!RNatjecanja->IsEOF()) {
		CString naziv = RNatjecanja->m_NazivNatjecanja;

		 CTime datum = RNatjecanja->m_DatumNatjecanja;
		 CString strDatum = datum.Format("%d.%m.%Y");

		m_combo_lista_natjecanja.AddString(naziv + _T(",  ") + strDatum);
		RNatjecanja->MoveNext();
	}	
	RNatjecanja->Close();
	m_combo_lista_natjecanja.SetCurSel(0);
}

void Dialog_Natjecanja::OnBnClickedBtnSpremiNatj()
{
	CString text;
	int nNoviID = 0;
	m_edit_naziv_natjecanja.GetWindowTextW(text);
	if (text.IsEmpty()) {
		MessageBox(_T("Nije unesen naziv natjecanja"), _T("Greška"),
			MB_ICONERROR | MB_OK);
		m_edit_naziv_natjecanja.SetFocus();
		return;
	}

	else if (m_rd_unos_natjecanja.GetCheck() == 1)
	{
		SpremiNatjecanje();
		OcistiNatjecanja();
	}
	else if (m_rd_promjena_unosa.GetCheck() == 1)
	{
		PromijeniNatjecanje();
		OcistiNatjecanja();
		m_rd_unos_natjecanja.SetCheck(1);
		m_rd_promjena_unosa.SetCheck(0);
	}	
}


void Dialog_Natjecanja::OnBnClickedBtnOdustaniNatj()
{
	OcistiNatjecanja();
	m_rd_unos_natjecanja.SetCheck(TRUE);
	m_rd_promjena_unosa.SetCheck(FALSE);
}

void Dialog_Natjecanja::OnBnClickedRdNatjecanja()
{
	m_rd_unos_natjecanja.SetCheck(TRUE);
}


void Dialog_Natjecanja::OcistiNatjecanja()
{
	m_edit_naziv_natjecanja.SetWindowTextW(_T(""));
	m_combo_lista_natjecanja.ResetContent();
	m_edit_koeficijent.SetWindowTextW(_T(""));

	CTime date;
	date = date.GetCurrentTime();
	m_dat_odrzavanja.SetTime(&date);
}

void Dialog_Natjecanja::SpremiNatjecanje()
{
	CString text;
	int nNoviID = 0;
	m_edit_naziv_natjecanja.GetWindowTextW(text);
	if (text.IsEmpty()) {
		MessageBox(_T("Nije unesen naziv natjecanja"), _T("Greška"),
			MB_ICONERROR | MB_OK);
		m_edit_naziv_natjecanja.SetFocus();
		return;
	}
	else {
		long noviID;
		if (!RNatjecanja->IsOpen())
		RNatjecanja->Open();
	
		noviID = RNatjecanja->MaxID() + 1;
		RNatjecanja->AddNew();

		CString naziv;
		m_edit_naziv_natjecanja.GetWindowText(naziv);

		CTime datum;
		m_dat_odrzavanja.GetTime(datum);

		CString Koef;
		m_edit_koeficijent.GetWindowTextW(Koef);
		double koef = _tstof(Koef);

		RNatjecanja->m_IDnatjecanja = noviID;
		RNatjecanja->m_NazivNatjecanja = naziv;
		RNatjecanja->m_DatumNatjecanja = datum;
		RNatjecanja->m_Koeficijent = koef;

		if (!RNatjecanja->Update())
			MessageBox(_T("Unos novog natjecanja nije uspio"), _T("Greška"),
				MB_ICONERROR | MB_OK);
		else
			MessageBox(_T("Novo natjecanje je uspješno uneseno u bazu"), _T("Obavijest"),
				MB_OK);

		RNatjecanja->Requery();
		RNatjecanja->Close();
	}
}


void Dialog_Natjecanja::PromijeniNatjecanje()
{
	CString text;
	if(!RNatjecanja->IsOpen())
	RNatjecanja->Open();
	RNatjecanja->Edit();

	CString editNaziv;
	m_edit_naziv_natjecanja.GetWindowTextW(editNaziv);

	CTime datum;
	m_dat_odrzavanja.GetTime(datum);

	CString Koef;
	m_edit_koeficijent.GetWindowText(Koef);
	double koef = _tstof(Koef);

	RNatjecanja->m_NazivNatjecanja = editNaziv;
	RNatjecanja->m_DatumNatjecanja = datum;
	RNatjecanja->m_Koeficijent = koef;

	if (!RNatjecanja->Update()) {
		MessageBox(_T("Promjene nisu uspješno unesene"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
	}
	else {
		MessageBox(_T("Promjene su uspješno unesene"), _T("Obavijest"), MB_OK);
	}
	RNatjecanja->Requery();
	RNatjecanja->m_strFilter = _T("");
	RNatjecanja->Close();
	m_combo_lista_natjecanja.ShowWindow(FALSE);
}


void Dialog_Natjecanja::OnCbnSelchangeComboListaNatjecanja()
{
	CString naziv;

	int nSel = m_combo_lista_natjecanja.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_lista_natjecanja.GetLBText(nSel, naziv);
	}

	naziv.Delete(naziv.Find(_T(",")), 16);
	m_edit_naziv_natjecanja.SetWindowTextW(naziv);

	RNatjecanja->m_strFilter = _T("[NazivNatjecanja] = '") + naziv + _T("'");
	
	if (!RNatjecanja->IsOpen())
	RNatjecanja->Open();

	CTime datum = RNatjecanja->m_DatumNatjecanja;
	m_dat_odrzavanja.SetTime(&datum);

	double koef = RNatjecanja->m_Koeficijent;
	koef = RNatjecanja->m_Koeficijent;
	CString strKoef;
	strKoef.Format(_T("%g"), koef);
	m_edit_koeficijent.SetWindowTextW(strKoef);

	RNatjecanja->m_strFilter = _T("");
	RNatjecanja->Close();
}


//////////////// R E Z U L T A T I  ///////////////////////

void Dialog_Natjecanja::OnBnClickedRdUnosRezultata()
{
	m_combo_natjecanje_rez.EnableWindow(TRUE);
	m_combo_natjecatelj.EnableWindow(TRUE);
	m_rd_promjena_unosa_rez_za_natjecanje.ShowWindow(FALSE);
	m_rd_promjena_unosa_rez_za_natjecatelja.ShowWindow(FALSE);

	OcistiRezultate();
	UcitajNatjecanje_rez();
	UcitajNatjecatelje_rez();	
}


void Dialog_Natjecanja::OnBnClickedRdPromjenaRezultata()
{
	m_rd_promjena_unosa_rez_za_natjecanje.ShowWindow(TRUE);
	m_rd_promjena_unosa_rez_za_natjecanje.SetCheck(TRUE);
	m_rd_promjena_unosa_rez_za_natjecatelja.ShowWindow(TRUE);
	m_rd_promjena_unosa_rez_za_natjecatelja.SetCheck(FALSE);

	OcistiRezultate();
	m_list_podaci.ResetContent();
	m_combo_natjecatelj.EnableWindow(FALSE);
}


void Dialog_Natjecanja::OnBnClickedBtnSpremiRez()
{
	if (m_rd_unos_rezultata.GetCheck() == 1)
	{
		SpremiRez();
		OcistiRezultate();
	}
	else if (m_rd_promjena_rezultata.GetCheck() == 1)
	{
		PromijeniRez();
		OcistiRezultate();
		m_combo_natjecatelj.EnableWindow(TRUE);
		m_combo_natjecanje_rez.EnableWindow(TRUE);
		m_rd_unos_rezultata.SetCheck(1);
		m_rd_promjena_rezultata.SetCheck(0);
		m_rd_promjena_unosa_rez_za_natjecanje.ShowWindow(FALSE);
		m_rd_promjena_unosa_rez_za_natjecatelja.ShowWindow(FALSE);
	}
}


void Dialog_Natjecanja::OnBnClickedBtnOdustaniRez()
{
	OcistiRezultate();
}
	
		
void Dialog_Natjecanja::OcistiRezultate()
{
	m_combo_natjecanje_rez.SetCurSel(0);
	m_combo_natjecatelj.SetCurSel(0);
	m_combo_rezultat.SetCurSel(0);
	m_edit_kategorija.SetWindowTextW(_T(""));
	m_list_podaci.ResetContent();
}

void Dialog_Natjecanja::OnBnClickedRdPromjenaRezZaNatjecanje()
{
	m_combo_natjecanje_rez.EnableWindow(TRUE);
	m_combo_natjecatelj.EnableWindow(FALSE);
	OcistiRezultate();
}


void Dialog_Natjecanja::OnBnClickedRdPromjenaUnosaRezZaNatjecatelja()
{
	OcistiRezultate();
	m_combo_natjecanje_rez.EnableWindow(FALSE);
	m_combo_natjecatelj.EnableWindow(TRUE);
}


void Dialog_Natjecanja::UcitajNatjecanje_rez()
{
	m_list_podaci.ResetContent();

	if (!RNatjecanja->IsOpen())
		RNatjecanja->Open();

	if ((RNatjecanja->IsBOF()) && (RNatjecanja->IsEOF()))
	{
		MessageBox(_T("U bazi nema niti jedno natjecanje"), _T("Obavijest"),
			MB_OK);
		return;
	}
	else
	{
		while (!RNatjecanja->IsEOF()) {

			CString naziv = RNatjecanja->m_NazivNatjecanja;

			CTime datum = RNatjecanja->m_DatumNatjecanja;
			CString strDatum = datum.Format("%d.%m.%Y");

			m_combo_natjecanje_rez.AddString(naziv + _T(",  ") + strDatum);
			RNatjecanja->MoveNext();
		}
		RNatjecanja->Close();
		m_combo_natjecanje_rez.SetCurSel(0);
	}
}


void Dialog_Natjecanja::UcitajNatjecatelje_rez()
{
	m_list_podaci.ResetContent();

	CString Ime;
	if (!RClanovi->IsOpen())
	RClanovi->Open();

	if ((RClanovi->IsBOF()) && (RClanovi->IsEOF()))
	{
		MessageBox(_T("U bazi nema niti jedan èlan"), _T("Obavijest"),
			MB_OK);
		return;
	}
	while (!RClanovi->IsEOF()) {
		Ime = RClanovi->m_ImePrezime;
		m_combo_natjecatelj.AddString(Ime);
		RClanovi->MoveNext();
	}
	RClanovi->Close();
	m_combo_natjecatelj.SetCurSel(0);
}

void Dialog_Natjecanja::OnCbnSelchangeComboNatjecanjeRez() 
{
	if (m_rd_promjena_rezultata.GetCheck() == 1)
	{
		if (m_rd_promjena_unosa_rez_za_natjecanje.GetCheck() == 1)
		{
			m_list_podaci.ResetContent();
			m_combo_natjecatelj.SetCurSel(-1);
			m_combo_natjecatelj.EnableWindow(FALSE);

			CString strID;
			strID.Format(_T("%ld"), NadiIDnatjecanja());

			RRezultati->m_strFilter= _T("IdNatjecanja = ") + strID + _T("");
			if (!RRezultati->IsOpen())
			RRezultati->Open();

			while (!RRezultati->IsEOF())
			{
				CString strIDrezultata;
				long IDrezultata = RRezultati->m_IDrezultata;
				strIDrezultata.Format(_T("%ld"), IDrezultata);

				long IDclana = RRezultati->m_IDclana;
				NadiIme(IDclana);

				CString ime;				
				m_edit_pom.GetWindowTextW(ime);

				CString kategorija = RRezultati->m_Kategorija;
				CString rezultat = RRezultati->m_Rezultat;
				
				m_list_podaci.AddString(strIDrezultata + _T(":  ") + ime + _T("  /  ") + kategorija + _T("  /  ") + rezultat);

				RRezultati->MoveNext();
			}
			RRezultati->m_strFilter = _T("");
			RRezultati->Close();

			m_list_podaci.SetCurSel(0);
		}	
	}
}

void Dialog_Natjecanja::OnCbnSelchangeComboNatjecatelj()
{
	if (m_rd_promjena_rezultata.GetCheck() == 1)
	{
		if (m_rd_promjena_unosa_rez_za_natjecatelja.GetCheck() == 1)
		{
			m_list_podaci.ResetContent();
			m_combo_natjecanje_rez.SetCurSel(-1);
			m_combo_natjecanje_rez.EnableWindow(FALSE);

			CString strID;
			strID.Format(_T("%ld"), NadiIDnatjecatelja());

			RRezultati->m_strFilter = _T("IdClana = ") + strID + _T("");
			if (!RRezultati->IsOpen())
			RRezultati->Open();

			while (!RRezultati->IsEOF())
			{
				CString strIDrezultata;
				long IDrezultata = RRezultati->m_IDrezultata;
				strIDrezultata.Format(_T("%ld"), IDrezultata);

				long IDnatjecanja = RRezultati->m_IDnatjecanja;
				NadiNatjecanje(IDnatjecanja);

				CString naziv;
				m_edit_pom.GetWindowTextW(naziv);

				CString kategorija = RRezultati->m_Kategorija;
				CString rezultat = RRezultati->m_Rezultat;

				m_list_podaci.AddString(strIDrezultata + _T(":  ") + naziv + _T("  /  ") + kategorija + _T("  /  ") + rezultat);

				RRezultati->MoveNext();
			}
			RRezultati->m_strFilter = _T("");
			RRezultati->Close();
			m_list_podaci.SetCurSel(0);
		}		
	}
}

long Dialog_Natjecanja::NadiIDnatjecanja()
{
	CString naziv;
	long IDnatjecanja;

	int nSel = m_combo_natjecanje_rez.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_natjecanje_rez.GetLBText(nSel, naziv);
	}
	naziv.Delete(naziv.Find(_T(",")), 16);

	RNatjecanja->m_strFilter = _T("NazivNatjecanja = '") + naziv + _T("'");
	if (!RNatjecanja->IsOpen())
	RNatjecanja->Open();
	IDnatjecanja = RNatjecanja->m_IDnatjecanja;
	RNatjecanja->m_strFilter = _T("");
	RNatjecanja->Close();

	return IDnatjecanja;
}


long Dialog_Natjecanja::NadiIDnatjecatelja()
{
	CString ime;
	long IDclana;

	int nSel = m_combo_natjecatelj.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_natjecatelj.GetLBText(nSel, ime);
	}
	RClanovi->m_strFilter = _T("ImePrezime = '") + ime + _T("'");
	if (!RClanovi->IsOpen())
	RClanovi->Open();
	IDclana = RClanovi->m_IDclana;
	RClanovi->m_strFilter = _T("");
	RClanovi->Close();

	return IDclana;
}

void Dialog_Natjecanja::NadiIme(long IDclana)
{
	CString strIDclana;
	strIDclana.Format(_T("%ld"), IDclana);
	RClanovi->m_strFilter = (_T("[IDclana] = ") + strIDclana + _T(""));
	if (!RClanovi->IsOpen())
	RClanovi->Open();

	CString ime = RClanovi->m_ImePrezime;
	RClanovi->m_strFilter = _T("");
	RClanovi->Close();
	
	m_edit_pom.SetWindowTextW(ime);
}

void Dialog_Natjecanja::NadiNatjecanje(long IDnatjecanja)
{
	CString strIDnatjecanja;
		strIDnatjecanja.Format(_T("%ld"), IDnatjecanja);
		RNatjecanja->m_strFilter = (_T("[IDnatjecanja] = ") + strIDnatjecanja + _T(""));
		if (!RNatjecanja->IsOpen())
		RNatjecanja->Open();
	
		CString naziv = RNatjecanja->m_NazivNatjecanja;
		CTime datum = RNatjecanja->m_DatumNatjecanja;
		RNatjecanja->m_strFilter = _T("");
		RNatjecanja->Close();
		CString natjecanje = naziv + _T(",  ") + datum.Format("%d.%m.%Y");
		
		m_edit_pom.SetWindowTextW(natjecanje);
}

void Dialog_Natjecanja::SpremiRez()
{
	CString naziv;
	int nSel= m_combo_natjecanje_rez.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_natjecanje_rez.GetLBText(nSel, naziv);
	}
	naziv.Delete(naziv.Find(_T(",")), 16);

	RNatjecanja->m_strFilter = _T("[NazivNatjecanja] = '") + naziv + _T("'");
	if (!RNatjecanja->IsOpen())
	RNatjecanja->Open();
	long IDnatjecanje = RNatjecanja->m_IDnatjecanja;
	RNatjecanja->m_strFilter = _T("");
	RNatjecanja->Close();

	CString ime;
	nSel = m_combo_natjecatelj.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_natjecatelj.GetLBText(nSel, ime);
	}
	
	RClanovi->m_strFilter = _T("[ImePrezime] = '") + ime + _T("'");
	if (!RClanovi->IsOpen())
	RClanovi->Open();
	long IDnatjecatelj = RClanovi->m_IDclana;
	RNatjecanja->m_strFilter = _T("");
	RClanovi->Close();

	long noviID;
	RRezultati->Open();
	
	noviID = RRezultati->MaxID() + 1;

	RRezultati->AddNew();

	CString kategorija;
	m_edit_kategorija.GetWindowTextW(kategorija);

	CString rezultat;
	m_combo_rezultat.GetWindowTextW(rezultat);

	RRezultati->m_IDrezultata = noviID;
	RRezultati->m_IDclana = IDnatjecatelj;
	RRezultati->m_IDnatjecanja = IDnatjecanje;
	RRezultati->m_Kategorija = kategorija;
	RRezultati->m_Rezultat = rezultat;

	if (!RRezultati->Update())
		MessageBox(_T("Unos novog rezultata nije uspio"), _T("Greška"), MB_ICONERROR | MB_OK);			
	else
		MessageBox(_T("Novi rezultat je uspješno unesen u bazu"), _T("Obavijest"), MB_OK);
			
	RRezultati->Requery();
	RRezultati->Close();	
}


void Dialog_Natjecanja::PromijeniRez()
{
	if (!RRezultati->IsOpen())
	RRezultati->Open();
	RRezultati->Edit();

	CString kategorija;
	m_edit_kategorija.GetWindowTextW(kategorija);

	CString rezultat;
	int nSel = m_combo_rezultat.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_rezultat.GetLBText(nSel, rezultat);
	}

	RRezultati->m_IDclana = NadiIDnatjecatelja();
	RRezultati->m_IDnatjecanja = NadiIDnatjecanja();
	RRezultati->m_Kategorija = kategorija;
	RRezultati->m_Rezultat = rezultat;

	if (!RRezultati->Update()) {
		MessageBox(_T("Promjene nisu uspješno unesene"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
	}
	else {
		MessageBox(_T("Promjene su uspješno unesene"), _T("Obavijest"), MB_OK);
	}
	RRezultati->m_strFilter = _T("");
	RRezultati->Requery();
	RRezultati->Close();	
}

void Dialog_Natjecanja::OnLbnSelchangeListPodaci()
{
	CString podaci;
	int nSel = m_list_podaci.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_list_podaci.GetText(nSel, podaci);
	}
	CString strIndex = podaci.Left(podaci.Find(_T(":")));
	strIndex.Trim();

	RRezultati->m_strFilter = _T("IDrezultata = ") + strIndex + _T("");
	if (!RRezultati->IsOpen())
		RRezultati->Open();

	CString naziv;
	NadiNatjecanje(RRezultati->m_IDnatjecanja);
	m_edit_pom.GetWindowTextW(naziv);
	if (m_combo_natjecanje_rez.FindStringExact(-1, naziv) == LB_ERR)
		m_combo_natjecanje_rez.SetCurSel(-1);
	else
		m_combo_natjecanje_rez.SetCurSel(m_combo_natjecanje_rez.FindStringExact(-1, naziv));

	CString ime;
	NadiIme(RRezultati->m_IDclana);
	m_edit_pom.GetWindowTextW(ime);
	if (m_combo_natjecatelj.FindStringExact(-1, ime) == LB_ERR)
		m_combo_natjecatelj.SetCurSel(-1);
	else
		m_combo_natjecatelj.SetCurSel(m_combo_natjecatelj.FindStringExact(-1,  ime));

	m_edit_kategorija.SetWindowTextW(RRezultati->m_Kategorija);
	CString rez = RRezultati->m_Rezultat;
	if(m_combo_rezultat.FindStringExact(-1, rez) == LB_ERR)
		m_combo_rezultat.SetCurSel(-1);
	else
		m_combo_rezultat.SetCurSel(m_combo_rezultat.FindStringExact(-1, rez));
}


//////////////// P R I K A Z  ///////////////////////

void Dialog_Natjecanja::OnBnClickedBtnPrikazi()
{
	DPrikazNatjecanja = new Dialog_Prikaz_Natjecanja;
	DPrikazNatjecanja->DoModal();
}


void Dialog_Natjecanja::OnBnClickedBtnZatvori3()
{
	PostQuitMessage(0);
}


void Dialog_Natjecanja::OnBnClickedBtnPocetna3()
{
	OnCancel();
}


void Dialog_Natjecanja::OnBnClickedBtnClanovi3()
{
	DialogClanovi* DClanovi;
	DClanovi = new DialogClanovi;
	OnCancel();
	DClanovi->DoModal();
}


void Dialog_Natjecanja::OnBnClickedBtnClanarine3()
{
	DialogClanarine* DClanarine;
	DClanarine = new DialogClanarine;
	OnCancel();
	DClanarine->DoModal();
}
