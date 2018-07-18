
// KlubDoc.h : interface of the CKlubDoc class
//


#pragma once
#include "KlubSet.h"


class CKlubDoc : public CDocument
{
protected: // create from serialization only
	CKlubDoc();
	DECLARE_DYNCREATE(CKlubDoc)

// Attributes
public:
	CKlubSet m_KlubSet;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CKlubDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
