// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemyActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class AIMTRAINER_API ABaseEnemyActor : public AActor
{
	GENERATED_BODY()

public:

	ABaseEnemyActor();

	UStaticMeshComponent* GetStaticMesh() const { return StaticMeshComponent; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	virtual void BeginPlay() override;
};
