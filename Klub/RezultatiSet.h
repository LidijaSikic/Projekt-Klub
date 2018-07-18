// RezultatiSet.h : Declaration of the CRezultatiSet

#pragma once

// code generated on 21. svibnja 2018., 13:27

class CRezultatiSet : public CRecordset
{
public:
	CRezultatiSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRezultatiSet)

// Field/Param Data

	long	m_IDrezultata;
	long	m_IDclana;
	long	m_IDnatjecanja;
	CStringW	m_Kategorija;
	CStringW	m_Rezultat;

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


