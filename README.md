声明:
=
以下为个人笔记，仅供参考。

Game Mode:
-
    GetCharacterMovement()->bOrientRotationToMovement = true;将角色面朝方向向加速方向旋转
    GetCharacterMovement()->bConstrainToPlane = true;启用平面约束
    GetCharacterMovement()->bSnapToPlaneAtStart = true;启用将角色吸附到平面上
----------------------------------------------------------------------------------------------------
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;将鼠标控制镜头全部禁止

Init Ability Actor Info:
-
		InitAbilityActorInfo(AvatarActor, OwnerActor);
AvatarActor: 在敌人为本身，在玩家为PlayState，即玩家控制的实际角色实体，负责实际执行能力。<br>
OwnerActor: 在敌人为本身，在玩家为本身，用于表示游戏中具有能力的所有者。<br>
在调用InitAbilityActorInfo时必须保证Controller与Pawn的关联，否则无法访问玩家状态信息。<br>
		PossessedBy(AController* NewController)
必须确保能力系统组件与角色和所有者一起初始化。在`服务器`上一起初始化。<br>
		OnRep_PlayerState（）
调用同时需确保玩家状态有效后，在`客户端`上初始化。使用PlayerState：当Character被销毁时不会丢失技能和属性，复活可直接复制PlayerState初始化<br>
(如果直接使用玩家则使用AcknowledgePossession()在客户端上初始化)。<br>
