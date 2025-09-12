// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

UActionButton::UActionButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UActionButton::NativeConstruct()
{
	Super::NativeConstruct();
	ActionButton->OnClicked.AddDynamic(this, &UActionButton::OnActionClicked);
}
void UActionButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UActionButton::OnActionClicked()
{
	ActionDelegateHandle.Broadcast();
}
