#pragma once


namespace AGE
{

	class AssetRegistryWindow
	{
	public:
		AssetRegistryWindow() = default;
		~AssetRegistryWindow() = default;

		void OnImGuiRender();

		void RenderWindow(const char* WindowName, bool* IsOpen);

		void RestoreWindow();


	private:

		bool bOpened = false;
	};

}