// SFaceNWB Game


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		//标题
		"<Title>FIRE BLAST</>\n\n"

		//等级
		"<Small>Level: </><Level>%d</>\n"
		//法力消耗
		"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
		//冷却时间
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//火球数
		"<Default>Launches %d</>"
		"<Default>Fire balls in all directions. each coming back and</>"
		"<Default>exploding upon return ,causing</>"

		//伤害
		"<Default>Launched </><Damage>%d</>"
		"<Default> radial fire damage with a chance to burn</>"),

		//值
		Level,
		ManaCost,
		Cooldown,
		NumFireBalls,
		ScaleDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
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

		//火球数
		"<Default>Launches %d</>"
		"<Default>Fire balls in all directions. each coming back and</>"
		"<Default>exploding upon return ,causing</>"

		//伤害
		"<Default>Launched </><Damage>%d</>"
		"<Default> radial fire damage with a chance to burn</>"),

		//值
		Level,
		ManaCost,
		Cooldown,
		NumFireBalls,
		ScaleDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	return TArray<AAuraFireBall*>();
}
