声明:
=
以下为个人笔记，仅供参考。

Game Mode:
-
    GetCharacterMovement()->bOrientRotationToMovement = true;//将角色面朝方向向加速方向旋转
    GetCharacterMovement()->bConstrainToPlane = true;//启用平面约束
    GetCharacterMovement()->bSnapToPlaneAtStart = true;//启用将角色吸附到平面上
----------------------------------------------------------------------------------------------------
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;//将鼠标控制镜头全部禁止

Init Ability Actor Info:
-	
    InitAbilityActorInfo(AvatarActor, OwnerActor);
AvatarActor: 在敌人为本身，在玩家为PlayState，即玩家控制的实际角色实体，负责实际执行能力。<br>
OwnerActor: 在敌人为本身，在玩家为本身，用于表示游戏中具有能力的所有者。<br>
在调用InitAbilityActorInfo时必须保证Controller与Pawn的关联，否则无法访问玩家状态信息。

    PossessedBy(AController* NewController);
必须确保能力系统组件与角色和所有者一起初始化。在`服务器`上一起初始化。

    OnRep_PlayerState();
调用同时需确保玩家状态有效后，在`客户端`上初始化。使用PlayerState：当Character被销毁时不会丢失技能和属性，复活可直接复制PlayerState初始化<br>
(如果直接使用玩家则使用AcknowledgePossession()在客户端上初始化)。<br>

Health and Mana
-
GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth)
宏，这个函数会在属性值通过网络从服务器复制到客户端时被调用。使用这个宏可以确保属性值的旧值被保存，以便在需要时可以进行回滚操作。

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always); //宏
注册需要复制的属性，让UE知道哪些属性需要同步。宏用来添加属性到列表中`REPNOTIFY_Always`表示一直复制，`COND_None`表示无条件复制。

Mapping Tags to Attributes
-
委托与指针的关系如下

    TMap<FGameplayTag,FAttributeSignature> TagsToAttributes;
    const FAuraGameplayTag& GameplayTags = FAuraGameplayTags::Get();
委托的方式：

    DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);
    FAttributeSignature StrengthDelegate;
    StrengthDelegate.BindStatic(UAuraAttributeSet::GetStrengthAttribute);
    TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, StrengthDelegate)
指针的方式：

    TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr == FAttributeSignature；//委托的含义替代
    TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr == FGameplayAttribute(*)();//本质为函数指针
    TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
    // typedef是特殊对于FGameplayAttribute()的signature， TStaticFunPtr是对任何选择的signature通用的。
    //typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
    template<class T>
    using TStaticFuncPtr = typename TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr;//模块化为通用模板

Settings on Gameplay Abilities
-
Tags  
Ability Tags: 技能有这些标签  
Cancel Abilities with Tag: 有这些标签的技能在执行时会被取消。  
Block Abilities with Tag: 有这些标签的技能在激活时会被阻止。  
Activation Owned Tags: 在技能激活时应用于激活所有者的标签，如果ReplicateActivationOwnedTags是在AbilitySystemGlobals里启用，则会复制这些标签。  
Activation Required Tags: 只有在需要激活的Actor或组件有这些标签的情况下才能被激活。  
Activation Blocked Tags:如果需要激活的Actor或组件有这些标签的任何一个，该技能会被阻止。  
Source Required Tags: 只有当源Actor或组件具有这些标签才能被激活。  
Source Blocked Tags:如果源Actor或组件具有这些标签中的任何一个，该技能会被阻止。  
Target Required Tags: 只有当目标Actor或组件具有这些标签才能被激活。  
Target Blocked Tags:如果目标Actor或组件具有这些标签中的任何一个，该技能会被阻止。  
Instancing Policy  
Instance Per Actor:为该技能创建一个实例，每次激活都会被重复使用。可以存储持久数据，但是变量每次必须手动重置。  
Instanced Per Execution: 每次激活都会创建一个实例。不会在激活的时候存储持久数据，性能不如Instance Per Actor。  
Non-Instanced: 只使用类默认对象，不创建实例。不能存储状态，不能在Ability Tasks上绑定委托，三项中性能最好的。  
Net Execution Policy  
Local Only:只能在本地客户端运行，服务器不允许技能。  
Local Predicted: 在本地客户端激活，然后在服务器上激活。利用预测，服务器可以回滚无效的更改。  
Server Only: 只能在服务器上运行。  
Server Initiated: 首先在服务器上运行，然后再自己的本地客户端上运行。  
