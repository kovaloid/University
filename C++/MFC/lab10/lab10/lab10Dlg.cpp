// lab10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab10.h"
#include "lab10Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Clab10Dlg dialog




Clab10Dlg::Clab10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clab10Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_EXIT, &Clab10Dlg::OnFileExit)
	ON_COMMAND(ID_FILE_OPEN32771, &Clab10Dlg::OnFileOpen32771)
END_MESSAGE_MAP()


// Clab10Dlg message handlers

BOOL Clab10Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Clab10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
			//Если открыт bmp файл
			if(hbm)
			{
				CClientDC dc(this);
			//Получить указатель на DC.
				HDC hdc=::GetDC(m_hWnd);
				HDC hdcBits=::CreateCompatibleDC(hdc);
			//Выбрать объект
				SelectObject(hdcBits,hbm);
			//Закрасить клиентскую облаcть черным цветом
				CRect wdRect;
				GetClientRect(&wdRect);
				CBrush brush;
				brush.CreateSolidBrush(RGB(0,0,0));
				dc.FillRect(&wdRect,&brush);
			//Вывести изображение
				BitBlt(hdc, 0, 0, bm.bmWidth,bm.bmHeight,hdcBits,0,0, SRCCOPY);
			//Удалить DC
				DeleteDC(hdcBits);
				::ReleaseDC(m_hWnd,hdc);
			}

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Clab10Dlg::OnFileExit()
{
	// TODO: Add your command handler code here
	OnOK();
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

char * unicode_to_1251(wchar_t * unicode_string)
{
	int err;
	char * res;
	int res_len = WideCharToMultiByte(
		1251,				// Code page
		0,					// Default replacement of illegal chars
		unicode_string,		// Multibyte characters string
		-1,					// Number of unicode chars is not known
		NULL,				// No buffer yet, allocate it later
		0,					// No buffer
		NULL,				// Use system default
		NULL				// We are not interested whether the default char was used
		);
	if (res_len == 0) return NULL;
	res = (char*)calloc(sizeof(char), res_len);
	if (res == NULL) return NULL;
	err = WideCharToMultiByte(
		1251,				// Code page
		0,					// Default replacement of illegal chars
		unicode_string,		// Multibyte characters string
		-1,					// Number of unicode chars is not known
		res,				// Output buffer
		res_len,			// buffer size
		NULL,				// Use system default
		NULL				// We are not interested whether the default char was used
		);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

HANDLE Clab10Dlg::OpenDIB(LPWSTR szFile)
{
    HFILE               fh;
    BITMAPINFOHEADER    bi;
    LPBITMAPINFOHEADER  lpbi;
    DWORD               dwLen = 0;
    DWORD               dwBits;
    HANDLE              hdib;
    HANDLE              h;
    OFSTRUCT            of;
	char * new_szFile = unicode_to_1251(szFile);
    fh = OpenFile(new_szFile, &of, (UINT)OF_READ);
	if (fh == -1){
		MessageBox(L"Can't open file");
        return NULL;
	}
    hdib = ReadDibBitmapInfo(fh);
    if (!hdib)
        return NULL;
    DibInfo(hdib,&bi);
    dwBits = bi.biSizeImage;
    dwLen  = bi.biSize + (DWORD)PaletteSize(&bi) + dwBits;
    h = GlobalReAlloc(hdib, dwLen, GHND);
    if (!h){
        GlobalFree(hdib);
        hdib = NULL;
    }
    else hdib = h;
    if (hdib){
        lpbi = (tagBITMAPINFOHEADER *)GlobalLock(hdib);
        lread(fh, (LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi), dwBits);
        GlobalUnlock(hdib);
    }
    _lclose(fh);
    return hdib;
}

WORD Clab10Dlg::PaletteSize(VOID FAR * pv)
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;
    lpbi      = (LPBITMAPINFOHEADER)pv;
    NumColors = DibNumColors(lpbi);
    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return (WORD)(NumColors * sizeof(RGBTRIPLE));
    else return (WORD)(NumColors * sizeof(RGBQUAD));
}

HANDLE Clab10Dlg::ReadDibBitmapInfo(INT fh)
{
    DWORD     off;
    HANDLE    hbi = NULL;
    INT       size;
    INT       i;
    WORD      nNumColors;
    RGBQUAD FAR       *pRgb;
    BITMAPINFOHEADER   bi;
    BITMAPCOREHEADER   bc;
    LPBITMAPINFOHEADER lpbi;
    BITMAPFILEHEADER   bf;
    DWORD              dwWidth = 0;
    DWORD              dwHeight = 0;
    WORD               wPlanes, wBitCount;
    if (fh == -1) return NULL;

#ifdef FIXDWORDALIGNMENT
    /* Reset file pointer and read file header */
    off = _llseek(fh, 0L, (UINT)SEEK_CUR);
    if ((SIZEOF_BITMAPFILEHEADER_PACKED)  != _lread(fh, (LPSTR)&bf, (UINT)sizeof (SIZEOF_BITMAPFILEHEADER_PACKED)))
        return FALSE;
#else 
	ReadBitMapFileHeaderandConvertToDwordAlign(fh, &bf, &off);
#endif

    if (!ISDIB (bf.bfType)) {   
        bf.bfOffBits = 0L;               
        _llseek(fh, off, (UINT)SEEK_SET);
    }
    if (sizeof (bi) != _lread(fh, (LPSTR)&bi, (UINT)sizeof(bi)))
        return FALSE;
    nNumColors = DibNumColors (&bi);
    switch (size = (INT)bi.biSize){
        case sizeof (BITMAPINFOHEADER):
            break;
        case sizeof (BITMAPCOREHEADER):
            bc = *(BITMAPCOREHEADER*)&bi;
            dwWidth   = (DWORD)bc.bcWidth;
            dwHeight  = (DWORD)bc.bcHeight;
            wPlanes   = bc.bcPlanes;
            wBitCount = bc.bcBitCount;
			bi.biSize				= sizeof(BITMAPINFOHEADER);
            bi.biWidth              = dwWidth;
            bi.biHeight             = dwHeight;
            bi.biPlanes             = wPlanes;
            bi.biBitCount           = wBitCount;
            bi.biCompression        = BI_RGB;
            bi.biSizeImage          = 0;
            bi.biXPelsPerMeter      = 0;
            bi.biYPelsPerMeter      = 0;
            bi.biClrUsed            = nNumColors;
            bi.biClrImportant       = nNumColors;
            _llseek(fh, (LONG)sizeof (BITMAPCOREHEADER) - sizeof (BITMAPINFOHEADER), (UINT)SEEK_CUR);
            break;
        default: return NULL;
    }
    if (bi.biSizeImage == 0){
        bi.biSizeImage = WIDTHBYTES ((DWORD)bi.biWidth * bi.biBitCount)
                         * bi.biHeight;
    }
    if (bi.biClrUsed == 0) bi.biClrUsed = DibNumColors(&bi);
    hbi = GlobalAlloc (GHND, (LONG)bi.biSize + nNumColors * sizeof(RGBQUAD));
    if (!hbi) return NULL;
    lpbi = (tagBITMAPINFOHEADER *)GlobalLock (hbi);
    *lpbi = bi;
    pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + bi.biSize);
    if (nNumColors){
        if (size == sizeof(BITMAPCOREHEADER)){
            _lread(fh, (LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBTRIPLE));
            for (i = nNumColors - 1; i >= 0; i--){
                RGBQUAD rgb;
                rgb.rgbRed      = ((RGBTRIPLE FAR *)pRgb)[i].rgbtRed;
                rgb.rgbBlue     = ((RGBTRIPLE FAR *)pRgb)[i].rgbtBlue;
                rgb.rgbGreen    = ((RGBTRIPLE FAR *)pRgb)[i].rgbtGreen;
                rgb.rgbReserved = (BYTE)0;
                pRgb[i] = rgb;
            }
        }
        else _lread(fh, (LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBQUAD));
    }
    if (bf.bfOffBits != 0L){
        _llseek(fh, off + bf.bfOffBits, (UINT)SEEK_SET);
        }
    GlobalUnlock(hbi);
    return hbi;
}

