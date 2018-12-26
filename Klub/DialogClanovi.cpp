// DialogClanovi.cpp : implementation file
//

#include "stdafx.h"
#include "Klub.h"
#include "DialogClanovi.h"
#include "afxdialogex.h"
#include "ClanoviSet.h"
#include "DialogClanarine.h"
#include "Dialog_Natjecanja.h"


// DialogClanovi dialog

IMPLEMENT_DYNAMIC(DialogClanovi, CDialog)

DialogClanovi::DialogClanovi(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_CLANOVI, pParent)
	, m_rb_stanje_upis(0)
{	
	RClanovi = new CClanoviSet;
}

DialogClanovi::~DialogClanovi()
{
}

void DialogClanovi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RD_NOVI_CLAN, m_rb_stanje_upis);
	DDX_Control(pDX, IDC_RD_NOVI_CLAN, m_rb_upis_novog_clana);
	DDX_Control(pDX, IDC_RD_PROMJENA_CLANOVI, m_rb_promjena_podataka_clanovi);
	DDX_Control(pDX, IDC_EDIT_IME_CLANA, m_edit_ime_clana);
	DDX_Control(pDX, IDC_COMBO_CLANOVI_IMENA, m_combo_clanovi_imena);
	DDX_Control(pDX, IDC_COMBO_SPOL, m_combo_spol);
	DDX_Control(pDX, IDC_DAT_ROD, m_date_rod);
	DDX_Control(pDX, IDC_COMBO_AKT, m_combo_akt);
	DDX_Control(pDX, IDC_EDIT_TEL, m_edit_tel);
	DDX_Control(pDX, IDC_EDIT_ADRESA, m_edit_adresa);
	DDX_Control(pDX, IDC_EDIT_MAIL, m_edit_mail);
	DDX_Control(pDX, IDC_BTN_PRIKAZI_CLANOVE, m_btn_prikazi_clanove);
	DDX_Control(pDX, IDC_STATIC_IME, m_static_ime);
	DDX_Control(pDX, IDC_EDIT_ID_CLANA, m_edit_ID_clana);
}


BEGIN_MESSAGE_MAP(DialogClanovi, CDialog)
	ON_BN_CLICKED(IDC_RD_NOVI_CLAN, &DialogClanovi::OnBnClickedRdNoviClan)
	ON_BN_CLICKED(IDC_RD_PROMJENA_CLANOVI, &DialogClanovi::OnBnClickedRdPromjenaClanovi)
	ON_BN_CLICKED(IDC_BTN_SPREMI, &DialogClanovi::OnBnClickedBtnSpremi)
	ON_BN_CLICKED(IDC_BTN_ODUSTANI, &DialogClanovi::OnBnClickedBtnOdustani)
	ON_CBN_SELCHANGE(IDC_COMBO_CLANOVI_IMENA, &DialogClanovi::OnCbnSelchangeComboClanoviImena)
	ON_BN_CLICKED(IDC_BTN_PRIKAZI_CLANOVE, &DialogClanovi::OnBnClickedBtnPrikaziClanove)	
	ON_BN_CLICKED(IDC_BTN_POCETNA1, &DialogClanovi::OnBnClickedBtnPocetna1)
	ON_BN_CLICKED(IDC_BTN_ZATVORI1, &DialogClanovi::OnBnClickedBtnZatvori1)
	ON_BN_CLICKED(IDC_CLANARINE1, &DialogClanovi::OnBnClickedClanarine1)
	ON_BN_CLICKED(IDC_BTN_NATJECANJA1, &DialogClanovi::OnBnClickedBtnNatjecanja1)
END_MESSAGE_MAP()


// DialogClanovi message handlers


