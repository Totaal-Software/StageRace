// LINKE SOEP HIERONDER

// Internal user defined messages
#define WM_USER_KEY_LOCKED					WM_USER+1
#define WM_USER_KEY_FREE					WM_USER+2

#define WM_USER_ACTIVEDOC_DOCOPEN			WM_USER+3
#define WM_USER_ACTIVEDOC_DOCCLOSE			WM_USER+4
#define WM_USER_ACTIVEDOC_DOCSELECT			WM_USER+5

#define WM_USER_MESSAGINGACTION				WM_USER+6

#define WM_USER_DRAGGEDEVENTITEM			WM_USER+7

#define WM_USER_GENERATE_PROGRESS_SET		WM_USER+8
#define WM_USER_GENERATE_PROGRESS_INCREMENT	WM_USER+9
#define WM_USER_GENERATE_PROGRESS_FINISH	WM_USER+10

#define WM_USER_UPDATEALLVIEWS				WM_USER+11

#define WM_USER_LOADSTR						WM_USER+12
#define WM_USER_POPULATELISTBOX				WM_USER+13

#define WM_USER_GENERATE					WM_USER+14

#define WM_USER_ADDFILETOMONITOR			WM_USER+15

#define WM_USER_COM_OPERATORMESSAGE			WM_USER+16

#pragma message( "This is the FUTURE version" )


#if defined(MAIN_INCLUDE_FILE_STAGERACE)
#pragma message( "Main include file ALREADY included" )
#endif

#if !defined(MAIN_INCLUDE_FILE_STAGERACE)
#define MAIN_INCLUDE_FILE_STAGERACE

// STAGERACE INDEPENDENT (EXTERNALLY OBTAINED?) CLASSES
#include "SubEdit1.h"
#include "Help.h"
#include "webbrowser2.h"
#include "Hyperlink.h"
#include "TransparentImage.h"
#include "AW_CMultiViewSplitter.h"
#include "MDIClient.h"
#include "cdxCDynamicDialog.h"
#include "cdxCDynamicPropSheet.h"
#include "ChildFrameExclusive.h"
#include "Hasp.h"
#include "Haspconf.h"
#include "ColorStaticST.h"
#include "OptionsPanel.h"
#include "StatusControl.h"
#include "StatusStatic.h"
#include "StatusCombo.h"
#include "StatusProgress.h"
#include "FileDialogWithMemory.h"
#include "FileDialogImport.h"
#include "TipDlg.h"
#include "SRRegKey.h"
#include "SimpleCrypt.h"
#include "StaticWebBrowser2.h"

#include "DocManagerEx.h"

// RESOURCE IDENTIFIERS INCLUDE
#include "resource.h"

