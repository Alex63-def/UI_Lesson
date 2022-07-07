// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadioButtons.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_LESSON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// используется только для просмотра изменений в эдиторе и использовать тулько для визуальных вещей - стилей
	virtual void NativePreConstruct() override; // показывается еще все в эдиторе до создания виджета

	// констракт не обязателен, без него уже работал виджет
		// в нем обычно биндятся на различные события
	virtual void NativeConstruct() override; // собирается и делается когда виджет добавляется на экран уже

protected:
								// BindWidgetOptional - если не создадим в виджете эту кнопку, то будет предупреждение, но ругать не будет и можно работать дальше
	UPROPERTY(meta = (BindWidgetOptional)) // meta связывает кнопку из плюсов с кнопкой в принтах по названию
	class UButton* NewGameButtom;		// BindWidget - если кнопки не будет в виджете то будет ругаться и не будет работать

	UPROPERTY(Transient, meta = (BindWidgetAnim))  // для анимации Transient
	class UWidgetAnimation* TestAnimation;	// тоже должно совпадать название в виджете

	UPROPERTY(meta = (BindWidgetOptional)) 
	URadioButtons* RadioButton; // создали пользовательский виджет и будем менять в нем стиль

protected:

	UFUNCTION()
	void OnNewGameClicked();
};
