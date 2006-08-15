///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: StageRaceDoc.h
// Description: Interface file for the CStageRaceDoc class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
//
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAGERACEDOC_H__552C752C_B87F_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_STAGERACEDOC_H__552C752C_B87F_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum COMPETITOR_FIELD
{
	CF_STANO,
	CF_NAME,
	CF_TEAM,
	CF_COUNTRY,
	CF_UCI,
	CF_LICENSE,
	CF_CATEGORY
};
enum TEAM_FIELD
{
	TF_CODE,
	TF_NAME,
	TF_MANAGER,
	TF_COUNTRY
};

class CStageRaceDoc : public CDocument
{
	DECLARE_DYNCREATE( CStageRaceDoc )

public:
	enum PUBLI_WHAT
	{
		PWH_ALL,
		PWH_NOTHING,
		PWH_THIS
	};
	enum CONFIG_TYPE
	{
		CT_HALFSTAGE,
		CT_BONUS,
		CT_SPRINT,
		CT_POINTS,
		CT_CLIMB,
		CT_MOSTAGGRESSIVE
	};
protected:
	enum GENERATE_TYPE
	{
		GTY_CLASS=1,
		GTY_COMMUNIQUE=2,
		GTY_COMPETITORS=4,
		GTY_CROSSOUT=8,
		GTY_ORDER=16,
		GTY_SIGNIN=32,
		GTY_TOC=64
	};
	struct GENERATE
	{
		GENERATE_TYPE m_gt;
		CStageRaceDoc* m_pDoc;
		int m_nHalfStage;
		int m_nFullStage;
		PUBLI_WHAT m_what;
		unsigned short m_profile;
	};

	// Create from serialization only; therefore protected
	CStageRaceDoc();
	virtual ~CStageRaceDoc();

