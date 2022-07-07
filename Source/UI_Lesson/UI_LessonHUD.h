// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI_LessonHUD.generated.h"

UENUM()
enum class EWidgetID : uint8
{
	None, // когда никакого виджета никакого нету
	MainMenu,
	PauseMenu,
	Settings
};

UCLASS()
class AUI_LessonHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUI_LessonHUD();

public:
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

public:
	UUserWidget* UseWidget(EWidgetID WidgetID, bool RemovePrevios = true, int32 ZOrder = 0); // меняет виджеты на экране - 1- на какой виджет менять -2- удалить предыдущий -3- 

	UUserWidget* GetCurrentWidget() const; 

	void RemoveCurrentWidgetFromViewport();

	UUserWidget* AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);

protected:
	UPROPERTY()
	UUserWidget* CurrentWidget; // это виджет который сейчас на экране

	EWidgetID CurrentWidgetID; // название виджета - его текущее состояние из энама


protected:
	UPROPERTY(EditAnywhere)
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClasses; // тут массив виджетов выбираемых по ключу
	
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

