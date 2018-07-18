#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "ClanoviSet.h"
#include "NatjecanjaSet.h"
#include "RezultatiSet.h"
#include "Dialog_Prikaz_Natjecanja.h"

// Dialog_Natjecanja dialog

class Dialog_Natjecanja : public CDialog
{
	DECLARE_DYNAMIC(Dialog_Natjecanja)

public:
	Dialog_Natjecanja(CWnd* pParent = NULL);   // standard constructor

	CClanoviSet* RClanovi;
	CNatjecanjaSet* RNatjecanja;	
	CRezultatiSet* RRezultati;

	virtual ~Dialog_Natjecanja();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NATJECANJA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	Dialog_Prikaz_Natjecanja* DPrikazNatjecanja;

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_naziv_natjecanja;
	CDateTimeCtrl m_dat_odrzavanja;
	CEdit m_edit_koeficijent;
	CComboBox m_combo_lista_natjecanja;
	CButton m_rd_unos_natjecanja;
	CButton m_rd_promjena_unosa;
	BOOL m_rb_natjecanja_val;
	CComboBox m_combo_natjecanje_rez;
	CComboBox m_combo_natjecatelj;
	CEdit m_edit_kategorija;
	CButton m_rd_unos_rezultata;
	CButton m_rd_promjena_rezultata;
	BOOL m_rb_rezultat_val;	
	CButton m_rd_natjecatelj;
	CButton m_btn_spremi_natjecanja;
	CButton m_btn_odustani_natjecanja;
	CButton m_btn_spremi_rez;
	CButton m_btn_odustani_rez;
	CButton m_btn_prikazi;
	CButton m_rd_promjena_unosa_rez_za_natjecanje;
	BOOL m_rb_promjena_rez_za_natjecanje_val;
	CButton m_rd_promjena_unosa_rez_za_natjecatelja;
	CEdit m_edit_pom;
	CListBox m_list_podaci;
	CComboBox m_combo_rezultat;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRdUnosNatjecanja();
	afx_msg void OnBnClickedRdPromjenaUnosa();
	afx_msg void OnBnClickedRdUnosRezultata();
	afx_msg void OnBnClickedRdPromjenaRezultata();
	afx_msg void OnBnClickedBtnSpremiNatj();
	afx_msg void OnBnClickedBtnOdustaniNatj();
	afx_msg void OnBnClickedBtnSpremiRez();
	afx_msg void OnBnClickedBtnOdustaniRez();	
	afx_msg void OnBnClickedRdNatjecanja();
	afx_msg void OnCbnSelchangeComboListaNatjecanja();
	afx_msg void OnBnClickedRdPromjenaRezZaNatjecanje();
	afx_msg void OnBnClickedRdPromjenaUnosaRezZaNatjecatelja();
	afx_msg void OnCbnSelchangeComboNatjecatelj();
	afx_msg void OnCbnSelchangeComboNatjecanjeRez();
	afx_msg void OnLbnSelchangeListPodaci();
	afx_msg void OnBnClickedBtnPrikazi();	
	void OcistiNatjecanja();
	void OcistiRezultate();
	void SpremiNatjecanje();
	void PromijeniNatjecanje();	
	void UcitajNatjecanje_rez();
	void UcitajNatjecatelje_rez();	
	long NadiIDnatjecanja();
	long NadiIDnatjecatelja();	
	void NadiIme(long IDclana);
	void SpremiRez();
	void PromijeniRez();
	void NadiNatjecanje(long IDnatjecanja);	
	afx_msg void OnBnClickedBtnZatvori3();
	afx_msg void OnBnClickedBtnPocetna3();
	afx_msg void OnBnClickedBtnClanovi3();
	afx_msg void OnBnClickedBtnClanarine3();
};
