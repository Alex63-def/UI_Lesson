// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioButtonsWidgetStyle.h" // FRadioButtonsStyle
#include "Widgets/SCompoundWidget.h"

UENUM(BlueprintType)
enum class ERadioChoice : uint8
{
	Radio0, // показывает какой из трех чекбоксов горит
	Radio1,
	Radio2
};

DECLARE_DELEGATE_OneParam(FOnRadioChoiceChanged, ERadioChoice /*NewRadioChoice*/); // FOnRadioChoiсeChanged - название эвента
												// ERadioChoice - параметр который меняется
/**
 * 
 */
class UI_LESSON_API SMyRadioButtonsList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyRadioButtonsList)
	{}
		
		// говорим о том что у нас есть эвент с названием FOnRadioChoiсeChanged
		SLATE_EVENT(FOnRadioChoiceChanged, OnRadioChoiceChanged) // OnRadioChoiсeChanged это переменная делегата

		//SLATE_ATTRIBUTE(int32, CountCheckBox) // добавляем переменную атрибут 

		SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style) // FRadioButtonsStyle - структура из стилей 

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// если хотим делать изменения в виджете - то есть в радио баттонах - менять их кол-во и тп - это делается в тике
	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	// делает отрисовку видлжета каждый раз через определенное кол-во времени - не используем сейчас
	//virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
	ECheckBoxState IsRadioButtonChecked(ERadioChoice RadioButtonID); // нажата ли она

	void HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, ERadioChoice RadioButtonID); // когда меняем галочку то предыдушая стирается 

	TSharedRef<SWidget> CreateRadioButton(const FString& RadioText, ERadioChoice RadioButtonChoice); // создает боксы что бы сократить код в констракте

	//фун которая принимает аргументы стиля в принтах 
	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);

protected:
	ERadioChoice CurrentChoice; // текущая нажатая 
	FOnRadioChoiceChanged OnRadioChoiceChanged; // она хранит информацию о подписках и тд

	////переменная для того что бы динамически менять кол-во радио баттонов
	//TSharedRef<SVerticalBox> VerticalBox;

	//// кол-во боксов
	//TAttribute<int32> CountCheckBox;

	// эти две переменные получают инфу из класса стилей
	// для стиля бокса
	const FCheckBoxStyle* CheckBoxStyle;

	// для стиля текста
	const FTextBlockStyle* TextStyle;
};
