/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 02 21:03:44 2006
 */
/* Compiler settings for D:\Projects\StageRace\trunk\StageRace.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ISRHalfStage = {0x55B2C551,0x69F1,0x43D7,{0x9D,0xCA,0x59,0x98,0x9C,0x3B,0x18,0x08}};


const IID IID_IStageRaceDoc = {0xEB26427B,0x82AC,0x45FA,{0x80,0xAF,0xF9,0x3C,0x8A,0x31,0x89,0xAD}};


const IID IID_IStageRaceServer = {0x31AC26B2,0x80B3,0x4ACF,{0xBB,0xB9,0x68,0x6C,0xA5,0x5E,0xDA,0x44}};


const IID LIBID_StageRaceLib = {0x0F5CA62A,0x5B01,0x4FC6,{0x9D,0x68,0x4F,0xC2,0x23,0xAE,0xF8,0x9C}};


const CLSID CLSID_StageRaceServer = {0x5AD7E1A3,0xB139,0x4A1B,{0x83,0xE0,0x11,0x7F,0x2F,0x38,0x31,0xD0}};


const CLSID CLSID_StageRaceDoc = {0xC8B27B99,0xDDC6,0x457E,{0xB7,0xDC,0x8D,0xC3,0x50,0x79,0xA9,0xC6}};


const CLSID CLSID_SRHalfStage = {0x6612404C,0x66ED,0x4CAB,{0x85,0x06,0x4B,0x8B,0x59,0x67,0xF1,0x8C}};


#ifdef __cplusplus
}
#endif

