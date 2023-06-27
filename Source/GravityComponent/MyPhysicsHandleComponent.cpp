// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPhysicsHandleComponent.h"
#include "MyPhysicsHandleComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GravityComponentCharacter.h"
#include "DrawDebugHelpers.h"

//TODO - ������, ���� ���� �������� �������� ������������ �� ����� �� 1, ������� ��� �������� �������� �� ����� (��������, �� �������� 0.6)
//� ������� ���, ����� ����� ����, ��� �� ����������� � �����, �� ������ �� �����������, �� ��� ����� ���� �������.
UMyPhysicsHandleComponent::UMyPhysicsHandleComponent()
{
	InterpolatedValue = 0.f;
	MaxAllowableMass = 5000.f;
	LineTraceComponent = CreateDefaultSubobject<UMyLineTraceComponent>(TEXT("LineTraceComponent"));
}

void UMyPhysicsHandleComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGravityComponentCharacter>(GetOwner());
	if (Character)
	{
		UInputComponent* OwnersInputComponent = Character->InputComponent;
		OwnersInputComponent->BindAction("StartDragComponent", EInputEvent::IE_Pressed, this, &UMyPhysicsHandleComponent::StartDragComponent);
		OwnersInputComponent->BindAction("StopDragComponent", EInputEvent::IE_Pressed, this, &UMyPhysicsHandleComponent::StopDragComponent);
	}
}

void UMyPhysicsHandleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Character && GetGrabbedComponent())
	{
		//FVector SphereRadiusLocation = GetSphereEdgeLocation();
		//float GrabbedComponentsLocationLength = GetGrabbedComponent()->GetComponentLocation().Size();
		//float SphereEdgeLocationLength = SphereRadiusLocation.Size();
		//UE_LOG(LogTemp, Warning, TEXT("Component vector length: %f"), GrabbedComponentsLocationSizeSquared);
		//UE_LOG(LogTemp, Warning, TEXT("Sphere vector length: %f"), SphereRadiusPositionSizeSquared);

		//TODO ���������� ����������, ���� ������� ����������� ��������� ����� � �����.
		// 
		//bool AreVectorLengthsEqual = FMath::IsNearlyEqual(GrabbedComponentsLocationLength, SphereEdgeLocationLength, 20.f);
		//if (!AreVectorLengthsEqual)
		//{
		//}

		if (InterpolatedValue >= 1.f)
		{
			InterpolatedValue = 0.f;
		}
		DoShifting();
	}
}

void UMyPhysicsHandleComponent::StartDragComponent()
{
	UPrimitiveComponent* TracedComponent = LineTraceComponent->DoLineTrace();
	if (TracedComponent)
	{
		if (!(TracedComponent->Mobility == EComponentMobility::Movable))
		{
			UE_LOG(LogTemp, Error, TEXT("Traced component is not movable. It Cannot be dragged."));
		}
		else
		{
			float TracedComponentMass = TracedComponent->GetMass();
			if (TracedComponentMass <= MaxAllowableMass)
			{
				CurrentGrabbedComponentMass = TracedComponentMass;
				GrabComponentAtLocation(TracedComponent, NAME_None, TracedComponent->GetComponentLocation());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(
					"Mass of the traced component is too much. Max allowable mass : %f, traced component mass : %f."),
					MaxAllowableMass,
					TracedComponentMass);
			}
		}
	}
}

void UMyPhysicsHandleComponent::StopDragComponent()
{
	if (GetGrabbedComponent())
	{
		UPrimitiveComponent* GrabbedPrimitiveComponent = GetGrabbedComponent();
		ReleaseComponent();
		FVector CameraForwardVector = Character->GetFirstPersonCameraComponent()->GetForwardVector();
		FVector DirectionImpulse = CameraForwardVector * 3700.f;

		UE_LOG(LogTemp, Warning, TEXT("Directional impulse: %s"), *DirectionImpulse.ToString());

		GrabbedPrimitiveComponent->AddImpulse(DirectionImpulse, NAME_None, true);
		InterpolatedValue = 0.f;
	}
}

void UMyPhysicsHandleComponent::DoShifting()
{
	InterpolatedValue += 1 / CurrentGrabbedComponentMass;

	FVector GrabbedComponentLocation = GetGrabbedComponent()->GetComponentLocation();
	FVector SphereEdgeLocation = GetSphereEdgeLocation();
	FVector InterpolatedLocation = FMath::Lerp(GrabbedComponentLocation, SphereEdgeLocation, InterpolatedValue);

	UE_LOG(LogTemp, Warning, TEXT("�urrent location vector length: %f, Sphere location vector length: %f"), InterpolatedLocation.Size(), SphereEdgeLocation.Size());

	DrawDebugLine(GetWorld(), Character->GetActorLocation(), SphereEdgeLocation, FColor(128, 0, 128), false, 1.f, 0.f, 1.f);
	SetTargetLocation(InterpolatedLocation);
}

FVector UMyPhysicsHandleComponent::GetSphereEdgeLocation()
{
	FVector CharacterLocation = Character->GetActorLocation();
	FVector CameraForwardVector = Character->GetFirstPersonCameraComponent()->GetForwardVector();
	FVector SphereRadius = CameraForwardVector * Character->GetSphereRadius();
	FVector SphereEdgeLocation = CharacterLocation + SphereRadius;
	return SphereEdgeLocation;
}