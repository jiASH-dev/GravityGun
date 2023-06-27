// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLineTraceComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "GravityComponentCharacter.h"

// Sets default values for this component's properties
UMyLineTraceComponent::UMyLineTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	GrabMaxDistance = 200.f;
}

void UMyLineTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	Character = Cast<AGravityComponentCharacter>(Owner);
	if (Character)
	{
		this->Character = Character;
	}
}

UPrimitiveComponent* UMyLineTraceComponent::DoLineTrace()
{
	if (Character)
	{
		FHitResult HitResult;
		FVector StartLocation = Character->GetActorLocation();
		FVector CentralLocation = Character->GetFirstPersonCameraComponent()->GetForwardVector() * GrabMaxDistance;
		FVector EndLocation = StartLocation + CentralLocation;
		bool IsSmthTraced = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
		if (IsSmthTraced)
		{
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(0, 128, 0), false, 1.f, 0.f, 1.f);
			return HitResult.GetComponent();
		}
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, 1.f, 0.f, 1.f);
		return nullptr;
	}
	return nullptr;
}
