// Copyright Ben Hoffman 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleLevelChangeButton.generated.h"

UCLASS()
class EJ_ENVIORNMENT_API ASingleLevelChangeButton : public AActor
{
	GENERATED_BODY()
	
    /** The widget that will be 8used for level selection */
    UPROPERTY( EditDefaultsOnly, Category = "Level Select", meta = ( AllowPrivateAccess = "true" ) )
    TSubclassOf<AActor> LevelSelectWidget_Class;

    /** The spawn position of the widget */
    UPROPERTY( Category = "Level Select", EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
    class USceneComponent* LevelSelectionSpawnPoint;

    /** The spawned level selection widget on beginPlay */
    AActor* LevelSelectWidgetInstance;

public:	
	// Sets default values for this actor's properties
	ASingleLevelChangeButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