BOOL Clab10Dlg::DibInfo(HANDLE hbi, LPBITMAPINFOHEADER lpbi)
{
    if (hbi){
        *lpbi = *(LPBITMAPINFOHEADER)GlobalLock (hbi);
        if (lpbi->biSize != sizeof (BITMAPCOREHEADER)){
            if (lpbi->biSizeImage == 0L)
				lpbi->biSizeImage = WIDTHBYTES(lpbi->biWidth*lpbi->biBitCount) * lpbi->biHeight;
            if (lpbi->biClrUsed == 0L)
				lpbi->biClrUsed = DibNumColors (lpbi);
    }
        GlobalUnlock (hbi);
        return TRUE;
    }
    return FALSE;
}

DWORD PASCAL Clab10Dlg::lread(INT fh, VOID FAR *pv, DWORD ul)
{
    DWORD ulT = ul;
    BYTE *hp = (unsigned char *)pv;
    while (ul > (DWORD)MAXREAD) {
        if (_lread(fh, (LPSTR)hp, (UINT)MAXREAD) != MAXREAD) return 0;
        ul -= MAXREAD;
        hp += MAXREAD;
    }
    if (_lread(fh, (LPSTR)hp, (UINT)ul) != (UINT)ul) return 0;
    return ulT;
}

