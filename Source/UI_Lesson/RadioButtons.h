// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMyRadioButtonsList.h" // добавляем слейтовский класс 
#include "Components/Widget.h"
#include "RadioButtons.generated.h"

/**
 * 
 */

// этот делегат делаем для отправки инфы в принты - должен быть мультикаст
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioChoiceChangedEvent, ERadioChoice, NewRadioChoice);

// это наша обертка для слейтовского класса
UCLASS()
class UI_LESSON_API URadioButtons : public UWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "RadioButtons|Event") // отправляем делегат в принты
	FOnRadioChoiceChangedEvent OnRadioChoiceChanged;

	// переменная для стиля виджета - она хранит сразу два стиля - для бокса и текста в виде структуры
	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FRadioButtonsStyle WidgetStyle;
	
public:
	// при удалении виджета эта функция будет освобождать память
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:
	// создание и инициализация виджета
	virtual TSharedRef<SWidget> RebuildWidget() override;

	// для передачи инфы по делегату в принты
	void HandleOnRadioChoiceChanged(ERadioChoice NewRadioChoise);

	//int32 GetCountCheckBox() const;

protected:
	TSharedPtr<SMyRadioButtonsList> MyRadioButtons; // переменная будет хранить виджет

	//UPROPERTY(/*надо прописать*/)
	//int32 CountCheckBox; // для кол-ва боксов
};
