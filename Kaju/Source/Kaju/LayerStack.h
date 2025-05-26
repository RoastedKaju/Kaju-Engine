#pragma once

#include "Kaju/Core.h"
#include "Layer.h"

namespace KJ
{
	class LayerStack
	{
	public:
		KAJU_API LayerStack();
		KAJU_API ~LayerStack();

		KAJU_API void PushLayer(Layer* layer);
		KAJU_API void PushOverlay(Layer* overlay);
		KAJU_API void PopLayer(Layer* layer);
		KAJU_API void PopOverlay(Layer* overlay);

		KAJU_API std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		KAJU_API std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
		std::vector<Layer*>::iterator m_layerInsert;
	};
}