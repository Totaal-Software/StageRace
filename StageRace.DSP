# Microsoft Developer Studio Project File - Name="StageRace" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=StageRace - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StageRace.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StageRace.mak" CFG="StageRace - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StageRace - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StageRace - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StageRace - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /D "NDEBUG" /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib htmlhelp.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map /machine:I386 /out:"StageRace.exe" /libpath:"C:\Program Files\HTML Help Workshop\lib"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=D:\Projects\Non-StageRace\buildinc\Debug\buildinc.exe version.ver stagerace.rc	rc /l 0x809 /fo"Release/StageRace.res" /d "NDEBUG" /d "_AFXDLL" stagerace.rc
PostBuild_Cmds=copy Release\StageRace.tlb StageRace.tlb	"AppendChecksum\release\AppendChecksum.exe" "StageRace.exe"	copy StageRace.exe executable\StageRace.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "StageRace - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /ZI /Od /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /YX"stdafx.h" /FD /c
# SUBTRACT CPP /u
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /D "_DEBUG" /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib version.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map /debug /machine:I386 /out:"StageRace.exe" /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\lib"
# SUBTRACT LINK32 /profile /incremental:no
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=D:\Projects\Non-StageRace\buildinc\Debug\buildinc.exe version.ver stagerace.rc	rc /l 0x809 /fo"Debug/StageRace.res" /d "NDEBUG" /d "_AFXDLL" stagerace.rc
PostBuild_Cmds=copy Debug\StageRace.tlb StageRace.tlb	"AppendChecksum\release\AppendChecksum.exe" "StageRace.exe"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "StageRace - Win32 Release"
# Name "StageRace - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ActiveDocTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\AllListArrivals.cpp
# End Source File
# Begin Source File

SOURCE=.\AllListPages.cpp
# End Source File
# Begin Source File

SOURCE=.\AllSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\Arrival.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrivalList.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrivalListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\AvailableList.cpp
# End Source File
# Begin Source File

SOURCE=.\AW_CMultiViewSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\BonusDat.cpp
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicWndEx.cpp
# End Source File
# Begin Source File

SOURCE=.\cdxCSizeIconCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckImportFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrameExclusive.cpp
# End Source File
# Begin Source File

SOURCE=.\Classification.cpp
# End Source File
# Begin Source File

SOURCE=.\ClimbsClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.cpp
# End Source File
# Begin Source File

SOURCE=.\Communique.cpp
# End Source File
# Begin Source File

SOURCE=.\Competitor.cpp
# End Source File
# Begin Source File

SOURCE=.\CompetitorList.cpp
# End Source File
# Begin Source File

SOURCE=.\Correction.cpp
# End Source File
# Begin Source File

SOURCE=.\CorrectionList.cpp
# End Source File
# Begin Source File

SOURCE=.\Credits.cpp
# End Source File
# Begin Source File

SOURCE=.\DistributedClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgArrivalInsertPositions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutonumberCommuniques.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCleanupCompetitors.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEventItemSelection.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInsertItemInCommunique.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInterval.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewParagraphTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProfileName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProfilePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\DocManagerEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EditCommunique.cpp
# End Source File
# Begin Source File

SOURCE=.\EditCompetitor.cpp
# End Source File
# Begin Source File

SOURCE=.\EditTeam.cpp
# End Source File
# Begin Source File

SOURCE=.\EventItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ExeChecksum.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialogImport.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialogWithMemory.cpp
# End Source File
# Begin Source File

SOURCE=.\FormViewDetailsEmpty.cpp
# End Source File
# Begin Source File

SOURCE=.\FullStage.cpp
# End Source File
# Begin Source File

SOURCE=.\FullStageTrialDat.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\GetPwd.cpp
# End Source File
# Begin Source File

SOURCE=.\HalfStage.cpp
# End Source File
# Begin Source File

SOURCE=.\HalfStageTrialDat.cpp
# End Source File
# Begin Source File

SOURCE=.\HaspTotaal.cpp
# End Source File
# Begin Source File

SOURCE=.\Help.cpp
# End Source File
# Begin Source File

SOURCE=.\HtmlDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Hyperlink.cpp
# End Source File
# Begin Source File

SOURCE=.\Id.cpp
# End Source File
# Begin Source File

