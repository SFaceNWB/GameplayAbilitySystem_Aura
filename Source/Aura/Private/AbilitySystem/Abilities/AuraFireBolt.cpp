// SFaceNWB Game


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 DamageValue = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
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
			DamageValue);
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
			DamageValue);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 DamageValue = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
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
		DamageValue);
}