	//{{AFX_MSG(CStageRaceDoc)
	afx_msg void OnFileUpload();
	afx_msg void OnUpdateFileUpload(CCmdUI* pCmdUI);
	afx_msg void OnToolsExportscanovision();
	afx_msg void OnToolsExportfinishlynx();
	afx_msg void OnUpdateToolsExportscanovision(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsExportfinishlynx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenerateToc(CCmdUI* pCmdUI);
	afx_msg void OnViewEventItemSelection();
	afx_msg void OnUpdateViewEventItemSelection(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenerateAutomatically(CCmdUI* pCmdUI);
	afx_msg void OnGenerateCrossout();
	afx_msg void OnGenerateSignin();
	afx_msg void OnGenerateCommuniques();
	afx_msg void OnGenerateAutomatically();
	afx_msg void OnGenerateAll();
	afx_msg void OnGenerateToc();
	afx_msg void OnGenerateAllstages();
	afx_msg void OnGenerateCompetitors();
	afx_msg void OnUpdateConfigureAll(CCmdUI* pCmdUI);
	afx_msg void OnConfigureAllBonuses();
	afx_msg void OnConfigureAllClimbcl();
	afx_msg void OnConfigureAllHalfstage();
	afx_msg void OnConfigureAllPointscl();
	afx_msg void OnConfigureAllSprintcl();
	afx_msg void OnConfigureProfilepicker();
	afx_msg void OnViewMonitormode();
	afx_msg void OnUpdateViewMonitormode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewAddfiletomonitor(CCmdUI* pCmdUI);
	afx_msg void OnViewAddfiletomonitor();
	afx_msg void OnToolsServerProcesspending();
	afx_msg void OnToolsServerSendteamsCode();
	afx_msg void OnUpdateToolsServerSendteamsCode(CCmdUI* pCmdUI);
	afx_msg void OnToolsServerSendteamsName();
	afx_msg void OnUpdateToolsServerSendteamsName(CCmdUI* pCmdUI);
	afx_msg void OnEditAutonumber();
	afx_msg void OnConfigureAllMostaggressivecl();
	afx_msg void OnUpdateEditAutonumber(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageRaceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& objAr);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

private:
	// COMPETITORS
	CCompetitorList m_competitors;
	// SPARE COMPETITORS
	CMapPtrToPtr m_spareCompetitors;
	// TEAMS
	CTypedPtrMap<CMapStringToOb, CString, CTeam*> m_teams;
	// STAGES
	CList<CFullStage, CFullStage&> m_fullStages;
	// Version no. for serialisation
	int GetHardcodedFileVersion() const;
	int m_nFileVersion;
public:
	// SPARE COMPETITORS
	// Spare competitors list functions
	void				SpareCompetitorsUpdate( const CCompetitor* pComp, COMPETITOR_FIELD f, CString val );
	const CCompetitor*	SpareCompetitorsIterate( POSITION& nPos ) const;
	POSITION			SpareCompetitorsGetStartPosition() const;
	void				SpareCompetitorsEdit( const CCompetitor* pComp );
	bool				SpareCompetitorsExist( const CCompetitor* pComp ) const;
	bool				SpareCompetitorsDelete( const CCompetitor* pComp );
	int					SpareCompetitorsCount() const;
	void				SpareCompetitorsChangeStaNo( const CCompetitor* pComp, WORD nNewStaNo );
public:
	// COMPETITORS
	// Competitor list functions
	void				CompetitorsCleanup();
	bool				CompetitorsCleanupHelper(CCompetitor*, CLEANUPCOMPETITORS);
	void				CompetitorsUpdate( WORD nStaNo, COMPETITOR_FIELD f, CString val );
	void				CompetitorsChangeStaNo( WORD nStaNo, WORD nNewStaNo );
	CCompetitor			CompetitorsGet( int nStaNo ) const;
	bool				CompetitorsExist( int nStaNo ) const;
	bool				CompetitorsDelete( int nStaNo );
	int					CompetitorsMaxStaNo() const;
	void				CompetitorsNew(BOOL bRepeatedly);
	void				CompetitorsApplyMask();
	int					CompetitorsCount() const;
	bool				CompetitorsIterateSorted( DWORD &nState, CCompetitor& aComp ) const;
	void				CompetitorsEdit( int nStaNo );
	void				CompetitorsSetMask( int nStaNo, char nMask, bool bOn = TRUE, bool bSuppressFormalities = TRUE, bool bSuppressLocks = FALSE );
	void				CompetitorsCut( CArray<WORD,WORD>* pStaNos, CPtrArray* pComps );
	void				CompetitorsCopy( CArray<WORD,WORD>* pStaNos, CPtrArray* pComps );
	void				CompetitorsPaste(bool bWithStaNos);
	BOOL				CompetitorsCanPaste() const;
	void				CompetitorsSwap(WORD nStaNo1, CCompetitor* pComp2);
	void				CompetitorsSwap(CCompetitor* pComp1, WORD nStaNo2);
	void				CompetitorsSwap(WORD nStaNo1, WORD nStaNo2);
protected:				
	bool				CompetitorsInUse( int nStaNo );

public:
	// TEAMS
	// Team list functions
	bool				TeamsCleanupHelper(CTeam* pComp, CLEANUPCOMPETITORS clc);
	void				TeamsUpdate( CTeam* pTeam, TEAM_FIELD f, CString val );
	const CTeam*		TeamsGet(CString sCode) const;
	bool				TeamsExist(CString sCode) const;
	bool				TeamsDelete( CTeam* pTeam );
	void				TeamsNew(BOOL bRepeatedly=FALSE, CTeam** ppTeam=NULL, CString* pcCodeSuggestion=NULL, CString* pcNameSuggestion=NULL, bool bSuppressEdit=false);
	int					TeamsCount() const;
	int					TeamsCountUsed() const;
	void				TeamsIterate( POSITION& nPos, const CTeam*& rpTeam ) const;
	POSITION			TeamsGetStartPosition() const;
	void				TeamsEdit( CTeam* pTeam );
	void				TeamsCut( CArray<CTeam*,CTeam*>* pTeams );
	void				TeamsCopy( CArray<CTeam*,CTeam*>* pTeams );
	void				TeamsPaste();
protected:				
	bool				TeamsInUse( CTeam* pTeam ) const;

public:
	// STAGES
	// Stages list functions
	CFullStage*			StagesGet(int nIndex);
	CHalfStage*			StagesGet(int nFSIndex,int nHSIndex);
	CHalfStage*			StagesGetPrev(int nFSIndex,int nHSIndex);
	CHalfStage*			StagesGetNext(int nFSIndex, int nHSIndex);
	void				StagesDelete(int nFSIndex, int nHSIndex);
	void				StagesDelete(int nIndex);
	int					StagesFullCount() const;
	int					StagesHalfCount(int nParentFS);
	int					StagesCountTo(int nFS, int nHS);
	int					StagesHalfCount();
	void				StagesFullNew();
	void				StagesHalfNew(int nParentFS);
	void				StagesFullEdit(int nFS);
	void				StagesHalfEdit(int nParentFS, int nHS);
	void				StagesHalfEdit(CONFIG_TYPE ct);
	const CAvailableList*
						StagesGetAvailables(int nFSIndex, int nHSIndex);
protected:
	void				StagesFullNew(CFullStage* pNewOne);
	void				StagesHalfNew(int nParentFS, CHalfStage* pNewOne);
public:
	// Additional configuration
	bool TestAccess();
	void Settings();

public:
	// COMMUNIQUÉS
	void				CommuniqueEdit(int nFS=0, int nHS=0);
	void				CommuniqueDelete(int nFS=0, int nHS=0);
	CCommunique*		CommuniqueGet(int nFS, int nHS);

protected:
	// REFERENCE COUNTING
	long m_references;
public:
	bool m_bLongTeamNamesForCOM;
	void Release();
	void AddRef();

protected:
	// PUBLICATION GENERATION
	bool m_bGenerateAutomatically;
	void GenerateClass_Real(PUBLI_WHAT what=PWH_ALL, int nFS=-1, int nHS=-1);
	void GenerateCompetitors_Real();
	void GenerateCommunique_Real(int nFS, int nHS);
	void GenerateCrossout_Real();
	void GenerateOrder_Real(int nFS, int nHS);
	void GenerateToc_Real();
	void GenerateSignin_Real();

	void GenerateOrder_Single_Real(int nFS, int nHS);
	void GenerateCommunique_Single_Real(int nFS, int nHS);

	static UINT GenerateThread(LPVOID pParam);
	void UpdateAllViewsThreaded( CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL );
	static CWinThread* m_pGenerator;
	HANDLE m_hGenerateSemaphore_ChangeToDoc;
	HANDLE m_hGenerateSemaphore_KeepDocOpen;

	void GenerateSetProgress();

public:
	void Unlock();
	void Lock();
	static void Init();
	static void Exit();

	void GenerateAll();
	void GenerateAllstages();
	void GenerateClass(PUBLI_WHAT what=PWH_ALL, int nFS=-1, int nHS=-1);
	void GenerateCommunique(int nFS, int nHS);
	void GenerateCompetitors();
	void GenerateCrossout();
	void GenerateOrder(int nFS, int nHS);
	void GenerateSignin();
	void GenerateToc();

	CClassification * GenerateUpTo(int nSubjFS, int nSubjHS, CClassification* pClass=NULL, CTeamClassification* pTeam=NULL);
	void Upload() const;
	CFtpConnection* UploadPre() const;
	void UploadPost(CFtpConnection* pFtpConnection) const;

	// EXPORT
	void ExportScanovision();
	void ExportFinishlynx();
	void ExportTTWare(int nFS, int nHS);
	void ExportChronx(int nFS, int nHS);
	void ExportOptic(int nFS, int nHS);
protected:
	void ExportHelperCompetitors(CTextOutput *pOutput, int nFS, int nHS);

public:
	void InputStartingOrder( int nFS, int nHS );
	void InputSignOuts( int nFS, int nHS );
	void InputRanking( int nFS, int nHS, char nType );
	void InputFunctionRemovegaps( int nFS, int nHS, char nType );
	void InputFunctionRemove1xseconds( int nFS, int nHS, char nType );
	void InputFunctionImport( int nFS, int nHS, char nType );
	void InputFunctionGroupt(int nFS, int nHS, char nType, short nSecs );
	void InputFunctionCheck( int nFS, int nHS );

	bool InputArrivalSet(int nFS, int nHS, WORD nStaNo, WORD nRank, DWORD nUnits);
	bool InputArrivalSetByTime(int nFS, int nHS, WORD nStaNo, DWORD nUnits);
	bool InputArrivalReset(int nFS, int nHS, WORD nStaNo);
	void InputOnTimingIdle(int nFS, int nHS);

	// IDs
	CId m_idTeams;
	CId m_idCompetitors;
	CIdUseList* m_pListID;

	// VARIOUS
	CCommunique m_communique;
	bool m_IndexTocFlag;

protected:
	TCHAR CompetitorsPasteGetChar( char* pStr, int width );
	virtual void PreCloseFrame( CFrameWnd* pFrame );
	CDlgEventItemSelection* m_pEventItemSelection;

public:
	int GetFileVersion();
	CWnd* GetEventItemSelectionDlg();
	CString FilesTitle() const;
	CString FilesPath() const;
	// "filename.str *" SUPPORT
	void SetModifiedFlag();
	CStageRaceApp* m_pApp;
	CString GetTitle() const;

// MONITOR MODE
protected:
	void AutonumberCommuniquesHelp(CId* pId, int nFS, int nHS, TREEITEMS ti);
	void AddFileToMonitor(CString);
	void SetMonitor();
	bool m_bMonitorMode;
	static UINT MonitorThread(LPVOID pParam);
	CWinThread* m_pMonitor;

// SETTINGS
public:
	void AutonumberCommuniques();
	CAllSettings m_allsettings;

#ifdef _DEBUG
	clock_t start;
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGERACEDOC_H__552C752C_B87F_11D2_B376_0040954019F4__INCLUDED_)

