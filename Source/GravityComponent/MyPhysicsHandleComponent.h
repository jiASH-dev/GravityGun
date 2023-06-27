// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyLineTraceComponent.h"
#include "GravityComponentCharacter.h"
#include "MyPhysicsHandleComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRAVITYCOMPONENT_API UMyPhysicsHandleComponent : public UPhysicsHandleComponent
{
	GENERATED_BODY()

private:
	float CurrentGrabbedComponentMass;
	AGravityComponentCharacter* Character;

public:
	UPROPERTY(EditAnywhere)
	UMyLineTraceComponent* LineTraceComponent;
	float InterpolatedValue;
	UPROPERTY(EditAnywhere)
	float MaxAllowableMass;

public:
	UMyPhysicsHandleComponent();
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void StartDragComponent();
	void StopDragComponent();

private:
	FVector GetSphereEdgeLocation();
	void DoShifting();
};
