// Fill out your copyright notice in the Description page of Project Settings.

#include "StyleSet.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"

// эта функция в инклуде #include "Styling/ISlateStyle.h" поэтому ее нет в хедере
TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory)
{
	// тут мы только находим наш стиль в движке какой задали в принтах в слейт виджет стайл и сохраняем в переменную
	TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("StyleSet"),ScopeToDirectory, ScopeToDirectory);
	
	return Style;
}

TSharedPtr<ISlateStyle> FStyleSet::StylePtr = NULL; // так как нет конструктора то при создании файла в игре присваиваем ему ноль

void FStyleSet::Initialize()
{
	Shutdown(); // сначала всегда освобождаем памят а потом перезаписываем

	StylePtr = FindStyle("/Game/UI/Styles"); // тут путь принта слейт виджет стайл - вообще это ассет

	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr); // регистрируем наш стиль
}

void FStyleSet::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr); // отрегестрировать стиль

		ensure(StylePtr.IsUnique()); // проверяет есть ли стиль все еще иначе краш - можно и без этой строчки

		StylePtr.Reset(); // что-то делает у умных указателей - почитать
	}
}

const ISlateStyle& FStyleSet::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}

	return *StylePtr;
}
