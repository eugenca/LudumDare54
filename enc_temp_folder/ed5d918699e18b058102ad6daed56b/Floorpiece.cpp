// Fill out your copyright notice in the Description page of Project Settings.


#include "Floorpiece.h"

#include "Components/BoxComponent.h"

// Sets default values
AFloorpiece::AFloorpiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(false);
	RootComponent = Mesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxComponent->InitBoxExtent({ 50.0f, 50.0f, 10.0f });

	BoxComponent->CanCharacterStepUpOn = ECB_No;
	BoxComponent->SetShouldUpdatePhysicsVolume(true);
	BoxComponent->SetCanEverAffectNavigation(false);
	BoxComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AFloorpiece::BeginPlay()
{
	Super::BeginPlay();

}

void AFloorpiece::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (IsValid(Mesh))
	{
		MeshBoundsY = Mesh->Bounds.BoxExtent.Y * 2;
		UE_LOG(LogTemp, Log, TEXT("Spawned successfully! New Actor: %f"), MeshBoundsY);
	}
}

// Called every frame
void AFloorpiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorpiece::MoveFloorpiece(FVector NewLocation)
{
	AddActorWorldOffset(NewLocation);


}
