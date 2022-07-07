// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI_LessonHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AUI_LessonHUD::AUI_LessonHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AUI_LessonHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AUI_LessonHUD::BeginPlay()
{
	Super::BeginPlay();

	// настраиваем состояние инпут моде - можем ли мы играть пока горит виджет
	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();

		if (PC)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, nullptr, EMouseLockMode::DoNotLock, false); // это библиотека виртуальных абстракных статических фун - в ней мы можем поменять инпут мод -1- контроллер -2- виджет но сейчас его нет поэтому нулптр -3- мы можем крутить камеру мышкой -4- скрывать ли курсор
			PC->bShowMouseCursor = true; // для уверенности что она будет
		}
	}

	UseWidget(EWidgetID::PauseMenu, true, 0);
}

UUserWidget* AUI_LessonHUD::UseWidget(EWidgetID WidgetID, bool RemovePrevios, int32 ZOrder)
{
	if (WidgetID == CurrentWidgetID)
	{
		return CurrentWidget;
	}
	
	if (RemovePrevios)
	{
		RemoveCurrentWidgetFromViewport();
	}

	const TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClasses.FindRef(WidgetID); // FindRef - поиск по ключу

	if (WidgetClassToUse.Get()) // так как это TSubclassOf надо получать валидность через гет - то есть ссылку
	{
		CurrentWidgetID = WidgetID;
		UUserWidget* SpawnedWidged = AddWidgetToViewportByClass(WidgetClassToUse);
		return SpawnedWidged;
	}

	return nullptr;
}

UUserWidget* AUI_LessonHUD::GetCurrentWidget() const
{
	return CurrentWidget;
}

void AUI_LessonHUD::RemoveCurrentWidgetFromViewport()
{
	// если сейчас нет никаких виджетов то ничего и не делаем 
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();	// это просто удаляет с экрана
		CurrentWidget = nullptr;			// поэтому обнуляем 

		CurrentWidgetID = EWidgetID::None;	// доложны задать сотояние и энама 
	}
}

UUserWidget* AUI_LessonHUD::AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass); 

	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport(ZOrder);
	}
	
	return CurrentWidget;
}
