// SFaceNWB Game


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.0f, FVector::UpVector);
	TArray<FVector> SpawnLocation;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.0f, 0.0f, 400.0f), ChosenSpawnLocation - FVector(0.0f, 0.0f, 400.0f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}

		SpawnLocation.Add(ChosenSpawnLocation);
	}

	return SpawnLocation;
}
