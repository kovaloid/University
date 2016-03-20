#if !defined(AFX_MAINFRM_H__6C8FFC32_52FD_4F10_A490_A1F6BDDABB3C__INCLUDED_)
#define AFX_MAINFRM_H__6C8FFC32_52FD_4F10_A490_A1F6BDDABB3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CMainFrame : public CFrameWnd
{
public:	
	void OnIndex();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame);
	DECLARE_MESSAGE_MAP()
};

#endif
