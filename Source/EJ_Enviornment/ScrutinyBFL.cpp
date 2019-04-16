// Copyright Ben Hoffman 2019

#include "ScrutinyBFL.h"
#include "Runtime/Core/Public/Misc/Paths.h"

typedef void( *_InitLib )( const char* aServerAddress, const char* aServerPort ); // Declare a method to store the DLL method getInitLib.
typedef void( *_Release )( );           // Declare a method to store the DLL method Release.
typedef const int( *_TestRequest )( );  // Declare a method to store the DLL method TestRequest.
    
typedef void( *_StartReport )( );       // Declare a method to store the DLL method Release.
typedef const int( *_SendReport )( );   // Declare a method to store the DLL method Release.

typedef const int( *_ReportFloat )( const char* aKey, float aValue );   // Declare a method to store the DLL method Release.
typedef const int( *_ReportCharacter )( const char* aKey, const char* aValue );   // Declare a method to store the DLL method Release.

// Don't forget to release these!
_InitLib            m_getInitLibFromDll;
_Release            m_getReleaseFromDll;
_TestRequest        m_getTestRequestFromDll;

_StartReport        m_getStartReportFromDll;
_SendReport         m_getSendReportFromDll;

_ReportFloat        m_getReportFloatFromDll;
_ReportCharacter    m_getReportCharacterFromDll;

void* v_dllHandle;


#pragma region Load DLL

// Method to import a DLL.
bool UScrutinyBFL::importDLL( FString folder, FString name )
{
    FString filePath = *FPaths::GamePluginsDir() + folder + "/" + name;

    if ( FPaths::FileExists( filePath ) )
    {
        v_dllHandle = FPlatformProcess::GetDllHandle( *filePath ); // Retrieve the DLL.
        if ( v_dllHandle != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}
#pragma endregion Load DLL


#pragma region Import Methods

bool UScrutinyBFL::ImportScrutiny()
{
    bool iRet = false;

    iRet = importMethodInitLib();
    iRet = importMethodTestRequest();
    iRet = importMethodStartReport();
    iRet = importMethodSendReport();
    iRet = importMethodReportFloat();
    iRet = importMethodReportCharacter();
    iRet = importMethodRelease();

    return iRet;
}

// Imports the method getInitLibFromDll from the DLL.
bool UScrutinyBFL::importMethodInitLib()
{
    if ( v_dllHandle != NULL )
    {
        m_getInitLibFromDll = NULL;
        FString procName = "InitLib";	// Needs to be the exact name of the DLL method.
        m_getInitLibFromDll = ( _InitLib ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getInitLibFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

// Imports the method getTestRequestFromDll from the DLL.
bool UScrutinyBFL::importMethodTestRequest()
{
    if ( v_dllHandle != NULL )
    {
        m_getTestRequestFromDll = NULL;
        FString procName = "TestRequest";	// Needs to be the exact name of the DLL method.
        m_getTestRequestFromDll = ( _TestRequest ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getTestRequestFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

bool UScrutinyBFL::importMethodStartReport()
{
    if ( v_dllHandle != NULL )
    {
        m_getStartReportFromDll = NULL;
        FString procName = "StartReport";	// Needs to be the exact name of the DLL method.
        m_getStartReportFromDll = ( _StartReport ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getStartReportFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

bool UScrutinyBFL::importMethodSendReport()
{
    if ( v_dllHandle != NULL )
    {
        m_getSendReportFromDll = NULL;
        FString procName = "SendReport";	// Needs to be the exact name of the DLL method.
        m_getSendReportFromDll = ( _SendReport ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getSendReportFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

bool UScrutinyBFL::importMethodReportFloat()
{
    if ( v_dllHandle != NULL )
    {
        m_getReportFloatFromDll = NULL;
        FString procName = "ReportFloat";	// Needs to be the exact name of the DLL method.
        m_getReportFloatFromDll = ( _ReportFloat ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getReportFloatFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

bool UScrutinyBFL::importMethodReportCharacter()
{
    if ( v_dllHandle != NULL )
    {
        m_getReportCharacterFromDll = NULL;
        FString procName = "ReportCharacter";	// Needs to be the exact name of the DLL method.
        m_getReportCharacterFromDll = ( _ReportCharacter ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getReportCharacterFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

// Imports the method getReleaseFromDll from the DLL.
bool UScrutinyBFL::importMethodRelease()
{
    if ( v_dllHandle != NULL )
    {
        m_getReleaseFromDll = NULL;
        FString procName = "Release";	// Needs to be the exact name of the DLL method.
        m_getReleaseFromDll = ( _Release ) FPlatformProcess::GetDllExport( v_dllHandle, *procName );
        if ( m_getReleaseFromDll != NULL )
        {
            return true;
        }
    }
    return false;	// Return an error.
}

#pragma endregion Import Methods

#pragma region Method Calls

void UScrutinyBFL::getInitLibFromDll( FString aServerAddress, FString aServerPort )
{
    if ( m_getInitLibFromDll != NULL )
    {
        char* parameterServerChar = TCHAR_TO_ANSI( *aServerAddress );
        char* parameterPortChar = TCHAR_TO_ANSI( *aServerPort );

        m_getInitLibFromDll( parameterServerChar, parameterPortChar );
    }
}

const int UScrutinyBFL::getTestRequestFromDll()
{
    if ( m_getTestRequestFromDll != NULL )
    {
        int out = ( int ) ( m_getTestRequestFromDll() );
        return out;
    }
    return -32202;  // Return an error
}

void UScrutinyBFL::getStartReportFromDll()
{
    if ( m_getStartReportFromDll != NULL )
    {
        m_getStartReportFromDll();
    }
}

void UScrutinyBFL::getSendReportFromDll()
{
    if ( m_getSendReportFromDll != NULL )
    {
        m_getSendReportFromDll();
    }
}

void UScrutinyBFL::getReportFloatFromDll( FString aKey, float aVal )
{
    if ( m_getReportFloatFromDll != NULL )
    {
        char* parameterKeyChar = TCHAR_TO_ANSI( *aKey );
        m_getReportFloatFromDll( parameterKeyChar, aVal );
    }
}

void UScrutinyBFL::getReportCharacterFromDll( FString aKey, FString aVal )
{
    if ( m_getReportCharacterFromDll != NULL )
    {
        char* parameterKeyChar = TCHAR_TO_ANSI( *aKey );
        char* parameterValChar = TCHAR_TO_ANSI( *aVal );
        
        m_getReportCharacterFromDll( parameterKeyChar, parameterValChar );
    }
}

void UScrutinyBFL::getReleaseFromDll()
{
    if ( m_getReleaseFromDll != NULL )
    {
        m_getReleaseFromDll();
    }
}

#pragma endregion Method Calls


#pragma region Unload DLL

// If you love something  set it free.
void UScrutinyBFL::freeDLL()
{
    if ( v_dllHandle != NULL )
    {
        m_getInitLibFromDll = NULL;
        m_getTestRequestFromDll = NULL;
        m_getReleaseFromDll = NULL;

        m_getStartReportFromDll = NULL;
        m_getSendReportFromDll = NULL;

        m_getReportFloatFromDll = NULL;
        m_getReportCharacterFromDll = NULL;

        FPlatformProcess::FreeDllHandle( v_dllHandle );
        v_dllHandle = NULL;
    }
}
#pragma endregion Unload DLL