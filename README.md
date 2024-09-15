# DevUI
DevUI is a plugin, based around a fork [UnrealImGui](https://github.com/benui-dev/UnrealImGui), that I created to be able to make ImGui windows without much hassle quickly.
This plugin can use the [original version of UnrealImGui](https://github.com/segross/UnrealImGui), this allows the DevUI plugin to work on Unreal 4.27.

If there are any bugs or things that don't make sense, please open an issue! This plugin was mainly created for my use cases as such the code might not be the best quality or best practices. But I'm open sourcing it in the hopes it might be useful to someone else.

## How to use

### Displaying menu bar
A menu bar is created alongside this plugin which is rendered when `ImGui.ToggleInput` is active. You can set a hotkey to enable this by adding this to your DefaultInput.ini. Keep in mind this keybind will not work in shipping builds.
```ini
[/Script/Engine.PlayerInput]
DebugExecBindings=(Key=F6,Command="ImGui.ToggleInput")
```

### Making a window
Generally it's as simple as creating a basic class for your window. It is recommended to either place this in the game module or a specific ImGui module that is loaded at runtime. (I'm not sure if a runtime module is strictly required, I haven't really tested these in an editor module)

```cpp
// MyWindow.h
#pragma once

#include "CoreMinimal.h"
#include "DevUIWindow.h"
#include "MyWindow.generated.h"

UCLASS()
class UMyWindow : public UDevUIWindow
{
	GENERATED_BODY()
public:

	/**
	* Draws the window if enabled
	* @return True to indicate this window should remain open
	*/
	bool Draw(UWorld* World) override;

	/** Returns FString that will be used for the title */
	FString GetWindowName() override;

	/** Returns the window help text */
	FString GetWindowHelp() override;

	/** Returns ImGui windows flags */
	ImGuiWindowFlags GetWindowFlags() const override;
};

// MyWindow.cpp
#include "MyWindow.h"

bool UMyWindow::Draw(UWorld* World)
{
	DrawViewModeButtons(World);
	return true;
}

FString UMyWindow::GetWindowName()
{
	return TEXT("My Window");
}

FString UMyWindow::GetWindowHelp()
{
	return TEXT("My window help text!");
}

ImGuiWindowFlags UMyWindow::GetWindowFlags() const
{
	return ImGuiWindowFlags_None;
}

void UMyWindow::DrawViewModeButtons(UWorld* World)
{
	ImGui::BeginGroup();
	ImGui::Text(TCHAR_TO_ANSI(TEXT("View modes")));

	if (ImGui::Button(TCHAR_TO_ANSI(TEXT("Lit"))))
	{
		World->GetGameViewport()->ViewModeIndex = EViewModeIndex::VMI_Lit;
	}
	ImGui::SameLine();

	if (ImGui::Button(TCHAR_TO_ANSI(TEXT("Unlit"))))
	{
		World->GetGameViewport()->ViewModeIndex = EViewModeIndex::VMI_Unlit;
	}
	ImGui::SameLine();

	if (ImGui::Button(TCHAR_TO_ANSI(TEXT("Wireframe"))))
	{
		World->GetGameViewport()->ViewModeIndex = EViewModeIndex::VMI_Wireframe;
	}

	ImGui::EndGroup();
}
```

## Notes
- I have a custom version of UnrealImGui that will allow me to bind `ImGui.ToggleInput` to function keys, you can find the [diff here](Diffs/unrealimgui-allow-function-keys.diff). Keep in mind this process isn't ideal and will prevent ImGui from consuming function keys, and is also hardcoded between F1->F12.
    - This patch was made a while ago, so I can't remember the circumstances around it. But it would probably be best to avoid binding to function keys.
