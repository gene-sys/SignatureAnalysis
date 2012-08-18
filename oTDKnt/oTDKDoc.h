// oTDKDoc.h : interface of the COTDKDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include <afxtempl.h>

#if !defined(AFX_OTDKDOC_H__97EA3B8B_9AEB_11D5_BD12_005004230E79__INCLUDED_)
#define AFX_OTDKDOC_H__97EA3B8B_9AEB_11D5_BD12_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COTDKDoc : public COleDocument
{
protected: // create from serialization only
	COTDKDoc();
	DECLARE_DYNCREATE(COTDKDoc)

// Attributes
public:	
	CString strFName;   //имя файла
	CStringArray HeadNode; //массив узлов новых описаний деревьев
	CStringArray glsV; //массив выходов ТЭЗа
	CMapStringToString secondsV; //массив подузлов ТЭЗа
	CArray<COLORREF,COLORREF> bbggrr; //массив цветов выводимых строк
	int iOpenSig; //характеристика состояния нажатия клавиши формирования
														//файлов сигнатур
	int iChkSig; //характеристика состояния нажатия клавиши проверки
														//файлов сигнатур
	int iChkDia; //характеристика состояния нажатия клавиши 
											//диагностической проверки
	int iChkWord; //характеристика состояния нажатия клавиши документа Word
	//структура для записи позиций размещения сигнатур в файлах сигнатур
	int iCount; // количество тестов
	// позиции сигнатур в тестовых файлах
	struct stPos {
		DWORD dwPos1;
		DWORD dwPos2;
		DWORD dwPos3;
	}stPos;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COTDKDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL bClose; // признак закрытия файла дерева
	// получить позицию сигнатуры в тестовом файле
	DWORD gGetPosString(DWORD StartPos, CString csFF, CStdioFile* Fl);
	void RemovecsaItem(int x); //удаляет строку из массива выводных текстовых строк
	CString GetcsaItem(int index); //выдает строку из массива выводных текстовых строк
	int GetcsaSize(); //размер массива выводимых текстовых строк
	void AddString(CString s); //добавить строку в массив выводимых текстовых строк
	int GetArrSize(); //получить размер массива выходов ТЭЗов
		//выдает значение из массива выходов ТЭЗа согласно переданному индексу
	CString GetItemValue(UINT index); 
	void OnOpen(); // открытие файла дерева
	void SetString(int x, CString s, BOOL bTF); //установить строку для вывода в массив выводных строк
	CString GetDate(); // выдать строку
	virtual ~COTDKDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void gGetNode();
	void gMesNode(int cnt);
	CString csDate; //выводимая строка в текущий момент
	CString strFileName;  // имя открытого файла дерева
	CStringArray csaDate; //массив собственно выводимых строк
	//{{AFX_MSG(COTDKDoc)
	afx_msg void OnMakesig();
	afx_msg void OnUpdateMakesig(CCmdUI* pCmdUI);
	afx_msg void OnWord();
	afx_msg void OnUpdateWord(CCmdUI* pCmdUI);
	afx_msg void OnChksig();
	afx_msg void OnUpdateChksig(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDiap(CCmdUI* pCmdUI);
	afx_msg void OnDiap();
	afx_msg void OnCLOSEFILE();
	afx_msg void OnFindnode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL gRecTRW(int previndent, CString sLineKey, CArchive* ar);
	void gVlNode(char Perex[50], CString csOpa);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTDKDOC_H__97EA3B8B_9AEB_11D5_BD12_005004230E79__INCLUDED_)