VOID Clab10Dlg::ReadBitMapFileHeaderandConvertToDwordAlign(HFILE fh, LPBITMAPFILEHEADER pbf, LPDWORD lpdwoff)
{
        DWORD off;
        off = _llseek(fh, 0L, (UINT) SEEK_CUR);
        *lpdwoff = off;
        _lread(fh, (LPSTR) &pbf->bfType, sizeof(WORD));
        _lread(fh, (LPSTR) &pbf->bfSize, sizeof(DWORD) * 3);
}

WORD Clab10Dlg::DibNumColors(VOID FAR * pv)
{
    INT                 bits;
    LPBITMAPINFOHEADER  lpbi;
    LPBITMAPCOREHEADER  lpbc;
    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else bits = lpbc->bcBitCount;
    switch (bits){
        case 1: return 2;
        case 4: return 16;
        case 8: return 256;
        default: return 0;
    }
}

HBITMAP Clab10Dlg::BitmapFromDib(HANDLE hdib, HPALETTE hpal)
{
    LPBITMAPINFOHEADER  lpbi;
    HPALETTE            hpalT;
    HDC                 hdc;
    HBITMAP             hbm;
    StartWait();
    if (!hdib) return NULL;
    lpbi = (tagBITMAPINFOHEADER *)GlobalLock(hdib);
    if (!lpbi) return NULL;
	hdc = ::GetDC(NULL);
    if (hpal){
        hpalT = SelectPalette(hdc,hpal,FALSE);
        RealizePalette(hdc);
    }
    hbm = CreateDIBitmap(hdc,
                (LPBITMAPINFOHEADER)lpbi,
                (LONG)CBM_INIT,
                (LPSTR)lpbi + lpbi->biSize + PaletteSize(lpbi),
                (LPBITMAPINFO)lpbi,
                DIB_RGB_COLORS );
    if (hpal) SelectPalette(hdc,hpalT,FALSE);
	::ReleaseDC(NULL,hdc);
    GlobalUnlock(hdib);
    EndWait();
    return hbm;
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void Clab10Dlg::OnFileOpen32771()
{
	// TODO: Add your command handler code here
	//Заголовок и путь к файлу
		wchar_t FileName[500];
		wchar_t FileTitle[100];
		FileName[0]='\0';
	//Создать объект диалогового окна
		CFileDialog file(TRUE);
	//Уставновить аттрибуты диалогового окна
		file.m_ofn.lpstrFilter=TEXT("Bitmap picture files *.bmp\0*.bmp\0All Files *.*\0*.*\0\0");
		file.m_ofn.lpstrFileTitle=FileTitle;
		file.m_ofn.lpstrFile=FileName;
		file.m_ofn.lpstrTitle=TEXT("Open BMP File");
	//Вывести диалоговое окно
		file.DoModal();
	//Если ничего не выбранно, то вернуться
		if (FileName[0]=='\0')return;
	//Изменить заголовок окна на имя файла
		SetWindowText(FileTitle);
	//Получить указатель на объект в памяти
		HANDLE hdibCurrent1 = OpenDIB(FileName);
		hbm=0;
	//Получить указатель на изображение
		hbm=BitmapFromDib(hdibCurrent1,0);
	//Записать параметры изображения 
		GetObject(hbm,sizeof(BITMAP),(LPSTR)&bm);
	//Получить координаты окна
		CRect wdRect;
		GetClientRect(&wdRect);
		ClientToScreen(&wdRect);
	//Изменить размеры окна
		SetWindowPos(NULL, wdRect.left, wdRect.top, bm.bmWidth+4, bm.bmHeight+42, NULL);
	//Вывести картинку
		OnPaint();
}
