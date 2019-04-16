// Copyright Ben Hoffman 2019

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScrutinyBFL.generated.h"


typedef const char*( *CustomToStringDelegate )( void* );

/**
 * 
 */
UCLASS()
class EJ_ENVIORNMENT_API UScrutinyBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

    // Import DLL Call
    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importDLL( FString folder, FString name );
    
    // Method imports
    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool ImportScrutiny();
            
    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodInitLib();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodTestRequest();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodStartReport();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodSendReport();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodReportFloat();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodReportCharacter();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static bool importMethodRelease();


    // Method GETTERS
    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void getInitLibFromDll( FString aServerAddress, FString aServerPort );

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static const int getTestRequestFromDll();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void getStartReportFromDll();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void getSendReportFromDll();

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void getReportFloatFromDll( FString aKey, float aVal );

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void getReportCharacterFromDll( FString aKey, FString aVal );

    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void getReleaseFromDll();

    // Free dll call
    UFUNCTION( BlueprintCallable, Category = "Scrutiny" )
    static void freeDLL();
};
