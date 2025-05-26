#pragma once

#include "Kaju/Core.h"
#include "Kaju/Events/Event.h"

namespace KJ
{
	class Layer
	{
	public:
		KAJU_API Layer(const std::string& name = "Layer");
		KAJU_API virtual ~Layer();

		KAJU_API virtual void OnAttach() {}
		KAJU_API virtual void OnDetach() {}
		KAJU_API virtual void OnUpdate() {}
		KAJU_API virtual void OnEvent(Event& event) {}

		KAJU_API inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;

	};
}