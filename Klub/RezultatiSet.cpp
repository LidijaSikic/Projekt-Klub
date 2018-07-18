// RezultatiSet.h : Implementation of the CRezultatiSet class



// CRezultatiSet implementation

// code generated on 21. svibnja 2018., 13:27

#include "stdafx.h"
#include "RezultatiSet.h"
IMPLEMENT_DYNAMIC(CRezultatiSet, CRecordset)

CRezultatiSet::CRezultatiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_IDrezultata = 0;
	m_IDclana = 0;
	m_IDnatjecanja = 0;
	m_Kategorija = L"";
	m_Rezultat = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CRezultatiSet::GetDefaultConnect()
{
	return _T("DSN=BazaKlub;");
}

CString CRezultatiSet::GetDefaultSQL()
{
	return _T("[Rezultati]");
}

void CRezultatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[IDrezultata]"), m_IDrezultata);
	RFX_Long(pFX, _T("[IDclana]"), m_IDclana);
	RFX_Long(pFX, _T("[IDnatjecanja]"), m_IDnatjecanja);
	RFX_Text(pFX, _T("[Kategorija]"), m_Kategorija);
	RFX_Text(pFX, _T("[Rezultat]"), m_Rezultat);

}
/////////////////////////////////////////////////////////////////////////////
// CRezultatiSet diagnostics

#ifdef _DEBUG
void CRezultatiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRezultatiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


long CRezultatiSet::MaxID()
{
	MoveLast();
	return m_IDrezultata;
}
