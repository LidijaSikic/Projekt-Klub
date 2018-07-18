#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "ClanoviSet.h"
#include "ClanarineSet.h"
#include "Dialog_prikaz_clanarina.h"


// DialogClanarine dialog

class DialogClanarine : public CDialog
{
	DECLARE_DYNAMIC(DialogClanarine)

public:
	DialogClanarine(CWnd* pParent = NULL);   // standard constructor
	CClanoviSet* RClanovi;
	CClanarineSet* RClanarine;

	virtual ~DialogClanarine();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLANARINE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	Dialog_prikaz_clanarina* DPrikazClanarina;
	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_edit_svrha_uplate;
	CDateTimeCtrl m_dat_uplate;
	CComboBox m_combo_uplatitelj;
	CComboBox m_combo_lista_uplata;
	CComboBox m_combo_iznos;
	CButton m_btn_spremi;
	CButton m_btn_odustani;
	BOOL m_rb_unos_val;
	afx_msg void OnBnClickedRdPromjenaClanarine();
	CStatic m_static_uplatitelj;
	afx_msg void OnBnClickedRdUnosUplate();
	afx_msg void OnCbnSelchangeComboUplatitelj();
	long NadiIDclana();
	afx_msg void OnCbnSelchangeComboListaUplata();
	afx_msg void OnBnClickedBtnSpremi();
	afx_msg void OnBnClickedBtnOdustani();
	void Ocisti();
	void Spremi();
	CButton m_rd_unos_uplate;
	CButton m_rd_promjena_clanarine;
	afx_msg void OnBnClickedBtnPrikaziUplate();
	afx_msg void OnBnClickedBtnPocetna2();
	afx_msg void OnBnClickedBtnZatvori2();
	afx_msg void OnBnClickedBtnClanovix();
	afx_msg void OnBnClickedBtnNatjecanjax();
	CStatic m_static_lista_uplata;
};
