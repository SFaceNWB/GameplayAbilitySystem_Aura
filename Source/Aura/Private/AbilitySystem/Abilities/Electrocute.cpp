// SFaceNWB Game


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//标题
			"<Title>ELECTROCUTE</>\n\n"

			//等级
			"<Small>Level: </><Level>%d</>\n"
			//法力消耗
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//冷却时间
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//伤害
			"<Default>Emits a beam of lightning, connecting with the target, repeatedly causing: </><Damage>%d</>"
			"<Default>Lightning damage with a chance to stun</>"),

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
			"<Title>ELECTROCUTE</>\n\n"

			//等级
			"<Small>Level: </><Level>%d</>\n"
			//法力消耗
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//冷却时间
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//伤害
			"<Default>Emits a beam of lightning, propagating to %d additional targets nearby,Causing: </><Damage>%d</>"
			"<Default>Lightning damage with a chance to stun</>"),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaleDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
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
		"<Default>Emits a beam of lightning, connecting with the target, repeatedly causing: </><Damage>%d</>"
		"<Default>Lightning damage with a chance to stun</>"),

		//值
		Level,
		ManaCost,
		Cooldown,
		ScaleDamage);
}
