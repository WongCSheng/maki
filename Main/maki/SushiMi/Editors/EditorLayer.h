
#pragma once



namespace Core {

	class ImGuiLayer /*: public Layer*/
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() /*override*/;
		virtual void OnDetach() /*override*/;
		//virtual void OnEvent(Event& e) /*override*/;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

		unsigned GetActiveWidgetID() /*const*/;
	private:
		bool m_BlockEvents = true;
	};

}