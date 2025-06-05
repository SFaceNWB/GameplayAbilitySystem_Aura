// SFaceNWB Game


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//标题
			"<Title>FIRE BOLT</>\n\n"

			//等级
			"<Small>Level: </><Level>%d</>\n"
			//法力消耗
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//冷却时间
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			//伤害
			"<Default>Launched a bolt of fire, exploding on impact and dealing: </><Damage>%d</>"
			"<Default> fire damage with a chance to burn</>"),

			//值
			Level,
			ManaCost,
			Cooldown,
			ScaleDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			//标题
			"<Title>FIRE BOLT</>\n\n"

			//等级
			"<Small>Level: </><Level>%d</>\n"
			//法力消耗
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//冷却时间
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//伤害
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
		//标题
		"<Title>NEXT LEVEL</>\n\n"

		//等级
		"<Small>Level: </><Level>%d</>\n"
		//法力消耗
		"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
		//冷却时间
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//伤害
		"<Default>Launched %d bolts of fire, exploding on impact and dealing: </><Damage>%d</>"
		"<Default> fire damage with a chance to burn</>"),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaleDamage);
}