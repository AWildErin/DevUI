#pragma once

#include "Subsystems/GameInstanceSubsystem.h"

#include "DevUISubsystem.generated.h"

class UDevUIWindow;
class FImGuiModule;

/**
 * @class UDevUISubSystem
 * @brief Main subsytem that is created per game instance that manages all of ImGui
 */
UCLASS()
class DEVUI_API UDevUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	// Begin USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface

private:
	FImGuiModule*	ImGuiModule;
	UWorld*			ObjectWorld;

	bool bDrawImGuiDemo;
	bool bDrawImGuiMetrics;
	bool bDrawImGuiStyleEditor;
	bool bDrawImGuiAbout;

	TArray<UDevUIWindow*> AllWindows;

	/**
	 * Delegates
	 */

	FDelegateHandle OnDrawHandle;
	void			OnDraw();

	/** Handles drawing the menu bar for ImGui */
	void DrawMenuBar();

	/** Handles drawing our windows */
	void DrawWindows();

	/** Handles shared logic for drawing a specific window */
	bool DrawWindow(UDevUIWindow* Window);
};
