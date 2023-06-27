// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GravityComponentCharacter.h"
#include "MyLineTraceComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRAVITYCOMPONENT_API UMyLineTraceComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AGravityComponentCharacter* Character;

public:
	UPROPERTY(EditAnywhere)
	float GrabMaxDistance;

public:
	// Sets default values for this component's properties
	UMyLineTraceComponent();
	void BeginPlay() override;
	UPrimitiveComponent* DoLineTrace();
};
