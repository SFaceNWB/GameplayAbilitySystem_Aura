// SFaceNWB Game

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

protected:
	virtual void BeginPlay() override;
	void OnHit();
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereIverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;
private:

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.0f;
	
	bool bHit = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
