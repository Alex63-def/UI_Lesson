// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioButtonsWidgetStyle.h" // FRadioButtonsStyle
#include "Widgets/SCompoundWidget.h"

UENUM(BlueprintType)
enum class ERadioChoice : uint8
{
	Radio0, // ���������� ����� �� ���� ��������� �����
	Radio1,
	Radio2
};

DECLARE_DELEGATE_OneParam(FOnRadioChoiceChanged, ERadioChoice /*NewRadioChoice*/); // FOnRadioChoi�eChanged - �������� ������
												// ERadioChoice - �������� ������� ��������
/**
 * 
 */
class UI_LESSON_API SMyRadioButtonsList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyRadioButtonsList)
	{}
		
		// ������� � ��� ��� � ��� ���� ����� � ��������� FOnRadioChoi�eChanged
		SLATE_EVENT(FOnRadioChoiceChanged, OnRadioChoiceChanged) // OnRadioChoi�eChanged ��� ���������� ��������

		//SLATE_ATTRIBUTE(int32, CountCheckBox) // ��������� ���������� ������� 

		SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style) // FRadioButtonsStyle - ��������� �� ������ 

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// ���� ����� ������ ��������� � ������� - �� ���� � ����� �������� - ������ �� ���-�� � �� - ��� �������� � ����
	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	// ������ ��������� �������� ������ ��� ����� ������������ ���-�� ������� - �� ���������� ������
	//virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
	ECheckBoxState IsRadioButtonChecked(ERadioChoice RadioButtonID); // ������ �� ���

	void HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, ERadioChoice RadioButtonID); // ����� ������ ������� �� ���������� ��������� 

	TSharedRef<SWidget> CreateRadioButton(const FString& RadioText, ERadioChoice RadioButtonChoice); // ������� ����� ��� �� ��������� ��� � ����������

	//��� ������� ��������� ��������� ����� � ������� 
	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);

protected:
	ERadioChoice CurrentChoice; // ������� ������� 
	FOnRadioChoiceChanged OnRadioChoiceChanged; // ��� ������ ���������� � ��������� � ��

	////���������� ��� ���� ��� �� ����������� ������ ���-�� ����� ��������
	//TSharedRef<SVerticalBox> VerticalBox;

	//// ���-�� ������
	//TAttribute<int32> CountCheckBox;

	// ��� ��� ���������� �������� ���� �� ������ ������
	// ��� ����� �����
	const FCheckBoxStyle* CheckBoxStyle;

	// ��� ����� ������
	const FTextBlockStyle* TextStyle;
};
