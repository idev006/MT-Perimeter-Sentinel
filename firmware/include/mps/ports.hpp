#pragma once
#include "types.hpp"
#include <cstddef>
#include <optional>

namespace mps {

struct ISensor {
  virtual ~ISensor() = default;
  virtual bool healthy() const = 0;
};

struct ITransport {
  virtual ~ITransport() = default;
  virtual bool available() const = 0;
  virtual SendResult send(const Event&) = 0;
};

struct IEventStore {
  virtual ~IEventStore() = default;
  virtual bool push(const Event&) = 0;
  virtual std::optional<Event> peek() const = 0;
  virtual bool pop() = 0;
  virtual std::size_t size() const = 0;
};

}  // namespace mps
