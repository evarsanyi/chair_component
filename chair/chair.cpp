/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#include "chair.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome { namespace chair {

static const char *const TAG = "chair";

Chair::~Chair()
{
}

void
Chair::setup()
{
    ESP_LOGI(TAG, "Chair::setup()");
    backMotor_.setup(pin_back_up_, pin_back_dn_);
    legMotor_.setup(pin_leg_up_, pin_leg_dn_);
    back_up_.setup(pin_back_up_but_);
    back_dn_.setup(pin_back_dn_but_);
    leg_up_.setup(pin_leg_up_but_);
    leg_dn_.setup(pin_leg_dn_but_);
}

void
Chair::dump_config()
{
    ESP_LOGI(TAG, "Chair");
    ESP_LOGCONFIG(TAG, "  Model: Lazyboy");
    LOG_PIN("  back_up Pin: ", this->pin_back_up_);
    LOG_PIN("  back_dn Pin: ", this->pin_back_dn_);
    LOG_PIN("  leg_up Pin: ", this->pin_leg_up_);
    LOG_PIN("  leg_dn Pin: ", this->pin_leg_dn_);
    LOG_PIN("  back_up_but Pin: ", this->pin_back_up_but_);
    LOG_PIN("  back_dn_but Pin: ", this->pin_back_dn_but_);
    LOG_PIN("  leg_up_but Pin: ", this->pin_leg_up_but_);
    LOG_PIN("  leg_dn_but Pin: ", this->pin_leg_dn_but_);
}

void
Chair::loop()
{
    // ESP_LOGI(TAG, "Chair::loop()");
    back_up_.handle();
    back_dn_.handle();
    leg_up_.handle();
    leg_dn_.handle();
    backMotor_.loop();
    legMotor_.loop();
}

void
Chair::button_short_press(int id)
{
ESP_LOGI(TAG, "Chair::button_short_press(%d)", id);
    switch (static_cast<ButtonType>(id)) {
    case ButtonType::BACK_UP:
	if (backMotor_.running()) {
	    backMotor_.stop();
	} else {
	    backMotor_.startUp();
	}
	backHeld_ = false;
	break;
    case ButtonType::BACK_DOWN:
	if (backMotor_.running()) {
	    backMotor_.stop();
	} else {
	    backMotor_.startDown();
	}
	backHeld_ = false;
	break;
    case ButtonType::LEG_UP:
	if (legMotor_.running()) {
	    legMotor_.stop();
	} else {
	    legMotor_.startUp();
	}
	legHeld_ = false;
	break;
    case ButtonType::LEG_DOWN:
	if (legMotor_.running()) {
	    legMotor_.stop();
	} else {
	    legMotor_.startDown();
	}
	legHeld_ = false;
	break;
    }
}

void
Chair::button_double_press(int id)
{
ESP_LOGI(TAG, "Chair::button_double_press(%d)", id);
}

void
Chair::button_long_press(int id)
{
ESP_LOGI(TAG, "Chair::button_long_press(%d)", id);
    switch (static_cast<ButtonType>(id)) {
    case ButtonType::BACK_UP:
	backMotor_.startUp();
	backHeld_ = true;
	break;
    case ButtonType::BACK_DOWN:
	backMotor_.startDown();
	backHeld_ = true;
	break;
    case ButtonType::LEG_UP:
	legMotor_.startUp();
	legHeld_ = true;
	break;
    case ButtonType::LEG_DOWN:
	legMotor_.startDown();
	legHeld_ = true;
	break;
    }
}

void
Chair::button_very_long_press(int id)
{
ESP_LOGI(TAG, "Chair::button_very_long_press(%d)", id);
}

void
Chair::button_release(int id)
{
ESP_LOGI(TAG, "Chair::button_release(%d)", id);
    switch (static_cast<ButtonType>(id)) {
    case ButtonType::BACK_UP:
    case ButtonType::BACK_DOWN:
	if (backHeld_) {
	    backMotor_.stop();
	    backHeld_ = false;
	}
	break;
    case ButtonType::LEG_UP:
    case ButtonType::LEG_DOWN:
	if (legHeld_) {
	    legMotor_.stop();
	    legHeld_ = false;
	}
	break;
    }
}

}}
