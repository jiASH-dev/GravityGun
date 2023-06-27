// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GravityComponentHUD.generated.h"

UCLASS()
class AGravityComponentHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGravityComponentHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

