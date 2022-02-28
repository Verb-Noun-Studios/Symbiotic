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


/*=============================================================================
AkAcousticPortalVisualizer.cpp:
=============================================================================*/

#include "AkAcousticPortalVisualizer.h"
#include "AkSpatialAudioDrawUtils.h"
#include "AkDrawPortalComponent.h"
#include "AkRoomComponent.h"
#include "SceneManagement.h"
#include "DynamicMeshBuilder.h"
#include "Classes/EditorStyleSettings.h"
#include "EditorModes.h"
#include "Materials/Material.h"

void UAkPortalComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UAkPortalComponent* PortalComponent = Cast<UAkPortalComponent>(Component);
	if (IsValid(PortalComponent) && IsValid(PortalComponent->GetPrimitiveParent()))
	{
		const UPrimitiveComponent* PrimitiveParent = Cast<UPrimitiveComponent>(PortalComponent->GetPrimitiveParent());
		// Calculate the unscaled, unrotated box extent of the primitive parent component, at origin.
		FVector BoxExtent = PrimitiveParent->CalcBounds(FTransform()).BoxExtent;
		FDynamicMeshBuilder MeshBuilderFront(ERHIFeatureLevel::Type::ES3_1);
		FDynamicMeshBuilder MeshBuilderBack(ERHIFeatureLevel::Type::ES3_1);

		const FTransform T = PrimitiveParent->GetComponentTransform();
		AkDrawBounds DrawBounds(T, BoxExtent);
		MeshBuilderFront.AddVertices({ DrawBounds.FRU(), DrawBounds.FRD(), DrawBounds.RD(), DrawBounds.RU(),
										DrawBounds.FLU(), DrawBounds.FLD(), DrawBounds.LD(), DrawBounds.LU() });
		MeshBuilderBack.AddVertices({ DrawBounds.BLU(), DrawBounds.BLD(), DrawBounds.LD(), DrawBounds.LU(),
										DrawBounds.BRU(), DrawBounds.BRD(), DrawBounds.RD(), DrawBounds.RU() });

		// add vertices using front - back, right - left, up - down winding.
		MeshBuilderFront.AddTriangles
		({
			/*front face*/0, 3, 2,  0, 2, 1,
			/*back face*/4, 7, 6,  4, 6, 5,
			/*top face*/0, 3, 7,  0, 7, 4,
			/*bottom face*/1, 2, 6,  1, 6, 5
			});

		MeshBuilderBack.AddTriangles
		({
			/*front face*/0, 3, 2,  0, 2, 1,
			/*back face*/4, 7, 6,  4, 6, 5,
			/*top face*/0, 3, 7,  0, 7, 4,
			/*bottom face*/1, 2, 6,  1, 6, 5
			});

		// Allocate the material proxy and register it so it can be deleted properly once the rendering is done with it.
#if UE_4_22_OR_LATER
		auto* renderProxy = GEngine->GeomMaterial->GetRenderProxy();
#else
		auto* renderProxy = GEngine->GeomMaterial->GetRenderProxy(false);
#endif
		FLinearColor FrontDrawColor;
		FLinearColor BackDrawColor;
		AkSpatialAudioColors::GetPortalColors(PortalComponent, FrontDrawColor, BackDrawColor);

		FDynamicColoredMaterialRenderProxy* ColorInstanceFront = new FDynamicColoredMaterialRenderProxy(renderProxy, FrontDrawColor);
		PDI->RegisterDynamicResource(ColorInstanceFront);

		MeshBuilderFront.Draw(PDI, FMatrix::Identity, ColorInstanceFront, SDPG_World, true, false);

		FDynamicColoredMaterialRenderProxy* ColorInstanceBack = new FDynamicColoredMaterialRenderProxy(renderProxy, BackDrawColor);
		PDI->RegisterDynamicResource(ColorInstanceBack);

		MeshBuilderBack.Draw(PDI, FMatrix::Identity, ColorInstanceBack, SDPG_World, true, false);

		// Draw an outline around the centre of the portal, to distinguish front and back
		FVector RightTop = FVector(0.0f, BoxExtent.Y, BoxExtent.Z);
		FVector LeftBottom = -RightTop;
		FVector LeftTop = FVector(0.0f, -BoxExtent.Y, BoxExtent.Z);
		FVector RightBottom = -LeftTop;
		const float Thickness = AkDrawConstants::PortalRoomConnectionThickness;
		const FLinearColor OutlineColor = AkSpatialAudioColors::GetPortalOutlineColor(PortalComponent);
		PDI->DrawLine(T.TransformPosition(RightTop), T.TransformPosition(LeftTop), OutlineColor, SDPG_Foreground, Thickness);
		PDI->DrawLine(T.TransformPosition(LeftTop), T.TransformPosition(LeftBottom), OutlineColor, SDPG_Foreground, Thickness);
		PDI->DrawLine(T.TransformPosition(LeftBottom), T.TransformPosition(RightBottom), OutlineColor, SDPG_Foreground, Thickness);
		PDI->DrawLine(T.TransformPosition(RightBottom), T.TransformPosition(RightTop), OutlineColor, SDPG_Foreground, Thickness);
		// Draw a line from back room to front room.
		FVector Front = FVector(BoxExtent.X, 0.0f, 0.0f);
		FVector Back = FVector(-BoxExtent.X, 0.0f, 0.0f);
		PDI->DrawLine(T.TransformPosition(Back), T.TransformPosition(Front), OutlineColor, SDPG_Foreground, Thickness);

		// draw a diagonal on left and right faces if the portal is closed
		if (PortalComponent->InitialState == AkAcousticPortalState::Closed)
		{
			PDI->DrawLine(DrawBounds.FRU(), DrawBounds.BRD(), FrontDrawColor, SDPG_Foreground, Thickness);
			PDI->DrawLine(DrawBounds.FLD(), DrawBounds.BLU(), BackDrawColor, SDPG_Foreground, Thickness);
		}
	}

	if (GEditor->GetSelectedActorCount() == 1 && IsValid(PortalComponent))
	{
		AAkAcousticPortal* pPortal = Cast<AAkAcousticPortal>(PortalComponent->GetOwner());
		if (pPortal && pPortal->GetFitToGeometry() && pPortal->GetIsDragging())
		{
			FVector Point0, End0, Point1, End1;
			if (pPortal->GetBestHits(Point0, End0, Point1, End1))
			{
				FVector Dir0 = End0 - Point0;
				float L0 = Dir0.SizeSquared();

				FVector Dir1 = End1 - Point1;
				float L1 = Dir1.SizeSquared();

				FVector V01 = Point1 - Point0;
				FVector TL0 = Point1 - FVector::DotProduct(V01, Dir0) * Dir0 / L0;
				FVector TL1 = Point0 - FVector::DotProduct(-V01, Dir1) * Dir1 / L1;
				FVector TL = (TL0 + TL1) / 2.f;
				FVector TR = TL + Dir0;
				FVector BL = TL + Dir1;
				FVector BR = BL + Dir0;

				const FLinearColor PreviewColor = GetDefault<UEditorStyleSettings>()->SelectionColor * 1.3f;

				PDI->DrawLine(TL, TR, PreviewColor, 100, 5.f, 50.f);
				PDI->DrawLine(TR, BR, PreviewColor, 100, 5.f, 50.f);
				PDI->DrawLine(BR, BL, PreviewColor, 100, 5.f, 50.f);
				PDI->DrawLine(BL, TL, PreviewColor, 100, 5.f, 50.f);
			}
		}
	}
}
