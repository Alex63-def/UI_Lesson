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
	// ������������ ������ ��� ��������� ��������� � ������� � ������������ ������ ��� ���������� ����� - ������
	virtual void NativePreConstruct() override; // ������������ ��� ��� � ������� �� �������� �������

	// ��������� �� ����������, ��� ���� ��� ������� ������
		// � ��� ������ �������� �� ��������� �������
	virtual void NativeConstruct() override; // ���������� � �������� ����� ������ ����������� �� ����� ���

protected:
								// BindWidgetOptional - ���� �� �������� � ������� ��� ������, �� ����� ��������������, �� ������ �� ����� � ����� �������� ������
	UPROPERTY(meta = (BindWidgetOptional)) // meta ��������� ������ �� ������ � ������� � ������� �� ��������
	class UButton* NewGameButtom;		// BindWidget - ���� ������ �� ����� � ������� �� ����� �������� � �� ����� ��������

	UPROPERTY(Transient, meta = (BindWidgetAnim))  // ��� �������� Transient
	class UWidgetAnimation* TestAnimation;	// ���� ������ ��������� �������� � �������

	UPROPERTY(meta = (BindWidgetOptional)) 
	URadioButtons* RadioButton; // ������� ���������������� ������ � ����� ������ � ��� �����

protected:

	UFUNCTION()
	void OnNewGameClicked();
};
