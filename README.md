# StageRace

## Introduction

StageRace is a full-blown administration program for road cycling stage races.

More information can be found [here](https://www.totaalsoftware.com/products/stagerace).

## History

The development of StageRace's MS-DOS based predecessor started in 1996. StageRace itself is under development since
1998, and it had its first real-life test at the Netherlands Tour of 2000. It has been under active development until
2007, and has been in hibernation/maintenance since then. In 2017 it was open sourced. Today you found it.

## License

The StageRace source code was released in 2017 under version 3 of the GNU General Public License. The intention of 
this source code release is to allow existing customers (and the general public) to continue the useful life of the 
software for their purposes, while the original author has stopped making updated versions of the software available.
The intention of choosing the GNU General Public License is meant as an encouragement to share further changes with 
other customers and the general public.

Copyright 2000, 2003, 2005, 2012, 2017 Sander Verhagen, also acting as sole proprietor under the name "Totaal Software".

The name Totaal Software and the "totaal" logo remain the exclusive property of Sander Verhagen, but can be used in any
subsequent release of StageRace.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

See `LICENSE.txt`.

## Support

Again, this program (source code) comes WITHOUT ANY WARRANTY, also without any promises of support from the original 
author. However, you may always [reach out](mailto:sander@sanderverhagen.net) with questions, and entirely at their 
discretion the original author may try to answer your questions. Most likely, however, they do not have a working 
development environment at their disposal for this software.

## Usage

Usage of this software is extensively documented [here](https://www.totaalsoftware.com/products/stagerace). The 
remainder of this documentation is meant for development.

## Development

The remainder of this document describes the development using the StageRace source code.

## Note

This documentation was written some years *after* the last active development took place. Some information may not be
accurate as a result. If inaccuracies are suspected, these are indicated using the word PROBABLY.
 
## Another Note

StageRace was mainly written while, and shortly after the original author went to college. Their Visual C skills were 
mostly self-taught, and they still had a lot to learn in software development. As a seasoned professional, today, there 
is a lot of things in this code base that they would strongly advise against. That said, there is a lot of intention in 
the code, it has gotten a lot of love, and it has matured from the feedback of real-life application.

## Prerequisites

* PC with Microsoft Windows 8 or newer. PROBABLY the Pro edition is required 
* Microsoft Visual Studio 2010 installed. Likely newer versions are okay, but this was not verified. Support for MFC is 
required; in older versions of Visual Studio this was only the case for Professional and better editions (this may 
not be the case anymore)
* Git installed, cloned repository
* Working knowledge of C++, MFC, Visual Studio, Win32 development, and Git

For releases:

* Little Setup Builder installed (`lsb02_01.exe`)

For Help:

* Microsoft HTML Help Workshop

## Projects

The solution contains the following projects:

### StageRace ("Core Application")

The main StageRace application. StageRace is a MDI (Multiple Document Interface, main window with multiple documents)
application, that lets you open multiple stage races, each of which is stored in its own `.str` file. It mimics 
behavior from well-known applications (like e.g. Microsoft Word) in its behavior of "New", "Open", "Save", "Save As",
etc. PROBABLY this is achieved by classes such as `CMainFrame`, `CMDIClient`.

This application is the meat of the entire solution, and by itself should build into a usable and fully-functional 
`StageRace.exe`; everything else, well, bonus!

Other very distinct types of classes are:

* Modal dialogs: typically starting named like `CDlgExample`, e.g. `CDlgArrivalInsertPositions`, 
`CDlgAutonumberCommuniques`, etc. Implementation is often aided by `cdxCDynamicWnd` and friends (an open source 
library that was available at the time, also included)

* There's also a handful of modal dialogs acting as message boxes, typically starting named like `CMsgBoxExample`

* There's also many property pages for entry of arrival information, `CListArrival`, `CAllListArrivalPages`, 
`CListTimeTrialArrivalGross`, and so on

* Views: elements in the main document window, notably `CTreeViewMain` (tree view on the left-hand side), list views 
(competitors, teams), presentation view (e.g. showing HTML classifications, PROBABLY just wrapping Internet Explorer)

* Document: a representation of the `.str` file, starting with `CStageRaceDoc`, harboring a lot of stuff, like lists of
`CCompetitor` and `CTeam`, an instance of `CAllSettings`, and all stages. But the first thing written in the `.str` 
file is the file version, so that StageRace is able to open files from older versions. Stages are represented first by
full stages (`CFullStage`), which is mostly a wrapper around half stages, but also has a date and a communique 
(`CCommunique`). Half stages (`CHalfStage`) are considerably more-elaborate, as they hold all associated 
configuration (for example, bonus and points schemes), signouts (`CSignOutList`), corrections (`CCorrectionList`) and
arrival information (`CArrivalList`, not to be confused with the corresponding property pages, such as `CListArrival`,
discussed above)

* Configuration: part of the document that sets up half stages and full stages, property pages for this configuration
in `C...Dat`

* Settings: data objects in `CSettings` and friends, property pages for settings dialogs in `CPageSettings` and friends

* (D)COM application to let other applications integrate with a running instance of StageRace. This has, at times, been
used to integrate with scoreboards and timekeeping systems. A MIDL interface is specified in `ISRHalfStage` and 
implemented in `CStageRaceComDoc`. Also see "stagerace message protocol (EN)" in the `Documents/English` folder. Note
that this constellation involves a few files that are automatically generated on build, and that may appear in your 
change set, even if it's just an updated timestamp

...and much, much more! Helper classes, status bars, tool bars, multi-language, ...

Includes are managed centrally, in `incl.h`. This is convenient in the sense that all includes can be found in one 
place, but it leads to substantive rebuilds of the application, in case of changes to this file.

### Speed Calculator

A simple tool to calculate speed based on entered distance and time. It is shipped with StageRace. It depends on 
source code of the core application (see `incl.h`).

### Time Calculator

A simple tool to do additions and subtractions of entered time values. It is shipped with StageRace. It depends on 
source code of the core application (see `incl.h`).

### Increment Build Number (`buildinc`)

A tool used during build of StageRace to automatically increment the build number. It's incremented on every 
subsequent build, to make sure that every two separate executables can be uniquely identified. It looks at the head 
of `version.ver` (`Version.VER`) and automatically determines a new build number. If there is a larger change in 
version number than just the build number, PROBABLY `version.ver` must be manually edited. The tool is invoked from
`PreLink_Cmds`/`PreLinkEvent` in the StageRace project, and PROBABLY updates `StageRace.res` (generated file) for
"Debug"/"Release" as needed

### Append Checksum

A tool used during build of StageRace to a checksum to the end of the executable file, PROBABLY four bytes long. This
is meant as a security measure, to detect tampering with the executable, such as attempts to bypass the hardware key
requirements. The tool is invoked from `PostBuild_Cmds`/`PostBuildEvent` in the StageRace project, and directly 
updates `StageRace.exe` (as built) for "Debug"/"Release" as needed

### HelpTool

A tool used to convert Help, from raw topics into both separate topics (for HTML Help, with headers, footers, etc.), 
and PROBABLY a single HTML document (for making a PDF)

### KeySupport

A tool used to let customers update their own hardware keys, it was pre-programmed with specific instructions for 
specific hardware keys, known to be in the possession of specific customers. This source code is not included

### Setup

Everything needed to build releases, i.e. an interactive setup application. Setup applications for StageRace are 
built using Little Setup Builder ([website largely defunct](http://www.ammasw.com/LSB_Intro.html), therefore 
`lsb02_01.exe` included in this repository, this is PROBABLY not the same as [Basic Setup
Builder](http://www.ammasw.com/))

### Setup Support Library

A library used as part of the setup application, performing specific tasks during installation of StageRace that are 
not offered by Little Setup Builder, such as checking the version of Internet Explorer installed, and setting some 
specific file attributes

### Documents

Various documents that were created for selling StageRace and training customers to use it.

This `Documents` folder also contains a copy of UCI Cycling Regulations (PROBABLY old and outdated, just for 
reference); these are the property of the respective copyright holder, probably UCI.

This `Documents` folder also contains assets for the creation of CD-ROMs for StageRace (labels and covers), that were
made using CorelDraw. For many years already, physical media have not been shipped for StageRace anymore.

## Release

The main StageRace application can be built and released as follows:

1. Update version number in `Version.VER`
2. Build StageRace as you would, using the "Release" configuration
3. Update version number in `English.TIP`
4. Make sure `Updates.HTML` is up-to-date; it has to contain:
	- An entry in the overview with the correct date
	- An entry in the "Fixes per Update"

5. Make sure Little Setup Builder is installed (`lsb02_01.exe`)
6. Open `Setup Definition.LSB` in Little Setup Builder

   Then:
  
   1. "Project"
   2. "Global Settings"
   3. Adjust the version number in the output file name (e.g. `stagerace2005399.exe`)
  
   Then:
  
   1. "Run"
   2. "Build setup program"

7. Move `Setup/stagerace20053xx.exe` to wherever you want to release it

This does not acknowledge changes to the [Help](https://www.totaalsoftware.com/products/stagerace/support/online-help).
PROBABLY the Help has not been updated for a long time.

## Hardware Keys

StageRace software is protected by use of a hardware key. Without the hardware key your copy will work in evaluation 
mode. With the release of the source code, this protection is also given up. It is the expectation that whomever uses
this source code to craft a software update, also rips out the hardware keys requirement. Go for it!
