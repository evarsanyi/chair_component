/*
 * Copyright (c) 2024 Eric Varsanyi, All Rights Reserved
 */
#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "Button.h"
#include "Motor.h"

namespace esphome {
namespace chair {

using ::esphome::GPIOPin;

enum class ButtonType {
    BACK_UP,
    BACK_DOWN,
    LEG_UP,
    LEG_DOWN
};

class Chair: public Component {
public:
    virtual ~Chair();
    void setup() override;
    void dump_config() override;
    void loop() override;
    void set_pin_back_up(GPIOPin *pin) { pin_back_up_ = pin; }
    void set_pin_back_dn(GPIOPin *pin) { pin_back_dn_ = pin; }
    void set_pin_leg_up(GPIOPin *pin) { pin_leg_up_ = pin; }
    void set_pin_leg_dn(GPIOPin *pin) { pin_leg_dn_ = pin; }
    void set_pin_back_up_but(GPIOPin *pin) { pin_back_up_but_ = pin; }
    void set_pin_back_dn_but(GPIOPin *pin) { pin_back_dn_but_ = pin; }
    void set_pin_leg_up_but(GPIOPin *pin) { pin_leg_up_but_ = pin; }
    void set_pin_leg_dn_but(GPIOPin *pin) { pin_leg_dn_but_ = pin; }

    // Callbacks for physical button presses
    void button_short_press(int id);
    void button_double_press(int id);
    void button_long_press(int id);
    void button_very_long_press(int id);
    void button_release(int id);

protected:
    GPIOPin *pin_back_up_;
    GPIOPin *pin_back_dn_;
    GPIOPin *pin_leg_up_;
    GPIOPin *pin_leg_dn_;
    GPIOPin *pin_back_up_but_;
    GPIOPin *pin_back_dn_but_;
    GPIOPin *pin_leg_up_but_;
    GPIOPin *pin_leg_dn_but_;

    using Mot = Motor<Chair>;
    Mot backMotor_{*this, "Back"};
    Mot legMotor_{*this, "Leg"};

    using But = Button<Chair>;
    But back_up_{*this, static_cast<int>(ButtonType::BACK_UP)};
    But back_dn_{*this, static_cast<int>(ButtonType::BACK_DOWN)};
    But leg_up_{*this, static_cast<int>(ButtonType::LEG_UP)};
    But leg_dn_{*this, static_cast<int>(ButtonType::LEG_DOWN)};

    bool backHeld_{false};
    bool legHeld_{false};
};

}  // namespace chair
}  // namespace esphome
