声明:
=
以下为个人笔记，仅供参考。
Game Mode:
-
    GetCharacterMovement()->bOrientRotationToMovement = true;将角色面朝方向向加速方向旋转
    GetCharacterMovement()->bConstrainToPlane = true;启用平面约束
    GetCharacterMovement()->bSnapToPlaneAtStart = true;启用将角色吸附到平面上
--------------------------------------------------------------------------------------
    bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;将鼠标控制镜头全部禁止
