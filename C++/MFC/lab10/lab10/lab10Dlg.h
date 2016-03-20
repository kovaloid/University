// lab10Dlg.h : header file
//

#pragma once

//----------------------------------------------------------------------------
/* number of bytes to be read during each read operation */
#define MAXREAD 32768
/* macro to determine if resource is a DIB */
#define ISDIB(bft) ((bft) == BFT_BITMAP)
/* macro to determine to round off the given value to the closest byte */
#define WIDTHBYTES(i) ((i+31)/32*4)
/* 'BM' */
#define BFT_BITMAP 0x4d42
/* Macros to display/remove hourglass cursor for lengthy operations */
static HCURSOR hcurSave;
#define StartWait() hcurSave = SetCursor(LoadCursor(NULL,IDC_WAIT))
#define EndWait() SetCursor(hcurSave)
//----------------------------------------------------------------------------


// Clab10Dlg dialog
class Clab10Dlg : public CDialog
{
// Construction
public:
	Clab10Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileExit();
	afx_msg void OnFileOpen32771();
	BITMAP bm;
	HBITMAP hbm;
//----------------------------------------------------------------------------
	WORD PaletteSize(VOID FAR * pv);
	HANDLE OpenDIB(LPWSTR szFile);
	HANDLE ReadDibBitmapInfo(INT fh);
	BOOL DibInfo(HANDLE hbi, LPBITMAPINFOHEADER lpbi);
	DWORD PASCAL lread(INT fh, VOID FAR *pv, DWORD ul);
	VOID ReadBitMapFileHeaderandConvertToDwordAlign(HFILE fh, LPBITMAPFILEHEADER pbf, LPDWORD lpdwoff);
	WORD DibNumColors(VOID FAR * pv);
	HBITMAP BitmapFromDib(HANDLE hdib, HPALETTE hpal);
//----------------------------------------------------------------------------
};
