// DialogClanarine.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Klub.h"
#include "ClanoviSet.h"
#include "DialogClanarine.h"
#include "ClanarineSet.h"
#include "DialogClanovi.h"
#include "Dialog_Natjecanja.h"


// DialogClanarine dialog

IMPLEMENT_DYNAMIC(DialogClanarine, CDialog)

DialogClanarine::DialogClanarine(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_CLANARINE, pParent)
	, m_rb_unos_val(0)	
{
	RClanovi = new CClanoviSet;
	RClanarine = new CClanarineSet;
}

DialogClanarine::~DialogClanarine()
{
}

void DialogClanarine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SVRHA_UPLATE, m_edit_svrha_uplate);
	DDX_Control(pDX, IDC_DAT_UPLATE, m_dat_uplate);
	DDX_Control(pDX, IDC_COMBO_UPLATITELJ, m_combo_uplatitelj);
	DDX_Control(pDX, IDC_COMBO_LISTA_UPLATA, m_combo_lista_uplata);
	DDX_Control(pDX, IDC_COMBO_IZNOS_UPLATE, m_combo_iznos);
	DDX_Control(pDX, IDC_BTN_SPREMI, m_btn_spremi);
	DDX_Control(pDX, IDC_BTN_ODUSTANI, m_btn_odustani);
	DDX_Radio(pDX, IDC_RD_UNOS_UPLATE, m_rb_unos_val);
	DDX_Control(pDX, IDC_STATIC_UPLATITELJ, m_static_uplatitelj);
	DDX_Control(pDX, IDC_RD_UNOS_UPLATE, m_rd_unos_uplate);
	DDX_Control(pDX, IDC_RD_PROMJENA_CLANARINE, m_rd_promjena_clanarine);
	DDX_Control(pDX, IDC_STATIC_LISTA_UPLATA, m_static_lista_uplata);
}


BEGIN_MESSAGE_MAP(DialogClanarine, CDialog)
	ON_BN_CLICKED(IDC_RD_PROMJENA_CLANARINE, &DialogClanarine::OnBnClickedRdPromjenaClanarine)
	ON_BN_CLICKED(IDC_RD_UNOS_UPLATE, &DialogClanarine::OnBnClickedRdUnosUplate)
	ON_CBN_SELCHANGE(IDC_COMBO_UPLATITELJ, &DialogClanarine::OnCbnSelchangeComboUplatitelj)
	ON_CBN_SELCHANGE(IDC_COMBO_LISTA_UPLATA, &DialogClanarine::OnCbnSelchangeComboListaUplata)
	ON_BN_CLICKED(IDC_BTN_SPREMI, &DialogClanarine::OnBnClickedBtnSpremi)
	ON_BN_CLICKED(IDC_BTN_ODUSTANI, &DialogClanarine::OnBnClickedBtnOdustani)
	ON_BN_CLICKED(IDC_BTN_PRIKAZI_UPLATE, &DialogClanarine::OnBnClickedBtnPrikaziUplate)
ON_BN_CLICKED(IDC_BTN_POCETNA2, &DialogClanarine::OnBnClickedBtnPocetna2)
ON_BN_CLICKED(IDC_BTN_ZATVORI2, &DialogClanarine::OnBnClickedBtnZatvori2)
ON_BN_CLICKED(IDC_BTN_CLANOVIx, &DialogClanarine::OnBnClickedBtnClanovix)
ON_BN_CLICKED(IDC_BTN_NATJECANJAx, &DialogClanarine::OnBnClickedBtnNatjecanjax)
END_MESSAGE_MAP()


// DialogClanarine message handlers


