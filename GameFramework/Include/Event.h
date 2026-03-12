#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * @brief A simple event system that allows subscribing, unsubscribing, and invoking event handlers with arbitrary arguments.
 */
template <typename... Args>
class Event
{
 public:

  using Handler = function<void(Args...)>;

  Event() = default;
  ~Event() = default;

  inline void
  subscribe(const Handler& handler)
  {
    m_listeners.push_back(handler);
  }

  inline void
  unsubscribe(const Handler& handler)
  {
    auto it = find(m_listeners.begin(), m_listeners.end(), handler);
    if (it != m_listeners.end()) {
      m_listeners.erase(it);
    }
  }

  void
  invoke(Args... args)
  {
    for (const auto& handler : m_listeners) {
      handler(args...);
    }
  }

 private:

  Vector<Handler> m_listeners;
};