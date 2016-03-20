// lab8Dlg.h : header file
//

#pragma once


// Clab8Dlg dialog
class Clab8Dlg : public CDialog
{
// Construction
public:
	Clab8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB8_DIALOG };

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
private:
	CRect m_Canvas;
	CPoint m_LineEnd;
	CPoint m_LineStart;
	CPoint tmp;
	COLORREF m_PenColor;
	CRect m_PenColorSwatch;
	CPen m_Pen;
	bool m_IsDrawing;
	void DrawShape(bool stretch=false);
public:
	afx_msg void OnBnClickedClearbtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedPencolor();
	int m_PenWidth;
	int m_PenStyle;
	CComboBox m_ShapesCombo;
	CBrush m_Brush;	//Объект кисти
	COLORREF m_BrushColor;	//Цвет заливки
	CRect m_BrushColorSwatch;	//Координаты индикатора цвета
	CRect m_BrushPreviewSwatch;	//Координаты просмотра
	int	m_BrushStyle;	//Стиль закраски
	CListBox m_BrushStyleList;
	afx_msg void OnLbnSelchangeBrushstyle();
	void PaintBrushPreview();
	afx_msg void OnStnClickedBrushcolor();
	CMetaFileDC* m_pMF;
	afx_msg void OnDestroy();
};
