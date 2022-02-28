/*******************************************************************************
The content of the files in this repository include portions of the
AUDIOKINETIC Wwise Technology released in source code form as part of the SDK
package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use these files in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Copyright (c) 2021 Audiokinetic Inc.
*******************************************************************************/

#include "AkRoomComponentDetailsCustomization.h"
#include "AkRoomComponent.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"

#define LOCTEXT_NAMESPACE "AudiokineticTools"


//////////////////////////////////////////////////////////////////////////
// FAkRoomComponentDetailsCustomization

FAkRoomComponentDetailsCustomization::FAkRoomComponentDetailsCustomization()
{
}

TSharedRef<IDetailCustomization> FAkRoomComponentDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FAkRoomComponentDetailsCustomization());
}

void FAkRoomComponentDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	DetailLayout.EditCategory("Toggle", FText::GetEmpty(), ECategoryPriority::Important);
	DetailLayout.EditCategory("Room", FText::GetEmpty(), ECategoryPriority::TypeSpecific);
	DetailLayout.EditCategory("AkEvent", FText::GetEmpty(), ECategoryPriority::TypeSpecific);
	MyDetailLayout = &DetailLayout;
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailLayout.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	for (TWeakObjectPtr<UObject>& Object : ObjectsBeingCustomized)
	{
		UAkRoomComponent* RoomBeingCustomized = Cast<UAkRoomComponent>(Object.Get());
		if (RoomBeingCustomized)
		{
			UObject* OuterObj = RoomBeingCustomized->GetOuter();
			UActorComponent* OuterComponent = Cast<UActorComponent>(OuterObj);
			AActor* OuterActor = Cast<AActor>(OuterObj);
			// Do not hide the transform if the component has been created from within a component or actor, as this will hide the transform for that component / actor as well
			// (i.e. - only hide the transform if the component has been added to the hierarchy of a blueprint class or actor instance from the editor)
			if (OuterComponent == nullptr && OuterActor == nullptr)
			{
				IDetailCategoryBuilder& TransformCategory = DetailLayout.EditCategory("TransformCommon", LOCTEXT("TransformCommonCategory", "Transform"), ECategoryPriority::Transform);
				TransformCategory.SetCategoryVisibility(false);
				break;
			}
		}
	}

	if (ObjectsBeingCustomized.Num() != 1)
	{
		return;
	}

	UAkRoomComponent* RoomBeingCustomized = Cast<UAkRoomComponent>(ObjectsBeingCustomized[0].Get());
	if (RoomBeingCustomized)
	{
		IDetailCategoryBuilder& ToggleDetailCategory = DetailLayout.EditCategory("Toggle");
		auto EnableHandle = DetailLayout.GetProperty("bEnable");
		EnableHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FAkRoomComponentDetailsCustomization::OnEnableValueChanged));

		if (!RoomBeingCustomized->bEnable)
		{
			DetailLayout.HideCategory("Room");
		}
	}
}

void FAkRoomComponentDetailsCustomization::OnEnableValueChanged()
{
	MyDetailLayout->ForceRefreshDetails();
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE