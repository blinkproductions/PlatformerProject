// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlatformerCharacter::APlatformerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArm->SocketOffset = FVector(0.f,0.f,200.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 10.f;
	SpringArm->CameraRotationLagSpeed = 10.f;
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	WeaponSheath = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponentSheath"));
	WeaponSheath->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	//WeaponSheath->SetWorldRotation(FRotator(-190.f, 10.f,0.f));
	WeaponSheath->SetupAttachment(GetMesh(), FName("WeaponSheath1"));

	

	WeaponInHand = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponentWeaponInHand"));
	//WeaponInHand->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	//WeaponInHand->SetWorldRotation(FRotator(-185.f, 83.f,-36.f));
	WeaponInHand->SetupAttachment(GetMesh(), FName("WeaponSocket"));

	EquippedWeapon1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EquippedWeapon1Component"));
	EquippedWeapon1->SetupAttachment(WeaponSheath);
	

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 1.5f;

	

	JumpHeight = 600.f;
	bCanDoubleJump = true;
	NumberOfExtraJumps = 1;
	DoubleJumpCounter = 0;

}

// Called when the game starts or when spawned
void APlatformerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlatformerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlatformerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlatformerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	if (bCanDoubleJump)
	{
		PlayerInputComponent->BindAction("Jump", IE_Pressed,this,&APlatformerCharacter::DoubleJump);	
	} else
	{
		PlayerInputComponent->BindAction("Jump", IE_Pressed,this,&ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released,this,&ACharacter::StopJumping);
	}
}

void APlatformerCharacter::DoubleJump()
{
	if (DoubleJumpCounter <= NumberOfExtraJumps)
	{
		ACharacter::LaunchCharacter(FVector(0.f, 0.f, JumpHeight), false, true);
		DoubleJumpCounter++;
	}
}

void APlatformerCharacter::Landed(const FHitResult& Hit)
{
	DoubleJumpCounter = 0.f;
	StopJumping();
}

void APlatformerCharacter::MoveForward(float val)
{
	if (val != 0)
	{
		//AddMovementInput(GetActorForwardVector() * val);

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}
}

void APlatformerCharacter::MoveRight(float val)
{
	if (val != 0)
	{
		//AddMovementInput(GetActorRightVector() * val);

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, val);
	}
}

void APlatformerCharacter::LookUpRate(float val)
{
	AddControllerPitchInput(val * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlatformerCharacter::LookRightRate(float val)
{
	AddControllerYawInput(val * RotationRate * GetWorld()->GetDeltaSeconds());
}
