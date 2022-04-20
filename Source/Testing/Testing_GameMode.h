

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/Actor.h"
#include "Testing_GameMode.generated.h"


UCLASS()
class TESTING_API ATesting_GameMode : public AGameMode
{
	GENERATED_BODY()

	ATesting_GameMode();
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> CoinRecharge;

	UPROPERTY(EditAnywhere)
		float MinSpawnAxisX;
	UPROPERTY(EditAnywhere)
		float MaxSpawnAxisX;

	UPROPERTY(EditAnywhere)
		float MinSpawnAxisY;
	UPROPERTY(EditAnywhere)
		float MaxSpawnAxisY;

	const float SpawnAxisZ = 600.f;

	void SpawnCoins();
};
