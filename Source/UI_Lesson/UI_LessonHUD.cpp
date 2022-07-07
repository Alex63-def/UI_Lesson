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

	// ����������� ��������� ����� ���� - ����� �� �� ������ ���� ����� ������
	const UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PC = World->GetFirstPlayerController();

		if (PC)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, nullptr, EMouseLockMode::DoNotLock, false); // ��� ���������� ����������� ���������� ����������� ��� - � ��� �� ����� �������� ����� ��� -1- ���������� -2- ������ �� ������ ��� ��� ������� ������ -3- �� ����� ������� ������ ������ -4- �������� �� ������
			PC->bShowMouseCursor = true; // ��� ����������� ��� ��� �����
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

	const TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClasses.FindRef(WidgetID); // FindRef - ����� �� �����

	if (WidgetClassToUse.Get()) // ��� ��� ��� TSubclassOf ���� �������� ���������� ����� ��� - �� ���� ������
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
	// ���� ������ ��� ������� �������� �� ������ � �� ������ 
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();	// ��� ������ ������� � ������
		CurrentWidget = nullptr;			// ������� �������� 

		CurrentWidgetID = EWidgetID::None;	// ������� ������ �������� � ����� 
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
