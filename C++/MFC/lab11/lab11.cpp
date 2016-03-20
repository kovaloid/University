// lab11.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "lab11.h"
#include "MainFrm.h"

#include "lab11Doc.h"
#include "lab11View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab11App

BEGIN_MESSAGE_MAP(Clab11App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Clab11App::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Clab11App construction

Clab11App::Clab11App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Clab11App object

Clab11App theApp;


// Clab11App initialization

BOOL Clab11App::InitInstance()
{
	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(Clab11Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(Clab11View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void Clab11App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// Clab11App message handlers

BOOL Clab11App::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class

	//Вызвать функцию базового класса СWinApp::OnIdle(), чтобы завершить его служебные задачи
		CWinApp::OnIdle(lCount);
	//Получить указатель на шаблон документа
		POSITION pos = GetFirstDocTemplatePosition();
		CDocTemplate* pDocTemplate=GetNextDocTemplate(pos);
	//Получить указатель на документ
		pos=pDocTemplate->GetFirstDocPosition();
		CDocument* pDoc=pDocTemplate->GetNextDoc(pos);
	//Получить указатель на представление
		pos=pDoc->GetFirstViewPosition();
		Clab11View* pView=(Clab11View*) pDoc->GetNextView(pos);
	//Переменные для хранения времени
		static DWORD PrevTimeTask1=0;
		static DWORD PrevTimeTask2=0;
		static DWORD PrevTimeTask3=0;
	//Получить Текущее время
		DWORD CurrentTime=GetTickCount();
	//Получить данные от элементов уравления
		pView->UpdateData(TRUE);
	//Если время превысило 50 мс, то прибавить 1
		if(CurrentTime>PrevTimeTask1+50 && 
			pView->m_EnableTask1Check)
		{
			pView->m_Task1Edit=pView->m_Task1Edit+1;
			pView->UpdateData(FALSE);
			PrevTimeTask1=CurrentTime;
		}
	//Если время превысило 500 мс и cчетчик включен, то прибавить 1
		if(CurrentTime>PrevTimeTask2+500 &&
			pView->m_EnableTask2Check)
		{
			pView->m_Task2Edit=pView->m_Task2Edit+1;
			pView->UpdateData(FALSE);
			PrevTimeTask2=CurrentTime;
		}
	//Если время превысило 1000 мс и cчетчик включен, то прибавить 1
		if(CurrentTime>PrevTimeTask3+1000 &&
			pView->m_EnableTask3Check)
		{
			pView->m_Task3Edit=pView->m_Task3Edit+1;
			pView->UpdateData(FALSE);
			PrevTimeTask3=CurrentTime;
		}

	//Вернуть TRUE, чтобы опять запустить себя, если есть фоновый режим
	return TRUE;
}
