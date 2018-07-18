
// KlubDoc.cpp : implementation of the CKlubDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Klub.h"
#endif

#include "KlubSet.h"
#include "KlubDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKlubDoc

IMPLEMENT_DYNCREATE(CKlubDoc, CDocument)

BEGIN_MESSAGE_MAP(CKlubDoc, CDocument)
END_MESSAGE_MAP()


// CKlubDoc construction/destruction

CKlubDoc::CKlubDoc()
{
	// TODO: add one-time construction code here

}

CKlubDoc::~CKlubDoc()
{
}

BOOL CKlubDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

//CKlubDoc* CKlubDoc::GetDoc()
//{
	//CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
	//return (CKlubDoc*)pFrame->GetActiveDocument();
//}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CKlubDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CKlubDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CKlubDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CKlubDoc diagnostics

#ifdef _DEBUG
void CKlubDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKlubDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKlubDoc commands
