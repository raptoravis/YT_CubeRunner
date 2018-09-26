// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRObstacle.generated.h"

UCLASS()
class YT_CUBERUNNER_API ACRObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Setup")
	UStaticMeshComponent* Cube;
};
