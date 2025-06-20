// SFaceNWB Game


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		//����
		"<Title>FIRE BLAST</>\n\n"

		//�ȼ�
		"<Small>Level: </><Level>%d</>\n"
		//��������
		"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
		//��ȴʱ��
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//������
		"<Default>Launches %d</>"
		"<Default>Fire balls in all directions. each coming back and</>"
		"<Default>exploding upon return ,causing</>"

		//�˺�
		"<Default>Launched </><Damage>%d</>"
		"<Default> radial fire damage with a chance to burn</>"),

		//ֵ
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
		//����
		"<Title>NEXT LEVEL</>\n\n"

		//�ȼ�
		"<Small>Level: </><Level>%d</>\n"
		//��������
		"<SMall>ManaCost: </><ManaCost>%.1f</>\n"
		//��ȴʱ��
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//������
		"<Default>Launches %d</>"
		"<Default>Fire balls in all directions. each coming back and</>"
		"<Default>exploding upon return ,causing</>"

		//�˺�
		"<Default>Launched </><Damage>%d</>"
		"<Default> radial fire damage with a chance to burn</>"),

		//ֵ
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