BOOL DialogClanovi::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, FALSE);

	m_combo_clanovi_imena.ShowWindow(FALSE);
	m_edit_ime_clana.SetFocus();
	m_combo_spol.SetCurSel(0);
	m_combo_akt.SetCurSel(0);

	m_date_rod.SetFormat(_T("dd.MM.yyyy"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DialogClanovi::OnBnClickedRdNoviClan()
{
	m_static_ime.SetWindowTextW(_T("Ime i prezime"));
	m_combo_clanovi_imena.ShowWindow(FALSE);
	m_edit_ime_clana.ShowWindow(TRUE);
	ocisti();
}


void DialogClanovi::OnBnClickedRdPromjenaClanovi()
{
	m_combo_clanovi_imena.ShowWindow(TRUE);	
	m_combo_clanovi_imena.ResetContent();	
	ucitaj_imena();		
}


void DialogClanovi::OnBnClickedBtnSpremi()
{
	if (provjeri_podatke() == false)
	{
		return;
	}
	else if (m_rb_upis_novog_clana.GetCheck() == 1)
	{
		spremi();
		ocisti();
	}
	else if (m_rb_promjena_podataka_clanovi.GetCheck() == 1)
	{
		promijeni();
		ocisti();
		
		m_combo_clanovi_imena.SetCurSel(-1);		
	}
}


void DialogClanovi::OnBnClickedBtnOdustani()
{
	ocisti();	
}


void DialogClanovi::ocisti()
{
	m_edit_ime_clana.SetWindowTextW(_T(""));
	m_combo_spol.SetCurSel(0);
	
	CTime date;
	date = date.GetCurrentTime();
	m_date_rod.SetTime(&date);
	m_combo_akt.SetCurSel(0);
	m_edit_tel.SetWindowTextW(_T(""));
	m_edit_adresa.SetWindowTextW(_T(""));
	m_edit_mail.SetWindowTextW(_T(""));
	m_combo_clanovi_imena.ShowWindow(FALSE);
	m_rb_upis_novog_clana.SetCheck(1);
	m_rb_promjena_podataka_clanovi.SetCheck(0);
}


void DialogClanovi::promijeni()
{	
	CString strIDclana;
	m_edit_ID_clana.GetWindowTextW(strIDclana);

	if (!RClanovi->IsOpen())
		RClanovi->Open();
	RClanovi->MoveFirst();

	RClanovi->Edit();

	CString ime;
	m_edit_ime_clana.GetWindowTextW(ime);

	CTime datRod;
	m_date_rod.GetTime(datRod);

	CString spol;
	m_combo_spol.GetWindowText(spol);

	CString aktivnost;
	m_combo_akt.GetWindowText(aktivnost);

	CString tel;
	m_edit_tel.GetWindowTextW(tel);

	CString adresa;
	m_edit_adresa.GetWindowTextW(adresa);

	CString mail;
	m_edit_mail.GetWindowTextW(mail);

	RClanovi->m_ImePrezime = ime;
	RClanovi->m_DatumRodenja = datRod;
	RClanovi->m_Spol = spol;
	RClanovi->m_Aktivnost = aktivnost;
	RClanovi->m_Tel = tel;
	RClanovi->m_Adresa = adresa;
	RClanovi->m_Mail = mail;

	if (!RClanovi->Update()) 
	{
		MessageBox(_T("Promjene nisu uspješno unesene"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
	}
	else 
	{
		MessageBox(_T("Promjene su uspješno unesene"), _T("Obavijest"), MB_OK);
	}

	UpdateData(FALSE);
	RClanovi->Requery();
	RClanovi->m_strFilter = "";
	RClanovi->Close();

	m_static_ime.SetWindowTextW(_T("Ime i prezime"));
	m_combo_clanovi_imena.ShowWindow(FALSE);
}


void DialogClanovi::spremi()
{
	long nNoviID = 0;
	if (!RClanovi->IsOpen())
	RClanovi->Open();

	long noviID = RClanovi->MaxID() + 1;

	RClanovi->AddNew();

	CString ime;
	m_edit_ime_clana.GetWindowText(ime);

	CTime datRod;
	m_date_rod.GetTime(datRod);

	CString spol;
	m_combo_spol.GetWindowText(spol);

	CString aktivnost;
	m_combo_akt.GetWindowText(aktivnost);

	CString tel;
	m_edit_tel.GetWindowTextW(tel);

	CString adresa;
	m_edit_adresa.GetWindowTextW(adresa);

	CString mail;
	m_edit_mail.GetWindowTextW(mail);

	RClanovi->m_IDclana = noviID;
	RClanovi->m_ImePrezime = ime;
	RClanovi->m_Spol = spol;
	RClanovi->m_DatumRodenja = datRod;
	RClanovi->m_Tel = tel;
	RClanovi->m_Adresa = adresa;
	RClanovi->m_Mail = mail;
	RClanovi->m_Aktivnost = aktivnost;

	if (!RClanovi->Update())
		MessageBox(_T("Unos novog èlana nije uspio"), _T("Greška"),
			MB_ICONERROR | MB_OK);
	else
		MessageBox(_T("Novi èlan je uspješno unesen u bazu"), _T("Obavijest"),
			MB_OK);
	RClanovi->Requery();
	RClanovi->Close();

	ocisti();
}


void DialogClanovi::ucitaj_imena()
{
	m_static_ime.SetWindowTextW(_T("Izaberi ime za promjenu"));

			if (!RClanovi->IsOpen())
				RClanovi->Open();

			if (RClanovi->IsBOF() && RClanovi->IsEOF())
			{
				MessageBox(_T("U bazi nema podataka"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
				return;
			}
			else
			{
				while (!RClanovi->IsEOF()) {
					m_combo_clanovi_imena.AddString(RClanovi->m_ImePrezime);
					RClanovi->MoveNext();
				}
			}
				RClanovi->Close();
				m_combo_clanovi_imena.SetCurSel(0);			
}

void DialogClanovi::OnCbnSelchangeComboClanoviImena()
{
	CString ime;
	
	int nSel = m_combo_clanovi_imena.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_clanovi_imena.GetLBText(nSel, ime);
	}	
	m_edit_ime_clana.SetWindowTextW(ime);

	RClanovi->m_strFilter = _T("[ImePrezime] = '") + ime + _T("'");
	if(!RClanovi->IsOpen())
	RClanovi->Open();

	long IDclana = RClanovi->m_IDclana;
	CString strIDclana;
	strIDclana.Format(_T("%ld"), IDclana);
	m_edit_ID_clana.SetWindowTextW(strIDclana);

	CString spol = RClanovi->m_Spol;
	if(m_combo_spol.FindStringExact(-1, spol)==LB_ERR)
		m_combo_spol.SetCurSel(-1);
	else
		m_combo_spol.SetCurSel(m_combo_spol.FindStringExact(-1, spol));

	CTime datRod = RClanovi->m_DatumRodenja;
	m_date_rod.SetTime(&datRod);

	CString aktivnost = RClanovi->m_Aktivnost;
	if (m_combo_akt.FindStringExact(-1, aktivnost) == LB_ERR)
		m_combo_akt.SetCurSel(-1);
	else
		m_combo_akt.SetCurSel(m_combo_akt.FindStringExact(-1, aktivnost));

	CString adresa = RClanovi->m_Adresa;
	m_edit_adresa.SetWindowText(adresa);

	CString mail = RClanovi->m_Mail;
	m_edit_mail.SetWindowText(mail);

	CString tel = RClanovi->m_Tel;
	m_edit_tel.SetWindowText(tel);

	CString strID;
	long brID = RClanovi->m_IDclana;
	strID.Format(_T("%ld"), brID);
	
	RClanovi->m_strFilter = _T("");
	RClanovi->Close();	
}


long DialogClanovi::nadi_ID_clana()
{
	CString ime;
	long IDclana;
	m_edit_ime_clana.GetWindowTextW(ime);
	RClanovi->m_strFilter = _T("ImePrezime = '") + ime + _T("'");
	If(!RClanovi->IsOpen())
	RClanovi->Open();
	IDclana = RClanovi->m_IDclana;
	RClanovi->Close();

	return IDclana;
}


void DialogClanovi::OnBnClickedBtnPrikaziClanove()
{	
	DPrikazClanova = new Dialog_prikaz_clanova;
	DPrikazClanova->DoModal();
}


bool DialogClanovi::provjeri_podatke()
{
	int nSel;

	CString text;
	m_edit_ime_clana.GetWindowTextW(text);

	CString spol;
	nSel = m_combo_spol.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_spol.GetLBText(nSel, spol);
	}	
	CString  aktivnost;
	nSel = m_combo_spol.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_akt.GetLBText(nSel, aktivnost);
	}
	if (text.IsEmpty())
	{
		MessageBox(_T("Nije uneseno ime èlana"), _T("Greška"),
			MB_ICONERROR | MB_OK);
		m_edit_ime_clana.SetFocus();
		return false;
	}
	else if ((spol != _T("m")) && (spol != _T("ž")))
	{
		MessageBox(_T("Krivi unos! Za spol unesite: m ili ž"), _T("Greška"), MB_ICONERROR | MB_OK);					
			m_combo_spol.SetFocus();
			return false;
	}
	else if ((aktivnost != _T("aktivan")) && (aktivnost != _T("neaktivan")) && (aktivnost != _T("ispisan")))
	{
		MessageBox(_T("Krivi unos! Za aktivnost unesite: aktivan, neaktivan ili ispisan"), _T("Greška"),
			MB_ICONERROR | MB_OK);
		m_combo_akt.SetFocus();
		return false;
	}
	else
		return true;
}



void DialogClanovi::OnBnClickedBtnPocetna1()
{
	OnCancel();
}


void DialogClanovi::OnBnClickedBtnZatvori1()
{
	PostQuitMessage(0);
}


void DialogClanovi::OnBnClickedClanarine1()
{
	DialogClanarine* DClanarine;
	DClanarine = new DialogClanarine;
	OnCancel();
	DClanarine->DoModal();
}


void DialogClanovi::OnBnClickedBtnNatjecanja1()
{
	Dialog_Natjecanja* DNatjecanja;
	DNatjecanja = new Dialog_Natjecanja;
	OnCancel();
	DNatjecanja->DoModal();
}
