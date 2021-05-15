// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platformer_LaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PLATFORMERPROJECT_API APlatformer_LaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformer_LaunchPad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
        void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlaneMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Specs")
	float LaunchStrength;

	UPROPERTY(EditAnywhere, Category = "Specs", meta = (ToolTip = "If false, Launch Angle will be disabled and automatically be set to 90"))
	bool bDirectionalLaunchPad;

	UPROPERTY(EditAnywhere, Category = "Specs", meta = (EditCondition = "bDirectionalLaunchPad"))
	float LaunchAngle;
	
};
