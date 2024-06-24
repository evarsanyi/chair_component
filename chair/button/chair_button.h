/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/button/button.h"

namespace esphome {
namespace chair {

class Chair;

class ChairButton : public button::Button, public Component {
 public:
  ChairButton(Chair *chair) { this->chair_ = chair; }
  void dump_config() override;
  void set_but_id(int id) { but_id_ = id; };

 protected:
  void press_action() override;

  int but_id_;
  Chair* chair_;
};

}  // namespace chair
}  // namespace esphome
