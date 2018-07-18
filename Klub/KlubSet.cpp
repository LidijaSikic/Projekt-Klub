
// KlubSet.cpp : implementation of the CKlubSet class
//

#include "stdafx.h"
#include "Klub.h"
#include "KlubSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKlubSet implementation

// code generated on 23. ožujka 2018., 23:49

IMPLEMENT_DYNAMIC(CKlubSet, CRecordset)

CKlubSet::CKlubSet(CDatabase* pdb)
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

CString CKlubSet::GetDefaultConnect()
{
	return _T("DSN=BazaKlub;");
}

CString CKlubSet::GetDefaultSQL()
{
	return _T("[Clanovi]");
}

void CKlubSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
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
// CKlubSet diagnostics

#ifdef _DEBUG
void CKlubSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CKlubSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG



long CKlubSet::maxID()
{
	MoveLast();
	return m_IDclana;
}
