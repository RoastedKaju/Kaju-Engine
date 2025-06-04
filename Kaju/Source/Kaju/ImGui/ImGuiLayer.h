#pragma once

#include "Kaju/Layer.h"

namespace KJ
{
	class ImGuiLayer : public Layer
	{
	public:
		KAJU_API ImGuiLayer();
		KAJU_API ~ImGuiLayer();

		KAJU_API void OnAttach() override;
		KAJU_API void OnDetach() override;
		KAJU_API void OnUpdate() override;
		KAJU_API void OnEvent(Event& event) override;

	private:
		float m_time = 0.0f;
	};
}
