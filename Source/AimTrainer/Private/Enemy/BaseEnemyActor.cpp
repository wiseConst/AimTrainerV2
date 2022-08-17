// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/BaseEnemyActor.h"
#include "Components/StaticMeshComponent.h"

ABaseEnemyActor::ABaseEnemyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(StaticMeshComponent);
}

void ABaseEnemyActor::BeginPlay()
{
	Super::BeginPlay();
}
