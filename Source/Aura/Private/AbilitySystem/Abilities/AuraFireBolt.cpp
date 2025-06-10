// SFaceNWB Game


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//����
			"<Title>FIRE BOLT</>\n\n"

			//�ȼ�
			"<Small>Level: </><Level>%d</>\n"
			//��������
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//��ȴʱ��
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			//�˺�
			"<Default>Launched a bolt of fire, exploding on impact and dealing: </><Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

			//ֵ
			Level,
			ManaCost,
			Cooldown,
			ScaleDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			//����
			"<Title>FIRE BOLT</>\n\n"

			//�ȼ�
			"<Small>Level: </><Level>%d</>\n"
			//��������
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//��ȴʱ��
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//�˺�
			"<Default>Launched %d bolts of fire, exploding on impact and dealing: </><Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles), 
			ScaleDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		//����
		"<Title>NEXT LEVEL</>\n\n"

		//�ȼ�
		"<Small>Level: </><Level>%d</>\n"
		//��������
		"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
		//��ȴʱ��
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//�˺�
		"<Default>Launched %d bolts of fire, exploding on impact and dealing: </><Damage>%d</>"
		"<Default> fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaleDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomeingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.0f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.0f, FVector::UpVector);

	//NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	
	if (NumProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			const FVector Start = SocketLocation + FVector(0, 0, 5);
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), 
				Start,
				Start + Direction * 75.0f,
				1,
				FLinearColor::Red,
				120,
				1);
		}
	}
	else
	{
		//��������Ͷ����
		const FVector Start = SocketLocation + FVector(0, 0, 5);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),
			Start,
			Start + Forward * 75.0f,
			1,
			FLinearColor::Red,
			120,
			1);
	}

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.0f, 1, FLinearColor::Green, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.0f, 1, FLinearColor::Gray, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.0f, 1, FLinearColor::Yellow, 120, 1);
}
