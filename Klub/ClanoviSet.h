// ClanoviSet.h : Declaration of the CClanoviSet

#pragma once

// code generated on 31. ožujka 2018., 3:19

class CClanoviSet : public CRecordset
{
public:
	CClanoviSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClanoviSet)

	long	m_IDclana;
	CStringW	m_ImePrezime;
	CStringW	m_Spol;
	CTime	m_DatumRodenja;
	CStringW	m_Tel;
	CStringW	m_Adresa;
	CStringW	m_Mail;
	CStringW	m_Aktivnost;

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


