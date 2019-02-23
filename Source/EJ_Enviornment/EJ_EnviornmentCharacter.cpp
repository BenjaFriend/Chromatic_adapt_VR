// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EJ_EnviornmentCharacter.h"
#include "EJ_EnviornmentProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC( LogFPChar, Warning, All );

//////////////////////////////////////////////////////////////////////////
// AEJ_EnviornmentCharacter

AEJ_EnviornmentCharacter::AEJ_EnviornmentCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize( 55.f, 96.0f );

    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Create a CameraComponent	
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT( "FirstPersonCamera" ) );
    FirstPersonCameraComponent->SetupAttachment( GetCapsuleComponent() );
    FirstPersonCameraComponent->RelativeLocation = FVector( -39.56f, 1.75f, 64.f ); // Position the camera
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
    // are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

    // Create VR Controllers.
    R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>( TEXT( "R_MotionController" ) );
    R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
    R_MotionController->SetupAttachment( RootComponent );
    L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>( TEXT( "L_MotionController" ) );
    L_MotionController->SetupAttachment( RootComponent );

    // Uncomment the following line to turn motion controllers on by default:
    bUsingMotionControllers = true;
}

void AEJ_EnviornmentCharacter::BeginPlay()
{
    // Call the base class  
    Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEJ_EnviornmentCharacter::SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent )
{
    // set up gameplay key bindings
    check( PlayerInputComponent );

    // Bind jump events
    PlayerInputComponent->BindAction( "Jump", IE_Pressed, this, &ACharacter::Jump );
    PlayerInputComponent->BindAction( "Jump", IE_Released, this, &ACharacter::StopJumping );

    // Bind fire event
    PlayerInputComponent->BindAction( "Fire", IE_Pressed, this, &AEJ_EnviornmentCharacter::OnFire );

    // Enable touchscreen input
    EnableTouchscreenMovement( PlayerInputComponent );

    PlayerInputComponent->BindAction( "ResetVR", IE_Pressed, this, &AEJ_EnviornmentCharacter::OnResetVR );

    // Bind movement events
    PlayerInputComponent->BindAxis( "MoveForward", this, &AEJ_EnviornmentCharacter::MoveForward );
    PlayerInputComponent->BindAxis( "MoveRight", this, &AEJ_EnviornmentCharacter::MoveRight );

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis( "Turn", this, &APawn::AddControllerYawInput );
    PlayerInputComponent->BindAxis( "TurnRate", this, &AEJ_EnviornmentCharacter::TurnAtRate );
    PlayerInputComponent->BindAxis( "LookUp", this, &APawn::AddControllerPitchInput );
    PlayerInputComponent->BindAxis( "LookUpRate", this, &AEJ_EnviornmentCharacter::LookUpAtRate );
}

void AEJ_EnviornmentCharacter::OnFire()
{
   
}

void AEJ_EnviornmentCharacter::OnResetVR()
{
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AEJ_EnviornmentCharacter::BeginTouch( const ETouchIndex::Type FingerIndex, const FVector Location )
{
    if ( TouchItem.bIsPressed == true )
    {
        return;
    }
    if ( ( FingerIndex == TouchItem.FingerIndex ) && ( TouchItem.bMoved == false ) )
    {
        OnFire();
    }
    TouchItem.bIsPressed = true;
    TouchItem.FingerIndex = FingerIndex;
    TouchItem.Location = Location;
    TouchItem.bMoved = false;
}

void AEJ_EnviornmentCharacter::EndTouch( const ETouchIndex::Type FingerIndex, const FVector Location )
{
    if ( TouchItem.bIsPressed == false )
    {
        return;
    }
    TouchItem.bIsPressed = false;
}

void AEJ_EnviornmentCharacter::MoveForward( float Value )
{
    if ( Value != 0.0f )
    {
        // add movement in that direction
        AddMovementInput( GetActorForwardVector(), Value );
    }
}

void AEJ_EnviornmentCharacter::MoveRight( float Value )
{
    if ( Value != 0.0f )
    {
        // add movement in that direction
        AddMovementInput( GetActorRightVector(), Value );
    }
}

void AEJ_EnviornmentCharacter::TurnAtRate( float Rate )
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput( Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() );
}

void AEJ_EnviornmentCharacter::LookUpAtRate( float Rate )
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput( Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() );
}

bool AEJ_EnviornmentCharacter::EnableTouchscreenMovement( class UInputComponent* PlayerInputComponent )
{
    if ( FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch )
    {
        PlayerInputComponent->BindTouch( EInputEvent::IE_Pressed, this, &AEJ_EnviornmentCharacter::BeginTouch );
        PlayerInputComponent->BindTouch( EInputEvent::IE_Released, this, &AEJ_EnviornmentCharacter::EndTouch );

        //Commenting this out to be more consistent with FPS BP template.
        //PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AEJ_EnviornmentCharacter::TouchUpdate);
        return true;
    }

    return false;
}