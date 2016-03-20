#include "stdafx.h"
#include "windows.h"
#include "mmsystem.h"
#include "Bulls_Cow.h"
#include "MainFrm.h"
#include "Bulls_CowDoc.h"
#include "Bulls_CowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CBulls_CowApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)	
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)	
END_MESSAGE_MAP()

CBulls_CowApp::CBulls_CowApp(){}
CBulls_CowApp theApp;

BOOL CBulls_CowApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(0);
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBulls_CowDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CBulls_CowView));
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD){}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CBulls_CowApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
