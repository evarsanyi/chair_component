/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#include "chair_switch.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace chair {

static const char *const TAG = "chair.switch";

void ChairSwitch::dump_config() { LOG_SWITCH("", "Chair Switch", this); }
void ChairSwitch::write_state(bool state) {
  // Acknowledge
  this->publish_state(false);

  if (state) {
    ESP_LOGI(TAG, "Chair switched...");
  }
}

}  // namespace chair
}  // namespace esphome
