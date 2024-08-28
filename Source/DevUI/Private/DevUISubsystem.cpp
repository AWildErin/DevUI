#include "DevUISubsystem.h"

#include "DevUICommon.h"

void UDevUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// Class defaults
	bDrawImGuiDemo = false;
	AllWindows	   = {};

	// Don't bother doing the rest if we're a CDO
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	ImGuiModule = FModuleManager::GetModulePtr<FImGuiModule>("ImGui");
	check(ImGuiModule);

	ObjectWorld = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::Assert);
	check(ObjectWorld);

	// Turns off imgui input as it is still enabled from our last session
	ImGuiModule->GetProperties().SetInputEnabled(false);

	// Register our delegate
	OnDrawHandle = FImGuiDelegates::OnWorldDebug(ObjectWorld).AddUObject(this, &ThisClass::OnDraw);

	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (!It->IsChildOf(UDevUIWindow::StaticClass()) || It->HasAnyClassFlags(CLASS_Abstract))
		{
			continue;
		}

		UClass*		  Class	 = *It;
		UDevUIWindow* Window = CastChecked<UDevUIWindow>(Class->GetDefaultObject());

		AllWindows.Add(Window);
	}
}

void UDevUISubsystem::Deinitialize() {}

void UDevUISubsystem::OnDraw()
{
	// Only draw our menu bar if we have input
	if (ImGuiModule->GetProperties().IsInputEnabled())
	{
		DrawMenuBar();
	}

	DrawWindows();
}

void UDevUISubsystem::DrawMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			for (UDevUIWindow* Window : AllWindows)
			{
				bool bToggle = Window->ShouldDraw();
				if (ImGui::MenuItem(TCHAR_TO_ANSI(*Window->GetWindowName()), nullptr, &bToggle))
				{
					Window->SetDraw(bToggle);
				}

				FString HelpText = Window->GetWindowHelp();
				if (!HelpText.IsEmpty() && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip(TCHAR_TO_ANSI(*Window->GetWindowHelp()));
				}
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("ImGui"))
		{
			bool InputCheckboxVal = ImGuiModule->GetProperties().IsInputEnabled();
			ImGui::Checkbox("Input Enabled", &InputCheckboxVal);
			if (InputCheckboxVal != ImGuiModule->GetProperties().IsInputEnabled())
			{
				ImGuiModule->GetProperties().ToggleInput();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Debug"))
		{
			ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "ImGui");
			ImGui::MenuItem("Toggle ImGui demo", nullptr, &bDrawImGuiDemo);
			ImGui::MenuItem("Toggle ImGui metrics", nullptr, &bDrawImGuiMetrics);
			ImGui::MenuItem("Toggle ImGui style editor", nullptr, &bDrawImGuiStyleEditor);
			ImGui::MenuItem("Toggle ImGui about", nullptr, &bDrawImGuiAbout);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void UDevUISubsystem::DrawWindows()
{
	if (bDrawImGuiDemo)
	{
		// Draw imgui demo window if requested
		ImGui::ShowDemoWindow(&bDrawImGuiDemo);
	}

	if (bDrawImGuiMetrics)
	{
		ImGui::ShowMetricsWindow(&bDrawImGuiMetrics);
	}

	if (bDrawImGuiStyleEditor)
	{
		ImGui::ShowStyleEditor();
	}

	if (bDrawImGuiAbout)
	{
		ImGui::ShowAboutWindow(&bDrawImGuiAbout);
	}

	for (UDevUIWindow* Window : AllWindows)
	{
		if (Window->ShouldDraw())
		{
			bool bStayOpen = DrawWindow(Window);
			Window->SetDraw(bStayOpen);
		}
	}
}

bool UDevUISubsystem::DrawWindow(UDevUIWindow* Window)
{
	bool bClose = Window->ShouldDraw();
	ImGui::Begin(TCHAR_TO_ANSI(*Window->GetWindowName()), &bClose, Window->GetWindowFlags());

	if (!bClose)
	{
		Window->SetDraw(bClose);
		return false;
	}

	bool bStayOpen = Window->Draw(ObjectWorld);
	ImGui::End();

	return bStayOpen;
}
