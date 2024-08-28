#include "DevUIWindow.h"

#include "DevUICommon.h"

bool UDevUIWindow::Draw(UWorld* World)
{
	return false;
}

void UDevUIWindow::OnStateChanged() {}

FString UDevUIWindow::GetWindowName()
{
	// Default to the class name as UObjects name is (class)__Default
	return *GetClass()->GetName();
}

FString UDevUIWindow::GetWindowHelp()
{
	return FString();
}

ImGuiWindowFlags UDevUIWindow::GetWindowFlags() const
{
	return ImGuiWindowFlags_None;
}

bool UDevUIWindow::ShouldDraw()
{
	return bShouldDraw;
}

void UDevUIWindow::ToggleDraw()
{
	bShouldDraw = !bShouldDraw;
	OnStateChanged();
}

void UDevUIWindow::SetDraw(bool bDraw)
{
	bool bOld	= bShouldDraw;
	bShouldDraw = bDraw;

	if (bOld != bShouldDraw)
	{
		OnStateChanged();
	}
}
