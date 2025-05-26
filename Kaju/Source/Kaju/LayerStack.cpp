#include "PCH.h"
#include "LayerStack.h"

KJ::LayerStack::LayerStack()
{
	m_layerInsert = m_layers.begin();
}

KJ::LayerStack::~LayerStack()
{
	for (auto layer : m_layers)
	{
		delete layer;
	}
}

void KJ::LayerStack::PushLayer(Layer* layer)
{
	m_layerInsert = m_layers.emplace(m_layerInsert, layer);
}

void KJ::LayerStack::PushOverlay(Layer* overlay)
{
	m_layers.emplace_back(overlay);
}

void KJ::LayerStack::PopLayer(Layer* layer)
{
	auto itr = std::find(m_layers.begin(), m_layers.end(), layer);
	if (itr != m_layers.end())
	{
		m_layers.erase(itr);
		m_layerInsert--;
	}
}

void KJ::LayerStack::PopOverlay(Layer* overlay)
{
	auto itr = std::find(m_layers.begin(), m_layers.end(), overlay);
	if (itr != m_layers.end())
	{
		m_layers.erase(itr);
	}
}
