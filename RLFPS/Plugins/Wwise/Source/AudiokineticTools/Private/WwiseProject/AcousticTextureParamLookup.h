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

#pragma once
#include "WorkUnitXmlVisitor.h"
#include "WwiseWorkUnitParser.h"

class WwiseWorkUnitParser;

class AcousticTextureVisitor : public WorkUnitXmlVisitor
{
public:
	virtual void EnterAcousticTexture(const FGuid& Id, const FXmlNode* CurrentNode, const FString& Name, const FString& RelativePath) override;
};

class AkAcousticTextureParamLookup
{
public:
	AkAcousticTextureParamLookup();
	void UpdateParamsMap();

private:
	AcousticTextureVisitor Visitor;
	WwiseWorkUnitParser Parser;
};