SOURCE=.\IdUseList.cpp
# End Source File
# Begin Source File

SOURCE=.\IdView.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\ListArrival.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCorrection.cpp
# End Source File
# Begin Source File

SOURCE=.\ListSignOuts.cpp
# End Source File
# Begin Source File

SOURCE=.\ListTimeTrialArrival.cpp
# End Source File
# Begin Source File

SOURCE=.\ListTimeTrialArrivalNet.cpp
# End Source File
# Begin Source File

SOURCE=.\ListTimeTrialOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\ListViewActiveDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ListViewCompetitors.cpp
# End Source File
# Begin Source File

SOURCE=.\ListViewCompetitorsTeams.cpp
# End Source File
# Begin Source File

SOURCE=.\ListViewTeams.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MaskApplyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MDIClient.cpp
# End Source File
# Begin Source File

SOURCE=.\mEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MostAggressiveClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\MostAggressiveDat.cpp
# End Source File
# Begin Source File

SOURCE=.\MountainDat.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBoxBeforePaste.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBoxHardwareKey.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBoxIndexHtml.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiLanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettingsAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettingsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettingsHTML.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettingsPublication.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettingsRanking.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSettingsUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\PointsClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\PointsDat.cpp
# End Source File
# Begin Source File

SOURCE=.\PresentationTextView.cpp
# End Source File
# Begin Source File

SOURCE=.\PresentationView.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewCommunique.cpp
# End Source File
# Begin Source File

SOURCE=.\Publication.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsHTML.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsPublication.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsRanking.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\SignOut.cpp
# End Source File
# Begin Source File

SOURCE=.\SignOutList.cpp
# End Source File
# Begin Source File

SOURCE=.\SignOutListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleCrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\SizablePropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitterWndFixed.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitterWndHidable.cpp
# End Source File
# Begin Source File

SOURCE=.\SprintClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\SprintDat.cpp
# End Source File
# Begin Source File

SOURCE=".\SRHalfStage (COM).cpp"
# End Source File
# Begin Source File

SOURCE=.\SRRegKey.cpp
# End Source File
# Begin Source File

SOURCE=.\StageCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\StageDistance.cpp
# End Source File
# Begin Source File

SOURCE=.\StageRace.cpp
# End Source File
# Begin Source File

SOURCE=.\StageRace.idl
# ADD MTL /h "StageRace_i.h" /iid "StageRace_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\StageRace.rc
# End Source File
# Begin Source File

SOURCE=".\StageRaceDoc (COM).cpp"
# End Source File
# Begin Source File

SOURCE=.\StageRaceDoc.cpp
# End Source File
# Begin Source File

SOURCE=".\StageRaceServer (COM).cpp"
# End Source File
# Begin Source File

SOURCE=.\StageRaceStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StageRaceWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StageSpeed.cpp
# End Source File
# Begin Source File

SOURCE=.\StaNoEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\StaNoListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StaNoObject.cpp
# End Source File
# Begin Source File

SOURCE=.\StaNoObjectList.cpp
# End Source File
# Begin Source File

SOURCE=.\StartScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticPresentationView.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticWebBrowser2.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusActiveDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusControl.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusGenerate.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SubEdit1.cpp
# End Source File
# Begin Source File

SOURCE=.\Team.cpp
# End Source File
# Begin Source File

SOURCE=.\TeamClassification.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TextOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\Time.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBarWithProfilePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\TransparentImage.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeViewMain.cpp
# End Source File
# Begin Source File

SOURCE=.\TTOrderOptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateViewHint.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# Begin Source File

SOURCE=.\Hasp32b.obj
# End Source File
# Begin Source File

SOURCE=.\Haspms32.obj
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\ActiveDocTracker.h
# End Source File
# Begin Source File

SOURCE=.\AllListArrivals.h
# End Source File
# Begin Source File

SOURCE=.\AllListPages.h
# End Source File
# Begin Source File

SOURCE=.\AllSettings.h
# End Source File
# Begin Source File

SOURCE=.\Arrival.h
# End Source File
# Begin Source File

SOURCE=.\ArrivalList.h
# End Source File
# Begin Source File

SOURCE=.\ArrivalListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\AvailableList.h
# End Source File
# Begin Source File

SOURCE=.\AW_CMultiViewSplitter.h
# End Source File
# Begin Source File

