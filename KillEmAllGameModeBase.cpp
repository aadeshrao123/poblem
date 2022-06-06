// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	AController* PawnController = Cast<AController>(PawnKilled->GetController());
	if (PawnController)
	{
		EndGame(false);
	}
	
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}


void AKillEmAllGameModeBase::EndGame(bool IsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == IsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