// STAGERACE INCLUDES

	#include <WinCrypt.h>

	// Independent various
	#include "ExeChecksum.h"
	#include "StageCalc.h"
	#include "StageDistance.h"
	#include "StageSpeed.h"
	#include "Time.h"
	#include "mEdit.h"
	#include "TimeEdit.h"

	#include "HaspTotaal.h"
	#include "SplitterWndFixed.h"
	#include "SplitterWndHidable.h"
	#include "SizablePropertySheet.h"
	#include "MultiLanguage.h"
	#include "StageRaceWnd.h"
	#include "UpdateViewHint.h"
	#include "License.h"
	#include "StatusGenerate.h"

	// Independent views
	#include "FormViewDetailsEmpty.h"

	// Independent dialogs
	#include "OptionsDlg.h"
	#include "TTOrderOptionsDlg.h"
	#include "ImportPreview.h"
	#include "CheckImportFile.h"
	#include "MsgBoxBeforePaste.h"
	#include "MsgBoxHardwareKey.h"
	#include "MsgBoxIndexHtml.h"
	#include "GetPwd.h"
	#include "ReportDlg.h"
	#include "DlgInterval.h"
	#include "DlgInsertItemInCommunique.h"
	#include "DlgNewParagraphTitle.h"
	#include "DlgCleanupCompetitors.h"
	#include "DlgAutonumberCommuniques.h"
	#include "DlgArrivalInsertPositions.h"

	// About dialogs
	#include "AboutDlg.h"
	#include "Credits.h"
	#include "StartScreen.h"

	// After MultiLanguage.h
	#include "GeneralFunctions.h"

	// Event items
	class CStageRaceDoc;
	#include "EventItem.h"
	#include "DlgEventItemSelection.h"

	// Active doc thingies
	#include "StatusActiveDoc.h"
	#include "ActiveDocTracker.h"
	#include "ListViewActiveDoc.h"

	// After independent status bar classes
	// and after StatusActiveDoc
	#include "StageRaceStatusBar.h"

	// StaNo objects
	class CEditTeam;
	#include "Team.h"

	#include "StaNoObject.h"
	class CCorrection;
	class CClassification;
	#include "Arrival.h"
	class CEditCompetitor;
	#include "Competitor.h"
	#include "SignOut.h"
	#include "Correction.h"

	// StaNo object lists
	#include "StaNoObjectList.h"
	#include "SignOutList.h"
	class CArrivalList;
	#include "CorrectionList.h"
	#include "ArrivalList.h"
	#include "CompetitorList.h"

	// Arrival lists controls
	#include "StaNoListCtrl.h"
	#include "ArrivalListCtrl.h"
	#include "SignOutListCtrl.h"
	#include "StaNoEdit.h"

	class CClassification;
	#include "DistributedClassification.h"
	#include "AvailableList.h"

	// Arrival lists
	#include "AllListPages.h"
	#include "AllListArrivals.h"
	#include "ListArrival.h"
	#include "ListCorrection.h"
	#include "ListSignOuts.h"
	#include "ListTimeTrialArrival.h"
	#include "ListTimeTrialArrivalNet.h"
	#include "ListTimeTrialOrder.h"

	// After Competitor
	#include "MaskApplyDlg.h"

	// Settings
	#include "SettingsPanel.h"
	
	class CPageSettings;
	#include "Settings.h"
	#include "SettingsGeneral.h"
	#include "SettingsRanking.h"
	#include "SettingsPublication.h"
	#include "SettingsHTML.h"
	#include "SettingsUpload.h"
	#include "SettingsAccess.h"

	#include "PageSettings.h"
	#include "PageSettingsGeneral.h"
	#include "PageSettingsRanking.h"
	#include "PageSettingsPublication.h"
	#include "PageSettingsHTML.h"
	#include "PageSettingsUpload.h"
	#include "PageSettingsAccess.h"

	#include "AllSettings.h"

	#include "ToolBarWithProfilePicker.h"
	#include "DlgProfileName.h"
	#include "DlgProfilePicker.h"

	// Before other event items
	#include "Id.h"
	#include "IdView.h"
	#include "IdUseList.h"

	// Before fullstage/halfstage
	class CEditCommunique;
	class CCommunique;
	#include "Communique.h"
	#include "PreviewCommunique.h"

	class CHalfStage;
	class CFullStage;
	#include "FullStageTrialDat.h"
	#include "HalfStageTrialDat.h"
	#include "BonusDat.h"
	#include "MountainDat.h"
	#include "PointsDat.h"
	#include "MostAggressiveDat.h"
	#include "SprintDat.h"

	// Classification generators
	#include "Classification.h"
	#include "TeamClassification.h"
	#include "SprintClassification.h"
	#include "PointsClassification.h"
	#include "ClimbsClassification.h"
	#include "MostAggressiveClassification.h"

	// Now fullstage/halfstage
	#include "HalfStage.h"
	#include "FullStage.h"

	// Dependent views
	// Must before child frame
	#include "PresentationView.h"
	#include "StaticPresentationView.h"
	#include "ListViewCompetitorsTeams.h"
	#include "ListViewCompetitors.h"
	#include "ListViewTeams.h"
	#include "TreeViewMain.h"

	#include "ChildFrame.h"
	#include "MainFrm.h"

	// Output
	#include "Publication.h"
	#include "HtmlDoc.h"
	#include "TextOutput.h"

	// Some edit dialogs
	#include "EditCommunique.h"
	#include "EditCompetitor.h"
	#include "EditTeam.h"

	// And some important one's at the end
	#include "StageRace.h"
	#include "StageRaceDoc.h"

	// StageRace COM server classes
	#include "StageRace_i.h"
	#include "StageRaceServer (COM).h"
	#include "StageRaceDoc (COM).h"
	#include "SRHalfStage (COM).h"

//

#endif