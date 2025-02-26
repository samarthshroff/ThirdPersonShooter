#include "ThirdPersonShooterEditor.h"

#include "GameplayTagsWrapper.h"

void FThirdPersonShooterEditorModule::StartupModule()
{
	// if (!UGameplayTagsWrapper::StaticClass()->HasAnyClassFlags(CLASS_Constructed))
	// {
	// 	UGameplayTagsWrapper::StaticClass()->GetDefaultObject();
	// }
}

IMPLEMENT_MODULE(FThirdPersonShooterEditorModule, ThirdPersonShooterEditor);


