#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <iostream>
using namespace std;

// from npapi.h
#define WNNC_SPEC_VERSION                0x00000001
#define WNNC_SPEC_VERSION51              0x00050001
#define WNNC_NET_TYPE                    0x00000002
#define WNNC_START                       0x0000000C
#define WNNC_WAIT_FOR_START              0x00000001

//from ntdef.h
typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

// from NTSecAPI.h
typedef enum _MSV1_0_LOGON_SUBMIT_TYPE
{
	MsV1_0InteractiveLogon = 2,
	MsV1_0Lm20Logon,
	MsV1_0NetworkLogon,
	MsV1_0SubAuthLogon,
	MsV1_0WorkstationUnlockLogon = 7,
	MsV1_0S4ULogon = 12,
	MsV1_0VirtualLogon = 82,
	MsV1_0NoElevationLogon = 83,
	MsV1_0LuidLogon = 84,
} MSV1_0_LOGON_SUBMIT_TYPE, * PMSV1_0_LOGON_SUBMIT_TYPE;

// from NTSecAPI.h
typedef struct _MSV1_0_INTERACTIVE_LOGON
{
	MSV1_0_LOGON_SUBMIT_TYPE MessageType;
	UNICODE_STRING LogonDomainName;
	UNICODE_STRING UserName;
	UNICODE_STRING Password;
} MSV1_0_INTERACTIVE_LOGON, * PMSV1_0_INTERACTIVE_LOGON;

// from NTSecAPI.h
typedef enum _KERB_LOGON_SUBMIT_TYPE {
	KerbInteractiveLogon = 2,
	KerbSmartCardLogon = 6,
	KerbWorkstationUnlockLogon = 7,
	KerbSmartCardUnlockLogon = 8,
	KerbProxyLogon = 9,
	KerbTicketLogon = 10,
	KerbTicketUnlockLogon = 11,
	//#if (_WIN32_WINNT >= 0x0501) -- Disabled until IIS fixes their target version.
	KerbS4ULogon = 12,
	//#endif
#if (_WIN32_WINNT >= 0x0600)     
	KerbCertificateLogon = 13,
	KerbCertificateS4ULogon = 14,
	KerbCertificateUnlockLogon = 15,
#endif    
#if (_WIN32_WINNT >= 0x0602)     
	KerbNoElevationLogon = 83,
	KerbLuidLogon = 84,
#endif    
} KERB_LOGON_SUBMIT_TYPE, * PKERB_LOGON_SUBMIT_TYPE;

// from NTSecAPI.h
typedef struct _KERB_INTERACTIVE_LOGON {
	KERB_LOGON_SUBMIT_TYPE MessageType;
	UNICODE_STRING         LogonDomainName;
	UNICODE_STRING         UserName;
	UNICODE_STRING         Password;
} KERB_INTERACTIVE_LOGON, * PKERB_INTERACTIVE_LOGON;

extern "C" __declspec(dllexport)
DWORD
APIENTRY
NPGetCaps(
	DWORD nIndex
);

extern "C" __declspec(dllexport)
DWORD
APIENTRY
NPLogonNotify(
	PLUID lpLogonId,
	LPCWSTR lpAuthInfoType,
	LPVOID lpAuthInfo,
	LPCWSTR lpPrevAuthInfoType,
	LPVOID lpPrevAuthInfo,
	LPWSTR lpStationName,
	LPVOID StationHandle,
	LPWSTR * lpLogonScript
);