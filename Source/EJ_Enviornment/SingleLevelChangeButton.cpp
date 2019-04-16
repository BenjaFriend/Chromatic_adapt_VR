// Copyright Ben Hoffman 2019

#include "SingleLevelChangeButton.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ASingleLevelChangeButton::ASingleLevelChangeButton()
{
 	
    LevelSelectionSpawnPoint = CreateDefaultSubobject<USceneComponent>( TEXT( "LevelSelectionSpawnPoint" ) );
    LevelSelectionSpawnPoint->SetupAttachment( RootComponent );
    
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASingleLevelChangeButton::BeginPlay()
{
	Super::BeginPlay();
	
    UWorld* const World = GetWorld();
    if ( World )
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        LevelSelectWidgetInstance = World->SpawnActor<AActor>( LevelSelectWidget_Class, SpawnParams );
        if ( LevelSelectWidgetInstance )
        {
            // Set spawn pos and rot
            LevelSelectWidgetInstance->SetActorLocation( LevelSelectionSpawnPoint->GetComponentLocation() );
            LevelSelectWidgetInstance->SetActorRotation( LevelSelectionSpawnPoint->GetComponentRotation() );
            LevelSelectWidgetInstance->SetActorHiddenInGame( false );
        }
    }

}