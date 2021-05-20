// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlatformerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PLATFORMERPROJECT_API APlatformerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlatformerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Specs")
	float JumpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Specs")
	bool bCanDoubleJump;

	UPROPERTY(EditDefaultsOnly, Category = "Specs")
	int NumberOfExtraJumps;
	
	UFUNCTION()
    void DoubleJump();

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditDefaultsOnly)
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	uint8 BulletAmount = 10.f;

private:	
	void MoveForward(float val);
	void MoveRight(float val);

	void LookUpRate(float val);
	void LookRightRate(float val);

	UPROPERTY(EditDefaultsOnly)
	int DoubleJumpCounter;
};
