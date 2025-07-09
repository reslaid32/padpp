#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "IBytePadder.h"

namespace padpp
{

struct PadderFactory
{
  using Creator = std::function<std::unique_ptr<IBytePadder>()>;

  static PadderFactory& instance();

  bool register_creator(const std::string& name, Creator creator);
  std::unique_ptr<IBytePadder> create(const std::string& name) const;

private:
  PadderFactory();
  ~PadderFactory();

  PadderFactory(const PadderFactory&) = delete;
  PadderFactory& operator=(const PadderFactory&) = delete;

  mutable std::mutex mutex_;
  std::unordered_map<std::string, Creator> creators_;
};

struct PadderRegistrar
{
  PadderRegistrar(const std::string& name, PadderFactory::Creator creator);
};

}