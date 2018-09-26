// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CREndPoint.generated.h"

UCLASS()
class YT_CUBERUNNER_API ACREndPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACREndPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Setup")
	class UBoxComponent* Box;
	
};
