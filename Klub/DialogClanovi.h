#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "ClanoviSet.h"
#include "Dialog_prikaz_clanova.h"


// DialogClanovi dialog

class DialogClanovi : public CDialog
{
	DECLARE_DYNAMIC(DialogClanovi)

public:
	DialogClanovi(CWnd* pParent = NULL);   // standard constructor
	
	CClanoviSet* RClanovi;
	
	virtual ~DialogClanovi();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLANOVI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	Dialog_prikaz_clanova* DPrikazClanova;
	
	DECLARE_MESSAGE_MAP()
public:
	
	int m_rb_stanje_upis;
	CButton m_rb_upis_novog_clana;
	CButton m_rb_promjena_podataka_clanovi;
	CEdit m_edit_ime_clana;
	CComboBox m_combo_clanovi_imena;
	CComboBox m_combo_spol;
	CDateTimeCtrl m_date_rod;
	CComboBox m_combo_akt;
	CEdit m_edit_tel;
	CEdit m_edit_adresa;
	CEdit m_edit_mail;
	CButton m_btn_prikazi_clanove;	
	CStatic m_static_ime;
	CEdit m_edit_ID_clana;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRdNoviClan();
	afx_msg void OnBnClickedRdPromjenaClanovi();
	afx_msg void OnBnClickedBtnSpremi();
	afx_msg void OnBnClickedBtnOdustani();
	afx_msg void OnCbnSelchangeComboClanoviImena();
	afx_msg void OnBnClickedBtnPrikaziClanove();
	void ocisti();
	void promijeni();
	void spremi();
	void ucitaj_imena();	
	long nadi_ID_clana();
	bool provjeri_podatke();	
	afx_msg void OnBnClickedBtnPocetna1();
	afx_msg void OnBnClickedBtnZatvori1();
	afx_msg void OnBnClickedClanarine1();
	afx_msg void OnBnClickedBtnNatjecanja1();
};
