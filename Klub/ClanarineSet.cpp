// ClanarineSet.h : Implementation of the CClanarineSet class



// CClanarineSet implementation

// code generated on 30. travnja 2018., 15:41

#include "stdafx.h"
#include "ClanarineSet.h"
IMPLEMENT_DYNAMIC(CClanarineSet, CRecordset)

CClanarineSet::CClanarineSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_IDuplate = 0;
	m_IDclana = 0;
	m_DatumUplate;
	m_IznosUplate = L"";
	m_SvrhaUplate = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CClanarineSet::GetDefaultConnect()
{
	return _T("DSN=BazaKlub;");
}

CString CClanarineSet::GetDefaultSQL()
{
	return _T("[Clanarine]");
}

void CClanarineSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[IDuplate]"), m_IDuplate);
	RFX_Long(pFX, _T("[IDclana]"), m_IDclana);
	RFX_Date(pFX, _T("[DatumUplate]"), m_DatumUplate);
	RFX_Text(pFX, _T("[IznosUplate]"), m_IznosUplate);
	RFX_Text(pFX, _T("[SvrhaUplate]"), m_SvrhaUplate);

}
/////////////////////////////////////////////////////////////////////////////
// CClanarineSet diagnostics

#ifdef _DEBUG
void CClanarineSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClanarineSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


long CClanarineSet::MaxID()
{
	MoveLast();
	return m_IDclana;
}
