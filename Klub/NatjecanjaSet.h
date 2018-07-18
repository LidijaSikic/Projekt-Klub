// NatjecanjaSet.h : Declaration of the CNatjecanjaSet

#pragma once

// code generated on 3. svibnja 2018., 13:59

class CNatjecanjaSet : public CRecordset
{
public:
	CNatjecanjaSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNatjecanjaSet)

// Field/Param Data

	long	m_IDnatjecanja;
	CStringW	m_NazivNatjecanja;
	CTime	m_DatumNatjecanja;
	double	m_Koeficijent;

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


