// SFaceNWB Game


#include "UI/ViewModel/MVVM_LoadScreen.h"

void UMVVM_LoadScreen::SetNumLoadSlots(int32 InNumSlots)
{
	UE_MVVM_SET_PROPERTY_VALUE(NumLoadSlots, InNumSlots);
}
