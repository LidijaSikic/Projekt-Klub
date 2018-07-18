#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "ClanoviSet.h"
#include "ClanarineSet.h"
#include "KlubDoc.h"


// Dialog_prikaz_clanarina dialog

class Dialog_prikaz_clanarina : public CDialog
{
	DECLARE_DYNAMIC(Dialog_prikaz_clanarina)
	
public:
	Dialog_prikaz_clanarina(CWnd* pParent = NULL);   // standard constructor

	CClanoviSet* RClanovi;
	CClanarineSet* RClanarine;

	virtual ~Dialog_prikaz_clanarina();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRIKAZ_CLANARINA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	CButton m_rd_clan;
	CButton m_rd_klub;
	BOOL m_rb_stanje;
	CDateTimeCtrl m_date_od;
	CDateTimeCtrl m_date_do;
	CButton m_btn_prikazi;
	CListCtrl m_lista;
	CComboBox m_combo;
	CButton m_rd_sve_uplate;
	CButton m_rd_razdoblje;
	BOOL m_rb_stanje_datumi;
	CEdit m_edit_pom;	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPrikazi();
	afx_msg void OnBnClickedBtnIspisiPrikaz();
	afx_msg void OnBnClickedBtnZatvoriAplikaciju1();
	afx_msg void OnBnClickedBtnPocetna();
	afx_msg void OnBnClickedBtnClanovi1();
	afx_msg void OnBnClickedBtnNatjecanja1();
	void popuni_naslove();
	long NadiIDclana();
	void NadiIme(long IDclana);	
};