SOURCE=.\BonusDat.h
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicDialog.h
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicWnd.h
# End Source File
# Begin Source File

SOURCE=.\cdxCDynamicWndEx.h
# End Source File
# Begin Source File

SOURCE=.\cdxCSizeIconCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CheckImportFile.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrameExclusive.h
# End Source File
# Begin Source File

SOURCE=.\Classification.h
# End Source File
# Begin Source File

SOURCE=.\ClimbsClassification.h
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.h
# End Source File
# Begin Source File

SOURCE=.\Communique.h
# End Source File
# Begin Source File

SOURCE=.\Competitor.h
# End Source File
# Begin Source File

SOURCE=.\CompetitorList.h
# End Source File
# Begin Source File

SOURCE=.\Correction.h
# End Source File
# Begin Source File

SOURCE=.\CorrectionList.h
# End Source File
# Begin Source File

SOURCE=.\Credits.h
# End Source File
# Begin Source File

SOURCE=.\DistributedClassification.h
# End Source File
# Begin Source File

SOURCE=.\DlgArrivalInsertPositions.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutonumberCommuniques.h
# End Source File
# Begin Source File

SOURCE=.\DlgCleanupCompetitors.h
# End Source File
# Begin Source File

SOURCE=.\DlgEventItemSelection.h
# End Source File
# Begin Source File

SOURCE=.\DlgInsertItemInCommunique.h
# End Source File
# Begin Source File

SOURCE=.\DlgInterval.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewParagraphTitle.h
# End Source File
# Begin Source File

SOURCE=.\DlgProfileName.h
# End Source File
# Begin Source File

SOURCE=.\DlgProfilePicker.h
# End Source File
# Begin Source File

SOURCE=.\DocManagerEx.h
# End Source File
# Begin Source File

SOURCE=.\EditCommunique.h
# End Source File
# Begin Source File

SOURCE=.\EditCompetitor.h
# End Source File
# Begin Source File

SOURCE=.\EditTeam.h
# End Source File
# Begin Source File

SOURCE=.\EventItem.h
# End Source File
# Begin Source File

SOURCE=.\ExeChecksum.h
# End Source File
# Begin Source File

SOURCE=.\FileDialogImport.h
# End Source File
# Begin Source File

SOURCE=.\FileDialogWithMemory.h
# End Source File
# Begin Source File

SOURCE=.\FormViewDetailsEmpty.h
# End Source File
# Begin Source File

SOURCE=.\FullStage.h
# End Source File
# Begin Source File

SOURCE=.\FullStageTrialDat.h
# End Source File
# Begin Source File

SOURCE=.\GeneralFunctions.h
# End Source File
# Begin Source File

SOURCE=.\GetPwd.h
# End Source File
# Begin Source File

SOURCE=.\HalfStage.h
# End Source File
# Begin Source File

SOURCE=.\HalfStageTrialDat.h
# End Source File
# Begin Source File

SOURCE=.\Hasp.h
# End Source File
# Begin Source File

SOURCE=.\Haspconf.h
# End Source File
# Begin Source File

SOURCE=.\HaspTotaal.h
# End Source File
# Begin Source File

SOURCE=.\Help.h
# End Source File
# Begin Source File

SOURCE=.\HtmlDoc.h
# End Source File
# Begin Source File

SOURCE=.\Hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\Id.h
# End Source File
# Begin Source File

SOURCE=.\IdUseList.h
# End Source File
# Begin Source File

SOURCE=.\IdView.h
# End Source File
# Begin Source File

SOURCE=.\ImportPreview.h
# End Source File
# Begin Source File

SOURCE=.\Incl.h
# End Source File
# Begin Source File

SOURCE=.\License.h
# End Source File
# Begin Source File

SOURCE=.\ListArrival.h
# End Source File
# Begin Source File

SOURCE=.\ListCorrection.h
# End Source File
# Begin Source File

SOURCE=.\ListSignOuts.h
# End Source File
# Begin Source File

SOURCE=.\ListTimeTrialArrival.h
# End Source File
# Begin Source File

SOURCE=.\ListTimeTrialArrivalNet.h
# End Source File
# Begin Source File

SOURCE=.\ListTimeTrialOrder.h
# End Source File
# Begin Source File

SOURCE=.\ListViewActiveDoc.h
# End Source File
# Begin Source File

