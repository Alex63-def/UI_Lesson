// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "RadioButtonsWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct UI_LESSON_API FRadioButtonsStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

public:
	FRadioButtonsStyle();
	virtual ~FRadioButtonsStyle();

	// для стиля бокса
	UPROPERTY(EditAnywhere, Category = Appearance)
	FCheckBoxStyle CheckBoxStyle;
	
	// для стиля текста
	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextStyle;


	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override; // это параметры чем мы будем рисовать
	static const FName TypeName; 
	virtual const FName GetTypeName() const override { return TypeName; }; // возвращает тип слейтовской структуры и остального
	static const FRadioButtonsStyle& GetDefault(); // стиль по-умолчанию
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class URadioButtonsWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FRadioButtonsStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
