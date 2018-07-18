// ClanoviSet.h : Implementation of the CClanoviSet class



// CClanoviSet implementation

// code generated on 31. ožujka 2018., 3:19

#include "stdafx.h"
#include "ClanoviSet.h"
IMPLEMENT_DYNAMIC(CClanoviSet, CRecordset)

CClanoviSet::CClanoviSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_IDclana = 0;
	m_ImePrezime = L"";
	m_Spol = L"";
	m_DatumRodenja;
	m_Tel = L"";
	m_Adresa = L"";
	m_Mail = L"";
	m_Aktivnost = L"";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}

CString CClanoviSet::GetDefaultConnect()
{
	return _T("DSN=BazaKlub;");
}

CString CClanoviSet::GetDefaultSQL()
{
	return _T("[Clanovi]");
}

void CClanoviSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[IDclana]"), m_IDclana);
	RFX_Text(pFX, _T("[ImePrezime]"), m_ImePrezime);
	RFX_Text(pFX, _T("[Spol]"), m_Spol);
	RFX_Date(pFX, _T("[DatumRodenja]"), m_DatumRodenja);
	RFX_Text(pFX, _T("[Tel]"), m_Tel);
	RFX_Text(pFX, _T("[Adresa]"), m_Adresa);
	RFX_Text(pFX, _T("[Mail]"), m_Mail);
	RFX_Text(pFX, _T("[Aktivnost]"), m_Aktivnost);

}
/////////////////////////////////////////////////////////////////////////////
// CClanoviSet diagnostics

#ifdef _DEBUG
void CClanoviSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClanoviSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


long CClanoviSet::MaxID()
{
	MoveLast();
	return m_IDclana;
}
