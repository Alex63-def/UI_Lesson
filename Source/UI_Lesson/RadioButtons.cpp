// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyRadioButtons.Reset(); // nullptr
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	MyRadioButtons = SNew(SMyRadioButtonsList) // ������� ��� ������
		// ��� �� ������� ������� �� ������ �������� �� ����
		.OnRadioChoiceChanged(BIND_UOBJECT_DELEGATE(FOnRadioChoiceChanged, HandleOnRadioChoiceChanged)) // ����� ����� ����� ��������� ���� ��� ���-�� ���������� �� ��� �� ����� ���������� ���� �� ���������� � ������
		//.CountCheckBox(GetCountCheckBox()); // �� ������� �������� ���������� � �������� �� ������ � ��� ��� ���������������� ���

		.Style(&WidgetStyle); // �������� ���������� �������� ����� 

	return MyRadioButtons.ToSharedRef(); // ToSharedRef - ����������� ��������� � ������, ��� ��� � ��� ����� ���
}

void URadioButtons::HandleOnRadioChoiceChanged(ERadioChoice NewRadioChoise)
{
	// ��������� ���� �� �������� �� �������������� �������
	if (OnRadioChoiceChanged.IsBound())
	{
		OnRadioChoiceChanged.Broadcast(NewRadioChoise); // �������� � ������
	}
}

//int32 URadioButtons::GetCountCheckBox() const
//{
//	return CountCheckBox;
//}
