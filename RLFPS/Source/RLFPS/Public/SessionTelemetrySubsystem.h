// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HttpModule.h"
#include "SessionTelemetrySubsystem.generated.h"


/*
 * Session telemetry 
 * list of events
 * an event has a name, a timestamp (in "in game" seconds) and a list of paramerters
 * 
 * 
 * 
 */

/**
 * INFO AND SOME CODE SNIPPETS FROM: https://benui.ca/unreal/subsystem-singleton/
 */
UCLASS()
class RLFPS_API USessionTelemetrySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


	/** Override to control if the Subsystem should be created at all.
		* For example you could only have your system created on servers.
		* It's important to note that if using this is becomes very important to null check whenever getting the Subsystem.
		*
		* Note: This function is called on the CDO prior to instances being created!
		*/
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);


	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();



public:

	// Save feedback to disk for sending later
	UFUNCTION(BlueprintCallable)
	void SaveFeedback(FString category, uint8 mood, FString text);

	
	UFUNCTION(BlueprintCallable)
	void SaveEvent(FString name, TArray<FString> params);


	UFUNCTION(BlueprintCallable)
	void SessionStart();

	UFUNCTION(BlueprintCallable)
	void SessionEnd();
	
private:

	FGuid sessionID;
	int64 sessionStart;



	// send feedbacks that we have saved on disk
	void SendSavedFeedbacks();

};


// Little class to keep track of an http request
UCLASS()
class RLFPS_API UFeedbackSubmissionHTTP : public UObject {
	GENERATED_BODY()
public:
	static void Send(FString path, UObject* outer);

private:
	FString path;

	void OnComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};