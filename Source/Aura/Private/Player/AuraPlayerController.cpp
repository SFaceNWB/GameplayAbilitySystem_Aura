// SFaceNWB Game


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
	* �ӹ�꿪ʼ�Ĺ켣���м��������
	* 1.LastActor is null && ThisActor is null
	*	- ʲô������
	* 2.LastActor is null && ThisActor is valid
	*	- ͻ����ʾ(Highlight) ThisActor
	* 3.LastActor is valid && ThisActor is null
	*	- ȡ��ͻ����ʾ(UnHighlight) LastActor
	* 4.LastActor �� ThisActor ���� valid, ����LastActor != ThisActor
	*	- ȡ��ͻ����ʾ LastActor, ͻ����ʾ ThisActor
	* 5. LastActor �� ThisActor ���� valid, ����LastActor == ThisActor
	*	- ʲô������
	*/

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case 2.
			ThisActor->HighlightActor();
		}
		//Case 1.
	}
	else //LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			//Case 3.
			LastActor->UnHighlightActor();
		}
		else //ThisActor is valid
		{
			if (LastActor != ThisActor)
			{
				//Case 4.
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			//Case 5.
		}
	}
}
