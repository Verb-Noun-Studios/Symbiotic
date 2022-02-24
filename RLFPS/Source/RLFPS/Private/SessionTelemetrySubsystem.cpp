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
bool USessionTelemetrySubsystem::ShouldCreateSubsystem(UObject* Outer) const { /* TODO(thornton): disable in editor */return true; }

/** Implement this for initialization of instances of the system */
void USessionTelemetrySubsystem::Initialize(FSubsystemCollectionBase& Collection) {

	NewSession();
	

}


/** Implement this for deinitialization of instances of the system */
void USessionTelemetrySubsystem::Deinitialize() {

	// send any un sent feedback
	SendSavedFeedbacks();


}





void USessionTelemetrySubsystem::SaveFeedback(FString category, uint8 mood, FString text) {

	TSharedRef<FJsonObject> OutJson = MakeShareable(new FJsonObject);

	FGuid submissionID = FGuid::NewGuid();
	FDateTime timestamp = FDateTime::UtcNow();

	OutJson->SetStringField("id", submissionID.ToString());
	OutJson->SetStringField("timestamp", timestamp.ToIso8601());
	OutJson->SetStringField("session_id", sessionID.ToString());
	OutJson->SetStringField("category", category);
	OutJson->SetStringField("build_id", "0"); //TODO (thornton): make real build id
	OutJson->SetNumberField("mood", (double)mood);
	OutJson->SetStringField("text", text);


	// serialize game state
	TSharedRef<FJsonObject> StateJson = MakeShareable(new FJsonObject);

	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	StateJson->SetStringField("level_name", GetWorld()->GetMapName());
	StateJson->SetStringField("level_seed", "0"); //TODO (thornton): get level seed
	StateJson->SetStringField("level_pos", playerPos.ToString());
	StateJson->SetNumberField("playtime", (double)(timestamp.ToUnixTimestamp() - sessionStart));


	OutJson->SetObjectField("state", StateJson);
	

	// save to file
	FString folderPath = FPaths::ConvertRelativePathToFull(FPaths::AutomationDir()) + "/submissions/";
	FString filepath = folderPath + submissionID.ToString() + ".json";


	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	platformFile.CreateDirectory(*folderPath);



	// THIS IS SO STUPID BUT I CAN'T DEAL WITH WADING THROUGH 40 LAYERS OF OOP BULLSHIT
	// TO FIGURE OUT HOW TO WRITE DIRECTLY TO A FILE SO HERE WE ARE

	FString jsonStr;
	TSharedRef<TJsonWriter<TCHAR> > JsonWriter = TJsonWriterFactory<TCHAR>::Create(&jsonStr);

	FJsonSerializer::Serialize(OutJson, JsonWriter);

	FFileHelper::SaveStringToFile(jsonStr, *filepath);

}

void USessionTelemetrySubsystem::NewSession() {
	sessionID = FGuid::NewGuid();
	sessionStart = FDateTime::UtcNow().ToUnixTimestamp();
}

void  USessionTelemetrySubsystem::SendSavedFeedbacks() {

	

	TArray< FString > FoundFiles;
	FString folderPath = FPaths::ConvertRelativePathToFull(FPaths::AutomationDir()) + "/submissions/";

	IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
	platformFile.FindFiles(FoundFiles, *folderPath, NULL);

	for (const FString& path : FoundFiles) {
		UFeedbackSubmissionHTTP::Send(path);
		
	}
}




void UFeedbackSubmissionHTTP::Send(FString path) {

	const FString url = "localhost:8080/feedback";
	FString content;
	FFileHelper::LoadFileToString(content, *path);

	UFeedbackSubmissionHTTP* obj = NewObject<UFeedbackSubmissionHTTP>();
	obj->path = path;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(*url);
	HttpRequest->SetContentAsString(content);

	HttpRequest->OnProcessRequestComplete().BindUObject(obj, &UFeedbackSubmissionHTTP::OnComplete);

	HttpRequest->ProcessRequest();

}

void UFeedbackSubmissionHTTP::OnComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		// TODO (thornton): only delete if the request goes through
		platformFile.DeleteFile(*path);
	}
}