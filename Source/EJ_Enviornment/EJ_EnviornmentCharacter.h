// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EJ_EnviornmentCharacter.generated.h"

class UInputComponent;

UCLASS( config = Game )
class AEJ_EnviornmentCharacter : public ACharacter
{
    GENERATED_BODY()

    /** First person camera */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
    class UCameraComponent* FirstPersonCameraComponent;

    /** Motion controller (right hand) */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    class UMotionControllerComponent* R_MotionController;

    /** Motion controller (left hand) */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    class UMotionControllerComponent* L_MotionController;

    /** The widget interaction component for selecting the level */
    UPROPERTY( Category = "Level Select", VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    class UWidgetInteractionComponent* LevelSelectInteraction;

    UPROPERTY( Category = "Level Select", EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
    class USceneComponent* LevelSelectionSpawnPoint;

    /** The widget that will be 8used for level selection */
    UPROPERTY( EditDefaultsOnly, Category = "Level Select", meta = ( AllowPrivateAccess = "true" ) )
    TSubclassOf<AActor> LevelSelectWidget_Class;

    /** The spawned level selection widget on beginPlay */
    AActor* LevelSelectWidget;

public:
    AEJ_EnviornmentCharacter();

protected:
    virtual void BeginPlay();

public:
    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera )
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera )
    float BaseLookUpRate;

    /** Whether to use motion controller location for aiming. */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
    uint32 bUsingMotionControllers : 1;

    /** Whether to use eye level for the VR Camera. */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Demo Settings" )
    uint32 bUseEyeLevel : 1;

protected:

    /** Menu Pressed */
    void OnMenu();

    /** Fires a projectile. */
    void OnFire();

    /** Released fire key */
    void OnFireReleased();

    /** Resets HMD orientation and position in VR. */
    void OnResetVR();

    /** Handles moving forward/backward */
    void MoveForward( float Val );

    /** Handles stafing movement, left and right */
    void MoveRight( float Val );

    /**
     * Called via input to turn at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate( float Rate );

    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate( float Rate );

    struct TouchData
    {
        TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
        bool bIsPressed;
        ETouchIndex::Type FingerIndex;
        FVector Location;
        bool bMoved;
    };
    void BeginTouch( const ETouchIndex::Type FingerIndex, const FVector Location );
    void EndTouch( const ETouchIndex::Type FingerIndex, const FVector Location );
    void TouchUpdate( const ETouchIndex::Type FingerIndex, const FVector Location );
    TouchData	TouchItem;

protected:
    // APawn interface
    virtual void SetupPlayerInputComponent( UInputComponent* InputComponent ) override;
    // End of APawn interface

    /*
     * Configures input for touchscreen devices if there is a valid touch interface for doing so
     *
     * @param	InputComponent	The input component pointer to bind controls to
     * @returns true if touch controls were enabled.
     */
    bool EnableTouchscreenMovement( UInputComponent* InputComponent );

public:
    /** Returns FirstPersonCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};