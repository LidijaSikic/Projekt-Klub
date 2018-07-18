// ClanarineSet.h : Declaration of the CClanarineSet

#pragma once

// code generated on 30. travnja 2018., 15:41

class CClanarineSet : public CRecordset
{
public:
	CClanarineSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClanarineSet)

	long	m_IDuplate;
	long	m_IDclana;
	CTime	m_DatumUplate;
	CStringW	m_IznosUplate;
	CStringW	m_SvrhaUplate;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	long MaxID();
};


