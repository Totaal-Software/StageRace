// StaNoObjectList.h: interface for the CStaNoObjectList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STANOOBJECTLIST_H__9A7B06BE_55CB_4106_9214_642B0635B705__INCLUDED_)
#define AFX_STANOOBJECTLIST_H__9A7B06BE_55CB_4106_9214_642B0635B705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStaNoObjectList : public CObject  
{
	DECLARE_DYNAMIC( CStaNoObjectList )
public:
	void ClearDirty();
	bool IsDirty();
	void Iterate( POSITION& rNextPosition, CStaNoObject& rValue ) const;
	POSITION GetStartPosition() const;
	bool IterateSorted(DWORD &nState, CStaNoObject &objStaNo) const;
	bool Exist(WORD nTest) const;
	void Remove(WORD nKey, bool bSuppressLockWrite=false);
	void RemoveAll();
	void Insert(CStaNoObject &objStaNo);
	WORD GetCount() const;
	CStaNoObjectList();
	virtual ~CStaNoObjectList();
	void UnlockRead() const;
	void LockRead() const;
	void UnlockWrite();
	void LockWrite();
protected:
	bool m_bDirty;
	void Insert( CStaNoObject* pObj );
	CMapWordToOb m_list;
	CMap<WORD,WORD,int,int&> m_StaNoToIndex;
	CArray<WORD,WORD&> m_IndexToStaNo;
	HANDLE m_hWriterMutex;
	HANDLE m_hMutex;
	HANDLE m_hReaderEvent;
	long m_iCounter;
};

#endif // !defined(AFX_STANOOBJECTLIST_H__9A7B06BE_55CB_4106_9214_642B0635B705__INCLUDED_)
