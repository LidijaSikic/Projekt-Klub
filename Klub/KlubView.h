
// KlubView.h : interface of the CKlubView class
//

#pragma once

#include "DialogClanovi.h"
#include "DialogClanarine.h"
#include "Dialog_Natjecanja.h"

class CKlubSet;

class CKlubView : public CRecordView
{
protected: // create from serialization only
	CKlubView();
	DECLARE_DYNCREATE(CKlubView)

	DialogClanovi* DClanovi;
	DialogClanarine* DClanarine;
	Dialog_Natjecanja* DNatjecanja;

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_KLUB_FORM };
#endif
	CKlubSet* m_pSet;

// Attributes
public:
	CKlubDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CKlubView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnClanovi();
	afx_msg void OnBnClickedBtnClanarine();
	afx_msg void OnBnClickedBtnNatjecanja();
};

#ifndef _DEBUG  // debug version in KlubView.cpp
inline CKlubDoc* CKlubView::GetDocument() const
   { return reinterpret_cast<CKlubDoc*>(m_pDocument); }
#endif

