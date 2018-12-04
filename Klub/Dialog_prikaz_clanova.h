#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "ClanoviSet.h"


// Dialog_prikaz_clanova dialog

class Dialog_prikaz_clanova : public CDialog
{
	DECLARE_DYNAMIC(Dialog_prikaz_clanova)

public:
	Dialog_prikaz_clanova(CWnd* pParent = NULL);   // standard constructor
	
	CClanoviSet* RClanovi;
	
	virtual ~Dialog_prikaz_clanova();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRIKAZ_CLANOVA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	CFont* m_pFntData;
	CFont* m_pFntHeader1;
	CFont* m_pFntHeader2;
	CPen m_penBlack;
	void PrintHeader(CDC* pDC, CPrintInfo *pInfo);

	DECLARE_MESSAGE_MAP()
public:
	
	CListCtrl m_Lista_Clanovi;	
	CButton m_rd_aktivni;
	CButton m_rd_neaktivni;
	CButton m_rd_svi;
	int m_rb_stanje;
	CButton m_btn_prikazi;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPrikazi();
	afx_msg void OnBnClickedBtnIspisiPrikaz();
	afx_msg void OnBnClickedBtnZatvoriAplikaciju();
	afx_msg void OnBnClickedBtnPocetna4();
	afx_msg void OnBnClickedBtnClanarine4();
	afx_msg void OnBnClickedBtnNatjecanja4();
	void popuni_naslove();
	void popuni_listu();
	void Print();
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);	
	afx_msg void OnLvnItemchangedListClanovi(NMHDR *pNMHDR, LRESULT *pResult);
};

