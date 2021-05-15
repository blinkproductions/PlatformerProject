// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor2.generated.h"

class UStaticMeshComponent;

UCLASS()
class PLATFORMERPROJECT_API ATestActor2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BaseMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
