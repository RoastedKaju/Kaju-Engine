#pragma once

#include "Kaju/Core.h"
#include "PCH.h"

namespace KJ
{
	/**
	* Events in Kaju Engine are blocking, which means once dispatched it must be delta right away
	*/

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None							= 0,
		EventCategoryApplication		= 1 << 0,
		EventCategoryInput				= 1 << 1,
		EventCategoryKeyboard			= 1 << 2,
		EventCategoryMouse				= 1 << 3,
		EventCategoryMouseButton		= 1 << 4
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

#define BIND_EVENT(fn, object) std::bind(fn, object, std::placeholders::_1)

	class KAJU_API Event
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_event{ event } {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.m_Handled = func(*(T*)&m_event);
				return true;
			}

			return false;
		}

	private:
		Event& m_event;
	};
}