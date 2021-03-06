// MultiLanguage.h: interface for the CMultiLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILANGUAGE_H__75009714_033B_424F_B99F_2BBD945B7B0D__INCLUDED_)
#define AFX_MULTILANGUAGE_H__75009714_033B_424F_B99F_2BBD945B7B0D__INCLUDED_

#include <iostream> 
#include <fstream> 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMultiLanguage : public CObject  
{
public:
	typedef union LANGUAGE
	{
		char ac[3];
		DWORD n;
	};
	typedef struct LOADSTR
	{
		LANGUAGE lang;
		TCHAR* id;
		HANDLE hSemaphore;
	};
	typedef class MyArray : public CArray<LANGUAGE,LANGUAGE&>
	{
	public:
		MyArray &operator =(const MyArray& s)
		{
			this->RemoveAll();
			for(int i=0; i<s.GetSize(); i++)
			{
				const LANGUAGE & element = s.GetAt(i);
				this->Add((LANGUAGE &)element);
			}
			return *this;
		}
	};
	typedef MyArray REQUIREDLANGUAGES;

	void PopulateListBox( CComboBox* pComboBox );
	CString AssembleStr(TCHAR czID[],TCHAR czCement[], const REQUIREDLANGUAGES* pLang);
	CString LoadStr(TCHAR czID[],CMultiLanguage::LANGUAGE lang);
	CMultiLanguage(HWND hCurrentWnd);
	virtual ~CMultiLanguage();

protected:
	static UINT ThreadFunction(LPVOID pParam);
	CWinThread* m_pWorker;
};

#endif // !defined(AFX_MULTILANGUAGE_H__75009714_033B_424F_B99F_2BBD945B7B0D__INCLUDED_)