BOOL DialogClanarine::OnInitDialog()
{
	CDialog::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, FALSE);
	
	m_combo_iznos.SetCurSel(0);

	m_dat_uplate.SetFormat(_T("dd.MM.yyyy"));
	
	CString Ime;
	
	if (!RClanovi->IsOpen())
	RClanovi->Open();
	while (!RClanovi->IsEOF()) {
		Ime = RClanovi->m_ImePrezime;
		m_combo_uplatitelj.AddString(Ime);
		RClanovi->MoveNext();
	}
	RClanovi->Close();
	m_combo_uplatitelj.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DialogClanarine::OnBnClickedRdPromjenaClanarine()
{
	m_static_uplatitelj.SetWindowTextW(_T("Izaberite uplatitelja"));
	m_combo_lista_uplata.EnableWindow(TRUE);
	m_static_lista_uplata.ShowWindow(TRUE);
}


void DialogClanarine::OnBnClickedRdUnosUplate()
{
	m_static_uplatitelj.SetWindowTextW(_T("Uplatitelj"));
	Ocisti();
	m_combo_lista_uplata.EnableWindow(FALSE);
	m_static_lista_uplata.ShowWindow(FALSE);
}


void DialogClanarine::OnCbnSelchangeComboUplatitelj()
{
	if (m_rd_promjena_clanarine.GetCheck() == 1)
	{
		Ocisti();
	
		CString strIDclana;
		strIDclana.Format(_T("%ld"), NadiIDclana());

		CString strDateOd, strDateDo;

		RClanarine->m_strFilter = _T("IDclana = ") + strIDclana + _T("");
		if(!RClanarine->IsOpen())
		RClanarine->Open();

		while (!RClanarine->IsEOF()) {

			CString strIDuplate;
			long IDuplate = RClanarine->m_IDuplate;
			strIDuplate.Format(_T("%ld"), IDuplate);

			CString svrhaUplate = RClanarine->m_SvrhaUplate;

			CString  iznos;
			iznos = RClanarine->m_IznosUplate;

			CString strDatum;
			CTime datum = RClanarine->m_DatumUplate;
			strDatum = datum.Format(_T("%d.%m.%Y"));

			CString podaci;
			podaci = strIDuplate + _T(":  ") + svrhaUplate + _T("    ") + strDatum + _T("    ") + iznos + _T("");
			m_combo_lista_uplata.AddString(podaci);

			RClanarine->MoveNext();
		}
		RClanarine->m_strFilter = "";
		RClanarine->Close();

		m_combo_lista_uplata.SetCurSel(0);
	}
}


long DialogClanarine::NadiIDclana()
{
	CString ime;
	long IDclana;
	
	int nSel = m_combo_uplatitelj.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_uplatitelj.GetLBText(nSel, ime);
	}
	RClanovi->m_strFilter = _T("ImePrezime = '") + ime + _T("'");
	if (!RClanovi->IsOpen())
	RClanovi->Open();
	IDclana = RClanovi->m_IDclana;
	RClanovi->Close();

	return IDclana;
}


void DialogClanarine::OnCbnSelchangeComboListaUplata()
{
	CString podaci;
	int nSel = m_combo_lista_uplata.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_combo_lista_uplata.GetLBText(nSel, podaci);		
	}

	CString strIndex = podaci.Left(podaci.Find(_T(":")));
	strIndex.Trim();

	RClanarine->m_strFilter = _T("IDuplate = ") + strIndex + _T("");
	if (!RClanarine->IsOpen())
	RClanarine->Open();

	CString iznos = RClanarine->m_IznosUplate;
	if (m_combo_iznos.FindStringExact(-1, iznos) == LB_ERR)
		m_combo_iznos.SetCurSel(-1);
	else
		m_combo_iznos.SetCurSel(m_combo_iznos.FindStringExact(-1, iznos));
	
	CTime datum = RClanarine->m_DatumUplate;
	m_dat_uplate.SetTime(&datum);

	CString svrha = RClanarine->m_SvrhaUplate;
	m_edit_svrha_uplate.SetWindowTextW(svrha);

	RClanarine->Close();
}


void DialogClanarine::OnBnClickedBtnSpremi()
{
	Spremi();
}


