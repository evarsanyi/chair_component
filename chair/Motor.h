/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#pragma once

#include "esphome/core/hal.h"
#include "esphome/core/log.h"

static const char *const TAG = "Motor";

namespace esphome {
namespace chair {

using ::esphome::GPIOPin;
using ::esphome::gpio::FLAG_OUTPUT;

template<typename OWN>
class Motor {
public:
    Motor(OWN& own, const char* name) :
      own_(own),
      name_(name)
    {
    }

    void
    setup(GPIOPin* up, GPIOPin* down) {
	up_ = up;
	down_ = down;
	up_->pin_mode(FLAG_OUTPUT);
	down_->pin_mode(FLAG_OUTPUT);
	stop();
    }

    bool
    running() {
	return running_ != 0;
    }

    // NB: inverted outputs
    //
    void
    startUp() {
ESP_LOGE(TAG, "%s: motor: start up", name_);
	up_->digital_write(false);
	down_->digital_write(true);
	running_ = millis();
    }

    void
    startDown() {
ESP_LOGE(TAG, "%s motor: start down", name_);
	down_->digital_write(false);
	up_->digital_write(true);
	running_ = millis();
    }

    void
    stop() {
ESP_LOGE(TAG, "%s motor: stop", name_);
	up_->digital_write(true);
	down_->digital_write(true);
	running_ = 0;
    }

    void
    loop() {
	if (running_) {
	    if (millis() - running_ > 10000) {
		stop();
	    }
	}
    }

private:
    OWN& own_;
    const char* name_;
    int running_{0};
    GPIOPin* up_;
    GPIOPin* down_;
};

} }
