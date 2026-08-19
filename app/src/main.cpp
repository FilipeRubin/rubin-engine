#include "graphics-window.h"
#include "app.h"

const int WINDOWS_COUNT = 1;

bool TryInitializeGraphicsWindow(GraphicsWindow& graphicsWindow);

int main()
{
	GraphicsWindow graphicsWindows[WINDOWS_COUNT];
	App apps[WINDOWS_COUNT];
	for (int i = 0; i < WINDOWS_COUNT; i++)
	{
		if (not TryInitializeGraphicsWindow(graphicsWindows[i]))
		{
			for (int j = i - 1; j >= 0; j--)
			{
				graphicsWindows[j].Finalize();
			}
			return 1;
		}
		else
		{
			apps[i].Init(graphicsWindows[i]);
		}
	}

	for (int i = 0; i < WINDOWS_COUNT; i++)
	{
		graphicsWindows[i].GraphicsBackend().MakeCurrent();
		apps[i].Start();
	}

	while (GraphicsWindow::IsAnyWindowOpen())
	{
		for (int i = 0; i < WINDOWS_COUNT; i++)
		{
			if (not graphicsWindows[i].IsInitialized())
			{
				continue;
			}
			else if (graphicsWindows[i].ShouldClose())
			{
				graphicsWindows[i].Finalize();
				continue;
			}
			graphicsWindows[i].BeginDraw();
			apps[i].Update();
			graphicsWindows[i].EndDraw();
		}
	}

	for (int i = 0; i < WINDOWS_COUNT; i++)
	{
		if (graphicsWindows[i].IsInitialized())
		{
			graphicsWindows[i].Finalize();
		}
	}

	return 0;
}

bool TryInitializeGraphicsWindow(GraphicsWindow& graphicsWindow)
{
	WindowParameters params
	{
		.title = L"Game",
		.width = 1280,
		.height = 720
	};

	if (not graphicsWindow.TryInitialize(params))
	{
		return false;
	}

	return true;
}