void DialogClanarine::OnBnClickedBtnOdustani()
{
	Ocisti();
}


void DialogClanarine::Ocisti()
{
	CTime dat;
	dat = dat.GetCurrentTime();
	m_dat_uplate.SetTime(&dat);

	m_combo_iznos.SetCurSel(0);
	m_edit_svrha_uplate.SetWindowTextW(_T(""));
	m_combo_lista_uplata.ResetContent();
}


void DialogClanarine::Spremi()
{	
	if (m_rd_unos_uplate.GetCheck() == 1)
	{
		CString ime;
		long IDclana;
		m_combo_uplatitelj.GetWindowText(ime);
		RClanovi->m_strFilter = _T("[ImePrezime] = '") + ime + _T("'");
		RClanovi->Open();
		IDclana = RClanovi->m_IDclana;
		RClanovi->Close();

		if (!RClanarine->IsOpen())
		RClanarine->Open();
		
		long noviID;
		noviID = RClanarine->MaxID() + 1;

		RClanarine->AddNew();

		CTime datUplate;
		m_dat_uplate.GetTime(datUplate);

		CString iznos;
		m_combo_iznos.GetWindowText(iznos);

		CString svrha;
		m_edit_svrha_uplate.GetWindowTextW(svrha);

		RClanarine->m_IDuplate = noviID;
		RClanarine->m_IDclana = IDclana;
		RClanarine->m_DatumUplate = datUplate;
		RClanarine->m_IznosUplate = iznos;
		RClanarine->m_SvrhaUplate = svrha;

		if (!RClanarine->Update())
			MessageBox(_T("Unos nove uplate nije uspio"), _T("Greška"),
				MB_ICONERROR | MB_OK);
		else
			MessageBox(_T("Nova uplata je uspješno unesena u bazu"), _T("Obavijest"),
				MB_OK);
		RClanarine->Requery();
	}
	else if (m_rd_promjena_clanarine.GetCheck() == 1)
	{
		if (!RClanarine->IsOpen())
		RClanarine->Open();
		RClanarine->Edit();

		CTime datum;
		m_dat_uplate.GetTime(datum);

		CString iznos;
		m_combo_iznos.GetWindowText(iznos);

		CString svrha;
		m_edit_svrha_uplate.GetWindowTextW(svrha);

		RClanarine->m_IDclana = NadiIDclana();
		RClanarine->m_DatumUplate = datum;
		RClanarine->m_IznosUplate = iznos;
		RClanarine->m_SvrhaUplate = svrha;

		if (!RClanarine->Update()) {
			MessageBox(_T("Promjene nisu uspješno unesene"), _T("Greška"), MB_ICONEXCLAMATION | MB_OK);
		}
		else {
			MessageBox(_T("Promjene su uspješno unesene"), _T("Obavijest"), MB_OK);
		}
	}
	RClanarine->Requery();
	RClanarine->m_strFilter = _T("");
	RClanarine->Close();

	Ocisti();
}


void DialogClanarine::OnBnClickedBtnPrikaziUplate()
{
	DPrikazClanarina = new Dialog_prikaz_clanarina;
	DPrikazClanarina->DoModal();
}


//void DialogClanarine::OnBnClickedBtnClanovi2()
//{
//}


void DialogClanarine::OnBnClickedBtnPocetna2()
{
	OnCancel();
}


void DialogClanarine::OnBnClickedBtnZatvori2()
{
	PostQuitMessage(0);
}


void DialogClanarine::OnBnClickedBtnClanovix()
{
	DialogClanovi* DClanovi;
	DClanovi = new DialogClanovi;
	OnCancel();
	DClanovi->DoModal();
}


void DialogClanarine::OnBnClickedBtnNatjecanjax()
{
	Dialog_Natjecanja* DNatjecanja;
	DNatjecanja = new Dialog_Natjecanja;
	OnCancel();
	DNatjecanja->DoModal();
}