SOURCE=.\ListViewCompetitors.h
# End Source File
# Begin Source File

SOURCE=.\ListViewCompetitorsTeams.h
# End Source File
# Begin Source File

SOURCE=.\ListViewTeams.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MaskApplyDlg.h
# End Source File
# Begin Source File

SOURCE=.\MDIClient.h
# End Source File
# Begin Source File

SOURCE=.\mEdit.h
# End Source File
# Begin Source File

SOURCE=.\MostAggressiveClassification.h
# End Source File
# Begin Source File

SOURCE=.\MostAggressiveDat.h
# End Source File
# Begin Source File

SOURCE=.\MountainDat.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxBeforePaste.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxHardwareKey.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxIndexHtml.h
# End Source File
# Begin Source File

SOURCE=.\MultiLanguage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPanel.h
# End Source File
# Begin Source File

SOURCE=.\PageSettings.h
# End Source File
# Begin Source File

SOURCE=.\PageSettingsAccess.h
# End Source File
# Begin Source File

SOURCE=.\PageSettingsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\PageSettingsHTML.h
# End Source File
# Begin Source File

SOURCE=.\PageSettingsPublication.h
# End Source File
# Begin Source File

SOURCE=.\PageSettingsRanking.h
# End Source File
# Begin Source File

SOURCE=.\PageSettingsUpload.h
# End Source File
# Begin Source File

SOURCE=.\PointsClassification.h
# End Source File
# Begin Source File

SOURCE=.\PointsDat.h
# End Source File
# Begin Source File

SOURCE=.\PresentationTextView.h
# End Source File
# Begin Source File

SOURCE=.\PresentationView.h
# End Source File
# Begin Source File

SOURCE=.\PreviewCommunique.h
# End Source File
# Begin Source File

SOURCE=.\Publication.h
# End Source File
# Begin Source File

SOURCE=.\ReportDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# Begin Source File

SOURCE=.\SettingsAccess.h
# End Source File
# Begin Source File

SOURCE=.\SettingsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\SettingsHTML.h
# End Source File
# Begin Source File

SOURCE=.\SettingsPanel.h
# End Source File
# Begin Source File

SOURCE=.\SettingsPublication.h
# End Source File
# Begin Source File

SOURCE=.\SettingsRanking.h
# End Source File
# Begin Source File

SOURCE=.\SettingsUpload.h
# End Source File
# Begin Source File

SOURCE=.\SignOut.h
# End Source File
# Begin Source File

SOURCE=.\SignOutList.h
# End Source File
# Begin Source File

SOURCE=.\SignOutListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SimpleCrypt.h
# End Source File
# Begin Source File

SOURCE=.\SizablePropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\SplitterWndFixed.h
# End Source File
# Begin Source File

SOURCE=.\SplitterWndHidable.h
# End Source File
# Begin Source File

SOURCE=.\SprintClassification.h
# End Source File
# Begin Source File

SOURCE=.\SprintDat.h
# End Source File
# Begin Source File

SOURCE=".\SRHalfStage (COM).h"
# End Source File
# Begin Source File

SOURCE=.\SRRegKey.h
# End Source File
# Begin Source File

SOURCE=.\StageCalc.h
# End Source File
# Begin Source File

SOURCE=.\StageDistance.h
# End Source File
# Begin Source File

SOURCE=.\StageRace.h
# End Source File
# Begin Source File

SOURCE=.\StageRace_i.h
# End Source File
# Begin Source File

SOURCE=".\StageRaceDoc (COM).h"
# End Source File
# Begin Source File

SOURCE=.\StageRaceDoc.h
# End Source File
# Begin Source File

SOURCE=".\StageRaceServer (COM).h"
# End Source File
# Begin Source File

SOURCE=.\StageRaceSplitFrame.h
# End Source File
# Begin Source File

SOURCE=.\StageRaceSplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\StageRaceStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\StageRaceWnd.h
# End Source File
# Begin Source File

SOURCE=.\StageSpeed.h
# End Source File
# Begin Source File

SOURCE=.\StaNoEdit.h
# End Source File
# Begin Source File

SOURCE=.\StaNoListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StaNoObject.h
# End Source File
# Begin Source File

SOURCE=.\StaNoObjectList.h
# End Source File
# Begin Source File

