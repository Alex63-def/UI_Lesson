// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"

class UI_LESSON_API FStyleSet
{
public:
	static void Initialize(); // создает стиль
	static void Shutdown(); // освобождает из памяти 
	static const ISlateStyle& Get(); // получает 

private:
	static TSharedPtr<class ISlateStyle> StylePtr; // переменная содержающая данный стиль
};