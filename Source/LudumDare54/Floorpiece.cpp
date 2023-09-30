// Fill out your copyright notice in the Description page of Project Settings.


#include "Floorpiece.h"

// Sets default values
AFloorpiece::AFloorpiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AFloorpiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorpiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

