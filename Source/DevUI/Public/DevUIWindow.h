#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <imgui.h>

#include "DevUIWindow.generated.h"

/**
 * @class UDevUIWindow
 * @brief Abstract class for all DevUI windows
 */
UCLASS(Abstract)
class DEVUI_API UDevUIWindow : public UObject
{
	GENERATED_BODY()

public:
	UDevUIWindow()	= default;
	~UDevUIWindow() = default;

	/**
	 * Draws the window if enabled
	 * @returns True to indicate this window should remain open
	 */
	virtual bool Draw(UWorld* World);

	/**  Called when draw state is changed */
	virtual void OnStateChanged();

	/** Returns FString that will be used for the title */
	virtual FString GetWindowName();

	/** Returns the window help text */
	virtual FString GetWindowHelp();

	/** Returns ImGui windows flags */
	virtual ImGuiWindowFlags GetWindowFlags() const;

	bool ShouldDraw();
	void ToggleDraw();
	void SetDraw(bool bDraw);

private:
	bool bShouldDraw;
};
