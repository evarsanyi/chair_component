/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#pragma once

#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome { namespace chair {

using esphome::GPIOPin;
using esphome::gpio::FLAG_INPUT;
using esphome::gpio::FLAG_PULLUP;

static const char *const MTAG = "Button";

/*
 * Physical button IO - debounce and gestures (short, double, hold)
 */
template<typename OWN>
class Button {
public:
    Button(OWN& owner, int id) :
	owner_(owner),
	id_(id)
    {
    }
    void setup(GPIOPin* pin) {
	pin_ = pin;
	pin_->pin_mode(FLAG_INPUT | FLAG_PULLUP);

#if 0
	// disable button if it is "pressed" unintentionally
	if (isButtonPressed()) {
	    ESP_LOGE(MTAG, " input %s (id=%d) stuck, disabling", pin_->dump_summary().c_str(), id_);
	    ignore_ = true;
	}
#endif
    }
    bool isButtonPressed() {
	return pin_->digital_read() == true;		// active low
    }

    void handle() {
	if (ignore_) {
	    return;
	}
	bool signalRelease{false};
	if (isButtonPressed()) {
	    if (!buttonPressedBefore_) {
		buttonPressedTime_ = millis();
ESP_LOGE(MTAG, " button press id=%d", id_);
	    }
	    buttonPressedBefore_ = true;

	    if (millis() - buttonPressedTime_ > 600) {
		// long press
		if (!buttonLongPressed_) {
		    owner_.button_long_press(id_);
		    buttonLongPressed_ = true;
		}
	    }
	} else if (!isButtonPressed() && buttonPressedBefore_) {
ESP_LOGE(MTAG, " button release id=%d", id_);
	    // released
	    long dur = millis() - buttonPressedTime_;
	    if (dur < 50) {
		//too short "press", debounce
		buttonPressedBefore_ = false;
		return;
	    }
	    bool doublePress = buttonWaitTime_;
	    buttonWaitTime_ = 0;

	    if (dur > 6000) { 
		//very long press
        	// initAP(true);
		owner_.button_very_long_press(id_);
	    } else if (!buttonLongPressed_) {
		//short press
		if (doublePress) {
		    owner_.button_double_press(id_);
		} else {
		    buttonWaitTime_ = millis();
		}
	    }
	    buttonPressedBefore_ = false;
	    buttonLongPressed_ = false;
	    signalRelease = true;
	}
	if (buttonWaitTime_ && millis() - buttonWaitTime_ > 450 &&
	       !buttonPressedBefore_) {
	    buttonWaitTime_ = 0;
	    owner_.button_short_press(id_);
	}
	if (signalRelease) {
	    owner_.button_release(id_);
	}
    }

private:
    OWN& owner_;
    GPIOPin* pin_;
    const int id_;
    bool ignore_{false};
    bool buttonPressedBefore_{false};
    bool buttonLongPressed_{false};
    unsigned long buttonPressedTime_{0};
    unsigned long buttonWaitTime_{0};
};

} }
