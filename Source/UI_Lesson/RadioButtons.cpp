// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyRadioButtons.Reset(); // nullptr
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	MyRadioButtons = SNew(SMyRadioButtonsList) // создаем наш виджет
		// что бы работал делегат из слейта биндимся на него
		.OnRadioChoiceChanged(BIND_UOBJECT_DELEGATE(FOnRadioChoiceChanged, HandleOnRadioChoiceChanged)) // когда слейт будет присылать инфу что что-то поменялось то тут мы будем отправлять инфу об изменениях в принты
		//.CountCheckBox(GetCountCheckBox()); // из принтов получаем переменную и передаем ее слейту и там уже перерисовывается все

		.Style(&WidgetStyle); // передаем переменную хранящую стили 

	return MyRadioButtons.ToSharedRef(); // ToSharedRef - преобразует указатель в ссылку, так как у нас умный птр
}

void URadioButtons::HandleOnRadioChoiceChanged(ERadioChoice NewRadioChoise)
{
	// проверяем есть ли подписки на мультикастовый делегат
	if (OnRadioChoiceChanged.IsBound())
	{
		OnRadioChoiceChanged.Broadcast(NewRadioChoise); // передаем в принты
	}
}

//int32 URadioButtons::GetCountCheckBox() const
//{
//	return CountCheckBox;
//}
