// Fill out your copyright notice in the Description page of Project Settings.


#include "Platformer_LaunchPad.h"
#include "PlatformerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatformer_LaunchPad::APlatformer_LaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RootComponent = BoxCollision;
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APlatformer_LaunchPad::OnPlayerOverlap);

	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BaseMesh->SetupAttachment(RootComponent);
	

	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMeshCompopnent"));
	PlaneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlaneMesh->SetupAttachment(RootComponent);
	
	LaunchStrength = 1000.f;
	LaunchAngle = 45.f;
	bDirectionalLaunchPad = true;
}

// Called when the game starts or when spawned
void APlatformer_LaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformer_LaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformer_LaunchPad::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlatformerCharacter* PlayerCharacter = Cast<APlatformerCharacter>(OtherActor);

	FRotator LaunchDirection = GetActorRotation();
	if (bDirectionalLaunchPad)
	{
		LaunchDirection.Pitch += LaunchAngle;
	} else
	{
		LaunchDirection.Pitch += 90.f;
	}
	
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	if (PlayerCharacter)
	{
		PlayerCharacter->LaunchCharacter(LaunchVelocity, bDirectionalLaunchPad, true);	
	}
	
	/*if (bDirectionalLaunchPad)
	{
		FRotator LaunchDirection = GetActorRotation();
		LaunchDirection.Pitch += LaunchAngle;
		FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

		if (PlayerCharacter)
		{
			PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);	
		}
		
	} else
	{
		FRotator LaunchDirection = GetActorRotation();
		LaunchDirection.Pitch += LaunchAngle;
		FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

		if (PlayerCharacter)
		{
			PlayerCharacter->LaunchCharacter(LaunchVelocity, false, true);	
		}

		
		//FVector LaunchDirection = BaseMesh->GetForwardVector() + FVector(0.f, 0.f, LaunchAngle) ;
		/*FRotator LaunchDirection = PlayerCharacter->GetActorForwardVector();
		LaunchDirection.Z += LaunchAngle;
		FVector LaunchVelocity = LaunchDirection * LaunchStrength;

		if (PlayerCharacter)
		{
			PlayerCharacter->LaunchCharacter(LaunchVelocity, false, true);
		}#1#
	}*/
	
}