SOURCE=.\StartScreen.h
# End Source File
# Begin Source File

SOURCE=.\StaticPresentationView.h
# End Source File
# Begin Source File

SOURCE=.\StaticWebBrowser2.h
# End Source File
# Begin Source File

SOURCE=.\StatusActiveDoc.h
# End Source File
# Begin Source File

SOURCE=.\StatusCombo.h
# End Source File
# Begin Source File

SOURCE=.\StatusControl.h
# End Source File
# Begin Source File

SOURCE=.\StatusGenerate.h
# End Source File
# Begin Source File

SOURCE=.\StatusProgress.h
# End Source File
# Begin Source File

SOURCE=.\StatusStatic.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubEdit1.h
# End Source File
# Begin Source File

SOURCE=.\Team.h
# End Source File
# Begin Source File

SOURCE=.\TeamClassification.h
# End Source File
# Begin Source File

SOURCE=.\TextDoc.h
# End Source File
# Begin Source File

SOURCE=.\TextOutput.h
# End Source File
# Begin Source File

SOURCE=.\Time.h
# End Source File
# Begin Source File

SOURCE=.\TimeEdit.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\ToolBarWithProfilePicker.h
# End Source File
# Begin Source File

SOURCE=.\TransparentImage.h
# End Source File
# Begin Source File

SOURCE=.\TreeViewMain.h
# End Source File
# Begin Source File

SOURCE=.\TTOrderOptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\UpdateViewHint.h
# End Source File
# Begin Source File

SOURCE=.\versionno.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bannerbottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\borderli.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dialog1.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\idb_bannerbottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_borderline.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_credits.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_lightbulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_liststate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_mdiclient.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_options_panel_images.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_settings_topic.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_splashlogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_splashlogo_en.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\idb_splashlogo_fr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_splashlogo_nl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_StageRace.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_state.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_totaal.BMP
# End Source File
# Begin Source File

SOURCE=.\res\idb_tree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idb_treestate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idc_hlink.cur
# End Source File
# Begin Source File

SOURCE=.\res\idi_activedoctracker.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_activedoctracker_gray.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_dialog.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_key_free.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_key_lock.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_acti.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_configure.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_credits.txt
# End Source File
# Begin Source File

SOURCE=.\res\idr_license_du.txt
# End Source File
# Begin Source File

SOURCE=.\res\idr_license_en.txt
# End Source File
# Begin Source File

SOURCE=.\res\idr_mainframe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_mainframe.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_stag.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_stageracedoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_stageracetype.ico
# End Source File
# Begin Source File

SOURCE=.\res\key_free.ico
# End Source File
# Begin Source File

SOURCE=.\res\key_lock.ico
# End Source File
# Begin Source File

SOURCE=.\res\liststat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\listview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo_bit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mdiclien.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mdiclient.bmp
# End Source File
# Begin Source File

SOURCE=.\res\options_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OptionsPanel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splashlogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splashlogo_en.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splashlogo_nl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StageRace.rc2
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_competitors.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_configure.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_generate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_mainframe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_presentation.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_teams.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_treeview.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\treecomp.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CStageRaceDoc.rgs
# End Source File
# Begin Source File

SOURCE=.\Dutch.tip
# End Source File
# Begin Source File

SOURCE=.\English.tip
# End Source File
# Begin Source File

SOURCE=.\res\idr_credits.html
# End Source File
# Begin Source File

SOURCE=.\Help\Dutch\License.html
# End Source File
# Begin Source File

SOURCE=.\Help\English\License.html
# End Source File
# Begin Source File

SOURCE=.\MultiLanguage.mdb
# End Source File
# Begin Source File

SOURCE=".\Resource symbols.txt"
# End Source File
# Begin Source File

SOURCE=.\SRHalfStage.rgs
# End Source File
# Begin Source File

SOURCE=.\StageRace.clw
# End Source File
# Begin Source File

SOURCE=.\StageRace.rgs
# End Source File
# Begin Source File

SOURCE=.\StageRaceServer.rgs
# End Source File
# Begin Source File

SOURCE=.\version.ver
# End Source File
# End Target
# End Project
# Section StageRace : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section
# Section StageRace : {000A0001-0001-0010-0200-110002001200}
# 	1:13:IDR_STAGERACE:114
# End Section
# Section StageRace : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
