/*       
 *****************************************************************************
 *
 *  HASP.H - The Main include file for the HASP C/C++ API.
 *
 *****************************************************************************
 */

#ifndef HASP_H_
#define HASP_H_

/*
 *  General configuration file.
 */
#include "haspconf.h"

/*
 *	 Old Service symbols are included for compatibility with previous
 *  HASP releases. If you are a new HASP user this is not necessary for you.
 */
// #include "olddefs.h"


/*
 * LPT numbers for HASP and HASP36 on PC and NEC.
 */
#define HASP25								0
#define HASP36								50
#define HASP36NEC							60

/*
 *	 Services common to All Local Keys. HASP-3, MemoHASP, TimeHASP.
 */
#define LOCALHASP_ISHASP				1
#define LOCALHASP_HASPCODE				2
#define LOCALHASP_HASPSTATUS			5

/*
 *  MemoHASP Memory services.
 */
#define MEMOHASP_READMEMO				3
#define MEMOHASP_WRITEMEMO				4
#define MEMOHASP_HASPID					6
#define MEMOHASP_READBLOCK			   50
#define MEMOHASP_WRITEBLOCK			51

/*
 *	TimeHASP clock services.
 */
#define TIMEHASP_SETTIME            70
#define TIMEHASP_GETTIME            71
#define TIMEHASP_SETDATE            72
#define TIMEHASP_GETDATE            73

/*
 *	TimeHASP memory services.
 */
#define TIMEHASP_READMEMO				75
#define TIMEHASP_WRITEMEMO				74
#define TIMEHASP_HASPID					78
#define TIMEHASP_READBLOCK			   77
#define TIMEHASP_WRITEBLOCK			76

/*
 *	NetHASP network services.
 */
#define NETHASP_LASTSTATUS				40
#define NETHASP_HASPCODE				41
#define NETHASP_LOGIN               42
#define NETHASP_LOGOUT					43
#define NETHASP_SET_IDLETIME			48
#define NETHASP_SET_CONFIG_FILENAME	85
#define NETHASP_SET_SERVER_BY_NAME	96

/*
 *	NetHASP memory services.
 */
#define NETHASP_READMEMO			   44
#define NETHASP_WRITEMEMO				45
#define NETHASP_HASPID			 	   46
#define NETHASP_READBLOCK		      52
#define NETHASP_WRITEBLOCK		      53

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  The hasp() routine.
 *  The Macro HASPAPI depends on system and configuration. (see HASPCONF.H)
 */
void HASPAPI hasp(int service, int seed, int lptnum, int pass1, int pass2,
                  int FAR* p1, int FAR* p2, int FAR* p3, int FAR* p4 );

#ifdef __cplusplus
};
#endif


#endif  /*  HASP_H_ */

