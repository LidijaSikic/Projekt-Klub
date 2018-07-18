// NatjecanjaSet.h : Implementation of the CNatjecanjaSet class



// CNatjecanjaSet implementation

// code generated on 3. svibnja 2018., 13:59

#include "stdafx.h"
#include "NatjecanjaSet.h"
IMPLEMENT_DYNAMIC(CNatjecanjaSet, CRecordset)

CNatjecanjaSet::CNatjecanjaSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_IDnatjecanja = 0;
	m_NazivNatjecanja = L"";
	m_DatumNatjecanja;
	m_Koeficijent = 0.0;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}

CString CNatjecanjaSet::GetDefaultConnect()
{
	return _T("DSN=BazaKlub;");
}

CString CNatjecanjaSet::GetDefaultSQL()
{
	return _T("[Natjecanja]");
}

void CNatjecanjaSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[IDnatjecanja]"), m_IDnatjecanja);
	RFX_Text(pFX, _T("[NazivNatjecanja]"), m_NazivNatjecanja);
	RFX_Date(pFX, _T("[DatumNatjecanja]"), m_DatumNatjecanja);
	RFX_Double(pFX, _T("[Koeficijent]"), m_Koeficijent);

}
/////////////////////////////////////////////////////////////////////////////
// CNatjecanjaSet diagnostics

#ifdef _DEBUG
void CNatjecanjaSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CNatjecanjaSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


long CNatjecanjaSet::MaxID()
{
	MoveLast();
	return m_IDnatjecanja;
}
