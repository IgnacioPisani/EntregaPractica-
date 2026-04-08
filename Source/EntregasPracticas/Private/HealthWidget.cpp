// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Components/ProgressBar.h"

void UHealthWidget::UpdateBar(float Health, float MaxHealth)
{
	HealthProgressBar->SetPercent(Health / MaxHealth);
}
