
// KlubSet.h: interface of the CKlubSet class
//


#pragma once

// code generated on 23. ožujka 2018., 23:49

class CKlubSet : public CRecordset
{
public:
	CKlubSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CKlubSet)

// Field/Param Data

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

	long maxID();
};

