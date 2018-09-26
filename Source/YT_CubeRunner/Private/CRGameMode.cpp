// Fill out your copyright notice in the Description page of Project Settings.

#include "CRGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ACRGameMode::ACRGameMode()
{
    CurrentLevelIndex = 0;
}

void ACRGameMode::BeginPlay()
{
    Super::BeginPlay();

    Controller = GetWorld()->GetFirstPlayerController();

    FInputModeGameOnly InputMode;
    Controller->SetInputMode(InputMode);
    Controller->bShowMouseCursor = false;

    CheckLevel();

}

void ACRGameMode::CheckLevel()
{
   // FString CurrentLevelName = GetWorld()->GetMapName();

    FString CurrentLevelName = CleanLevelString(GetWorld());


    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Level Name: ") + CurrentLevelName);
   // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Index Before Find: ") + FString::FromInt(CurrentLevelIndex));
    Levels.Find(CurrentLevelName, CurrentLevelIndex);
   // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Index AFter Find: ") + FString::FromInt(CurrentLevelIndex));

    if(CurrentLevelIndex < Levels.Num() - 1)
    {
        NextLevel = Levels[CurrentLevelIndex + 1];
    }
    else
    {
        NextLevel = "End";
    }
}

void ACRGameMode::EndGame()
{
    FString LevelString = GetWorld()->GetMapName();
    FName LevelToLoad = FName(*LevelString);

    UGameplayStatics::OpenLevel(this, LevelToLoad, true);
}

void ACRGameMode::LevelComplete()
{
    if(DefaultLevelCompleteWidget)
    {
        LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
        LevelCompleteWidget->AddToViewport();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Default Level Complete Widget Selected!!"));
    }

    GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ACRGameMode::LoadNextLevel, 2.0f, false);
}

void ACRGameMode::LoadNextLevel()
{
    if(Levels.Contains(NextLevel))
    {
        FName LevelToLoad = FName(*NextLevel);
        UGameplayStatics::OpenLevel(this, LevelToLoad, true);
    }
    else
    {
        if(LevelCompleteWidget)
        {
            LevelCompleteWidget->RemoveFromParent();

            if(DefaultGameCompleteWidget)
            {
                GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
                GameCompleteWidget->AddToViewport();

                Controller->bShowMouseCursor = true;
                FInputModeUIOnly InputMode;
                Controller->SetInputMode(InputMode);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("No Default Game Complete Widget Selected!!"));
            }
        }
    }

}

FString ACRGameMode::CleanLevelString(UObject* WorldContextObject)
{
    if(GEngine)
    {
        FString Prefix = GEngine->GetWorldFromContextObject(WorldContextObject)->StreamingLevelsPrefix;
        FString LevelName = GetWorld()->GetMapName();

        return LevelName.RightChop(Prefix.Len());
    }
    return "No map Found";
}