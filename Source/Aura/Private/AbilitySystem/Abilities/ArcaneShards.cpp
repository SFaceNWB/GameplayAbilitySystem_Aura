// SFaceNWB Game


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//标题
			"<Title>ARCANE SHARDS</>\n\n"

			//等级
			"<Small>Level: </><Level>%d</>\n"
			//法力消耗
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//冷却时间
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//伤害
			"<Default>Summon Shards of arcane energy, causing radial arcane damage </><Damage>%d</>"
			"<Default>at the shard origin</>"),

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
			"<Title>ARCANE SHARDS</>\n\n"

			//等级
			"<Small>Level: </><Level>%d</>\n"
			//法力消耗
			"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
			//冷却时间
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//伤害
			"<Default>Summon %d shards of arcane energy, causing radial arcane damage</>"
			"<Default>%d</><Default>at the shard origin.</>"),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShards),
			ScaleDamage);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
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
		"<Default>Summon Shards of arcane energy, causing radial arcane damage </><Damage>%d</>"
		"<Default>at the shard origin</>"),

		//值
		Level,
		ManaCost,
		Cooldown,
		ScaleDamage);
}
