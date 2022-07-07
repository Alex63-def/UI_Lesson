// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "StyleSet.h"

void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (RadioButton)
	{																// класс стиля
		RadioButton->WidgetStyle = FStyleSet::Get().GetWidgetStyle<FRadioButtonsStyle>(FName("RadioButtonWidgetStyle")); // применяем стиль
	}																					// название ассета стиля в принтах
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// если на кнопке у нас стоит BindWidgetOptional - то мы должны проверить ее на валидность
	if (NewGameButtom)
	{
		// если кнопка есть подписываемся на событие клика на нее 
		NewGameButtom->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
	}
}

void UMainMenuWidget::OnNewGameClicked()
{
	PlayAnimation(TestAnimation);
}
