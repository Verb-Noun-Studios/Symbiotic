// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionTelemetrySubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

	/** Override to control if the Subsystem should be created at all.
		* For example you could only have your system created on servers.
		* It's important to note that if using this is becomes very important to null check whenever getting the Subsystem.
		*
		* Note: This function is called on the CDO prior to instances being created!
		*/
bool USessionTelemetrySubsystem::ShouldCreateSubsystem(UObject* Outer) const { return true; }

void USessionTelemetrySubsystem::SessionStart() {
	sessionID = FGuid::NewGuid();
	sessionStart = FDateTime::Now().ToUnixTimestamp();
}

void USessionTelemetrySubsystem::SessionEnd() {

}

/** Implement this for initialization of instances of the system */
void USessionTelemetrySubsystem::Initialize(FSubsystemCollectionBase& Collection) {

	// send any un sent feedback
	SendSavedFeedbacks();
}


/** Implement this for deinitialization of instances of the system */
void USessionTelemetrySubsystem::Deinitialize() {
}





void USessionTelemetrySubsystem::SaveFeedback(FString category, uint8 mood, FString text) {

	// don't save or send feedbacks if we are playing in editor or preview mode (i think thats when u pop out in editor)
	if (GetWorld()->IsPlayInEditor() || GetWorld()->IsPlayInPreview()) return;

	TSharedRef<FJsonObject> OutJson = MakeShareable(new FJsonObject);

	FGuid submissionID = FGuid::NewGuid();
	FDateTime timestamp = FDateTime::Now();

	OutJson->SetStringField("id", submissionID.ToString());
	OutJson->SetStringField("timestamp", timestamp.ToIso8601());
	OutJson->SetStringField("session_id", sessionID.ToString());
	OutJson->SetStringField("category", category);
	OutJson->SetStringField("build_id", "0"); //TODO (thornton): make real build id
	OutJson->SetNumberField("mood", (double)mood);
	OutJson->SetStringField("text", text);



	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	// serialize game state
	OutJson->SetStringField("level_name", GetWorld()->GetMapName());
	OutJson->SetStringField("level_seed", "0"); //TODO (thornton): get level seed
	OutJson->SetStringField("level_pos", playerPos.ToString());
	OutJson->SetNumberField("playtime", (double)(timestamp.ToUnixTimestamp() - sessionStart));


	// save to file
	FString dataPath = FPaths::ConvertRelativePathToFull(FPaths::AutomationDir());
	FString folderPath = dataPath + "/submissions/";
	FString backupPath = dataPath + "/submissions_backup/";
	FString filepath = folderPath + submissionID.ToString() + ".json";


	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	platformFile.CreateDirectory(*folderPath);
	platformFile.CreateDirectory(*backupPath);



	// THIS IS SO STUPID BUT I CAN'T DEAL WITH WADING THROUGH 40 LAYERS OF OOP 
	// TO FIGURE OUT HOW TO WRITE DIRECTLY TO A FILE SO HERE WE ARE

	FString jsonStr;
	TSharedRef<TJsonWriter<TCHAR> > JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

	FJsonSerializer::Serialize(OutJson, JsonWriter);


	FFileHelper::SaveStringToFile(jsonStr, *filepath);

	
	UFeedbackSubmissionHTTP::Send(filepath, this);

}

void  USessionTelemetrySubsystem::SendSavedFeedbacks() {

	TArray< FString > FoundFiles;
	FString folderPath = FPaths::ConvertRelativePathToFull(FPaths::AutomationDir()) + "/submissions/";

	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	platformFile.FindFiles(FoundFiles, *folderPath, NULL);

	for (const FString& path : FoundFiles) {

		UFeedbackSubmissionHTTP::Send(path, this);
		
	}
}


void USessionTelemetrySubsystem::SaveEvent(FString name, TArray<FString> params) {

}

void UFeedbackSubmissionHTTP::Send(FString path, UObject* outer) {

	const FString url = "local.trobol.net:8080/feedback";
	FString content;
	FFileHelper::LoadFileToString(content, *path);

	UFeedbackSubmissionHTTP* obj = NewObject<UFeedbackSubmissionHTTP>(outer);
	obj->path = path;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(*url);
	HttpRequest->SetContentAsString(content);

	HttpRequest->OnProcessRequestComplete().BindUObject(obj, &UFeedbackSubmissionHTTP::OnComplete);

	HttpRequest->ProcessRequest();

}


// This wont execute if we try to send when the game it shutting down, think the HTTP request is getting cleaned up before it finishes
void UFeedbackSubmissionHTTP::OnComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		FString backupPath = FPaths::ConvertRelativePathToFull(FPaths::AutomationDir()) + "/submissions_backup/" + FPaths::GetCleanFilename(path);
		
	
		platformFile.MoveFile(*backupPath, *path);
	}
}