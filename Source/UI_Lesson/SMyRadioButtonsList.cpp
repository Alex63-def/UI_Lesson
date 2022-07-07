// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyRadioButtonsList.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
// ������ ����� ������� ������� ����
/*
void SMyRadioButtonsList::Construct(const FArguments& InArgs)
{
	CurrentChoice = ERadioChoice::Radio0; // ������ ���� ����� �����
	
	ChildSlot // ��� ��� ������ � �������� � ������ ����� �����
	[
		// Populate the widget
		// ��� ��������� ������� ����������� ����� SNew()
		// ��� ���� ���� ��������� U � ����������� S
		SNew(SVerticalBox) 
		+SVerticalBox::Slot() // ������ ������� ����� �������� �����
		[
			SNew(SCheckBox)																		// 3 ����� - ���� ������ ������
			.IsChecked(MakeAttributeRaw(this, &SMyRadioButtonsList::IsRadioButtonChecked, ERadioChoice::Radio0)) // ��� ������� �������� ������� �������� �� ����� �� �� - ����� ������ ��� ����� ���� ��� - MakeAttributeRaw- ������ ������� � ������ ��� ��� �������
			.OnCheckStateChanged(this, &SMyRadioButtonsList::HandleRadioButtonStateChanged, ERadioChoice::Radio0) // �������������� �� ������� - ��������� ����� ����� ���� ������ ����������
			[
				SNew(STextBlock) // ��� ��������� - ����, ������, ����� - ���������� ����� ����� � ��� ���������
				.Text(FText::FromString("Option 1"))
			]
		]
		+ SVerticalBox::Slot() // ������ ������� ����� �������� �����
			[
				SNew(SCheckBox)
				[
					SNew(STextBlock) // ��� ��������� - ����, ������, ����� - ���������� ����� ����� � ��� ���������
					.Text(FText::FromString("Option 2"))
				]
			]
		+ SVerticalBox::Slot() // ������ ������� ����� �������� �����
			[
				SNew(SCheckBox)
				[
					SNew(STextBlock) // ��� ��������� - ����, ������, ����� - ���������� ����� ����� � ��� ���������
					.Text(FText::FromString("Option 3"))
				]
			]
	];
	
}
*/
void SMyRadioButtonsList::Construct(const FArguments& InArgs)
{
	// ������ � ��� ���������� ��� ����� �� ���������� � ������ ��� �� ����� ��� ��������� �� ������ ������
	OnRadioChoiceChanged = InArgs._OnRadioChoiceChanged;

	CurrentChoice = ERadioChoice::Radio0; // ������ ���� ����� �����

	// �������� ��� ��� ��������� �����
	SetRadioButtonStyle(InArgs._Style);

	ChildSlot // ��� ��� ������ � �������� � ������ ����� �����
		[
			// Populate the widget
			// ��� ��������� ������� ����������� ����� SNew()
			// ��� ���� ���� ��������� U � ����������� S
			SNew(SVerticalBox)
			+ SVerticalBox::Slot() // ������ ������� ����� �������� �����
			[
				CreateRadioButton("Option 1", ERadioChoice::Radio0)
			]
			+ SVerticalBox::Slot() // ������ ������� ����� �������� �����
			[
				CreateRadioButton("Option 2", ERadioChoice::Radio1)
			]
			+ SVerticalBox::Slot() // ������ ������� ����� �������� �����
			[
				CreateRadioButton("Option 3", ERadioChoice::Radio2)
			]
		];
}

// ��������� ��� �������� ������ �����������
//void SMyRadioButtonsList::Construct(const FArguments& InArgs)
//{
//	// ������ � ��� ���������� ��� ����� �� ���������� � ������ ��� �� ����� ��� ��������� �� ������ ������
//	OnRadioChoiceChanged = InArgs._OnRadioChoiceChanged;
//
//	// ���� ����� � ��� �������� �� ���-�� ������ - ������ ���� - �������� ���� �� ������� 
//	CountCheckBox = InArgs._CountCheckBox;
//
//	CurrentChoice = ERadioChoice::Radio0; // ������ ���� ����� �����
//
//	ChildSlot // ��� ��� ������ � �������� � ������ ����� �����
//		[
//			//SAssignNew � �� ������� ����� ��������� ����� � ����������
//			SAssignNew(VerticalBox, SVerticalBox)
//		];
//}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//void SMyRadioButtonsList::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
//
//	// ����� �������� ��������, ����� ������� ������ 
//	//VerticalBox->ClearChildren();
//
//	/*VerticalBox->AddSlot()
//		[
//			
//		];*/
//}
//
//int32 SMyRadioButtonsList::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
//{
//	// ������������ ��� ���� ����� 
//	return int32();
//}

ECheckBoxState SMyRadioButtonsList::IsRadioButtonChecked(ERadioChoice RadioButtonID)
{
	// ������ ��� ���� ��������� ������ ���� � ������ ��� ���������� ��������� �� ��������, ���� ��� �� ������ ��������� �������
	return (CurrentChoice == RadioButtonID) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SMyRadioButtonsList::HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, ERadioChoice RadioButtonID)
{
	if (NewRadioState == ECheckBoxState::Checked) // ���� ����� ���� ����� �� ������ ������� ������
	{
		CurrentChoice = RadioButtonID;

		// ����� ������ ��������� ��������� �� ���� - ��������� �������
		OnRadioChoiceChanged.ExecuteIfBound(CurrentChoice); // �������� ����� �������� ���� ����������� �� �������
	}
}

TSharedRef<SWidget> SMyRadioButtonsList::CreateRadioButton(const FString& RadioText, ERadioChoice RadioButtonChoice)
{
	return SNew(SCheckBox)																		// 3 ����� - ���� ������ ������
		.IsChecked(MakeAttributeRaw(this, &SMyRadioButtonsList::IsRadioButtonChecked, RadioButtonChoice)) // ��� ������� �������� ������� �������� �� ����� �� �� - ����� ������ ��� ����� ���� ��� - MakeAttributeRaw- ������ ������� � ������ ��� ��� �������
		.OnCheckStateChanged(this, &SMyRadioButtonsList::HandleRadioButtonStateChanged, RadioButtonChoice) // �������������� �� ������� - ��������� ����� ����� ���� ������ ����������
		.Style(CheckBoxStyle) // ��������� �������� ������� ��������� � ����� ����������
		[
			SNew(STextBlock) // ��� ��������� - ����, ������, ����� - ���������� ����� ����� � ��� ���������
			.Text(FText::FromString(RadioText))
			.TextStyle(TextStyle) // ��������� �������� ������� ��������� � ����� ����������
		];
}

void SMyRadioButtonsList::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
{
	// �� ��� �������� � ������� ������ � ��� ���������� ��� ������
	CheckBoxStyle = &InStyle->CheckBoxStyle;
	TextStyle = &InStyle->TextStyle;
}

