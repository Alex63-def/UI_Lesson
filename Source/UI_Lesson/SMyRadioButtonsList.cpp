// Fill out your copyright notice in the Description page of Project Settings.


#include "SMyRadioButtonsList.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
// сделал более удобный вариант ниже
/*
void SMyRadioButtonsList::Construct(const FArguments& InArgs)
{
	CurrentChoice = ERadioChoice::Radio0; // первый бокс будет нажат
	
	ChildSlot // это как дерево в виджетах в движке слева внизу
	[
		// Populate the widget
		// все слейтовые виджеты добавляются через SNew()
		// все юмдж имею приставку U а слейтовские S
		SNew(SVerticalBox) 
		+SVerticalBox::Slot() // теперь добавим детей вертикал боксу
		[
			SNew(SCheckBox)																		// 3 парам - энам первой кнопки
			.IsChecked(MakeAttributeRaw(this, &SMyRadioButtonsList::IsRadioButtonChecked, ERadioChoice::Radio0)) // это атрибут чекбокса который отвечает за нажат ли он - будем делать это через нашу фун - MakeAttributeRaw- биндим функцию и делаем это как делегат
			.OnCheckStateChanged(this, &SMyRadioButtonsList::HandleRadioButtonStateChanged, ERadioChoice::Radio0) // подиписываемся на собитые - перендаем парам какой кноп сейчас пользуемся
			[
				SNew(STextBlock) // все параметры - цвет, размер, текст - вызываются через точку и имя параметра
				.Text(FText::FromString("Option 1"))
			]
		]
		+ SVerticalBox::Slot() // теперь добавим детей вертикал боксу
			[
				SNew(SCheckBox)
				[
					SNew(STextBlock) // все параметры - цвет, размер, текст - вызываются через точку и имя параметра
					.Text(FText::FromString("Option 2"))
				]
			]
		+ SVerticalBox::Slot() // теперь добавим детей вертикал боксу
			[
				SNew(SCheckBox)
				[
					SNew(STextBlock) // все параметры - цвет, размер, текст - вызываются через точку и имя параметра
					.Text(FText::FromString("Option 3"))
				]
			]
	];
	
}
*/
void SMyRadioButtonsList::Construct(const FArguments& InArgs)
{
	// кладем в эту ерпеменную наш эвент из аргументов в хедере что бы потом шли изменения из слейта наружу
	OnRadioChoiceChanged = InArgs._OnRadioChoiceChanged;

	CurrentChoice = ERadioChoice::Radio0; // первый бокс будет нажат

	// вызываем фун для изменения стиля
	SetRadioButtonStyle(InArgs._Style);

	ChildSlot // это как дерево в виджетах в движке слева внизу
		[
			// Populate the widget
			// все слейтовые виджеты добавляются через SNew()
			// все юмдж имею приставку U а слейтовские S
			SNew(SVerticalBox)
			+ SVerticalBox::Slot() // теперь добавим детей вертикал боксу
			[
				CreateRadioButton("Option 1", ERadioChoice::Radio0)
			]
			+ SVerticalBox::Slot() // теперь добавим детей вертикал боксу
			[
				CreateRadioButton("Option 2", ERadioChoice::Radio1)
			]
			+ SVerticalBox::Slot() // теперь добавим детей вертикал боксу
			[
				CreateRadioButton("Option 3", ERadioChoice::Radio2)
			]
		];
}

// констракт для создания боксов динамически
//void SMyRadioButtonsList::Construct(const FArguments& InArgs)
//{
//	// кладем в эту ерпеменную наш эвент из аргументов в хедере что бы потом шли изменения из слейта наружу
//	OnRadioChoiceChanged = InArgs._OnRadioChoiceChanged;
//
//	// тоже самое и для атрибута по кол-ву боксов - смотри выше - попадает сюда из обертки 
//	CountCheckBox = InArgs._CountCheckBox;
//
//	CurrentChoice = ERadioChoice::Radio0; // первый бокс будет нажат
//
//	ChildSlot // это как дерево в виджетах в движке слева внизу
//		[
//			//SAssignNew с ее помощью можем запихнуть класс в переменную
//			SAssignNew(VerticalBox, SVerticalBox)
//		];
//}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//void SMyRadioButtonsList::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
//
//	// когда меняется значение, нужно чистить старые 
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
//	// используется для мини карты 
//	return int32();
//}

ECheckBoxState SMyRadioButtonsList::IsRadioButtonChecked(ERadioChoice RadioButtonID)
{
	// каждый чек бокс проверяет только себя и каждый раз сравнивает совпадает ли айдишник, если нет то всегда выключает галочку
	return (CurrentChoice == RadioButtonID) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SMyRadioButtonsList::HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, ERadioChoice RadioButtonID)
{
	if (NewRadioState == ECheckBoxState::Checked) // если новый бокс нажат то меняем текущий статус
	{
		CurrentChoice = RadioButtonID;

		// когда статус изменился оповещаем об этом - запускаем делегат
		OnRadioChoiceChanged.ExecuteIfBound(CurrentChoice); // передаем новый параметр всем подписанным на событие
	}
}

TSharedRef<SWidget> SMyRadioButtonsList::CreateRadioButton(const FString& RadioText, ERadioChoice RadioButtonChoice)
{
	return SNew(SCheckBox)																		// 3 парам - энам первой кнопки
		.IsChecked(MakeAttributeRaw(this, &SMyRadioButtonsList::IsRadioButtonChecked, RadioButtonChoice)) // это атрибут чекбокса который отвечает за нажат ли он - будем делать это через нашу фун - MakeAttributeRaw- биндим функцию и делаем это как делегат
		.OnCheckStateChanged(this, &SMyRadioButtonsList::HandleRadioButtonStateChanged, RadioButtonChoice) // подиписываемся на собитые - перендаем парам какой кноп сейчас пользуемся
		.Style(CheckBoxStyle) // вставляем аргумент который храниться в нашей переменной
		[
			SNew(STextBlock) // все параметры - цвет, размер, текст - вызываются через точку и имя параметра
			.Text(FText::FromString(RadioText))
			.TextStyle(TextStyle) // вставляем аргумент который храниться в нашей переменной
		];
}

void SMyRadioButtonsList::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
{
	// то что получили в принтах кладем в две переменные для стилей
	CheckBoxStyle = &InStyle->CheckBoxStyle;
	TextStyle = &InStyle->TextStyle;
}

