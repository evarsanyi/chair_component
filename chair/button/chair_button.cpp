/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#include "chair_button.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "../chair.h"

namespace esphome {
namespace chair {

static const char *const TAG = "chair.button";

void ChairButton::dump_config() { LOG_BUTTON("", "Chair Button", this); }
void ChairButton::press_action() {
    ESP_LOGI(TAG, "ChairButton virtual short press %d", but_id_);
    chair_->button_short_press(but_id_);
}

}  // namespace chair
}  // namespace esphome
