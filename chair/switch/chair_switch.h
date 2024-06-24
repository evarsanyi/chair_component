/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace chair {

class ChairSwitch : public switch_::Switch, public Component {
 public:
  void dump_config() override;

 protected:
  void write_state(bool state) override;
};

}  // namespace chair
}  // namespace esphome
