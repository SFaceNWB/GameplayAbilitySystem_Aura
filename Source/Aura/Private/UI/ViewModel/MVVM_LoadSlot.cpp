// SFaceNWB Game


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	// TODO: ���ݼ��ص����ݼ����״̬
	SetWidgetSwitcherIndex.Broadcast(2);
}

void UMVVM_LoadSlot::SetLoadSlotName(FString InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}
