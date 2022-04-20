

#include "Testing_GameMode.h"

ATesting_GameMode::ATesting_GameMode() {

	PrimaryActorTick.bCanEverTick = true;

}

void ATesting_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATesting_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &ATesting_GameMode::SpawnCoins, 
		FMath::FRandRange(3, 5), true);
}

void ATesting_GameMode::SpawnCoins()
{
	float RandX = FMath::FRandRange(MinSpawnAxisX, MaxSpawnAxisX);
	float RandY = FMath::FRandRange(MinSpawnAxisY, MaxSpawnAxisY);

	FVector SpawnPos = FVector(RandX, RandY, SpawnAxisZ);
	FRotator SpawnRot = FRotator(0.f, 0.f, 0.f);

	GetWorld()->SpawnActor(CoinRecharge, &SpawnPos, &SpawnRot);
}
