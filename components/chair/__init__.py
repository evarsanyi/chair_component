import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import (
    CONF_NAME,
    CONF_ID,
)

CONF_PIN_BACK_UP = "pin_back_up"
CONF_PIN_BACK_DN = "pin_back_dn"
CONF_PIN_LEG_UP = "pin_leg_up"
CONF_PIN_LEG_DN = "pin_leg_dn"
CONF_PIN_BACK_UP_BUT = "pin_back_up_but"
CONF_PIN_BACK_DN_BUT = "pin_back_dn_but"
CONF_PIN_LEG_UP_BUT = "pin_leg_up_but"
CONF_PIN_LEG_DN_BUT = "pin_leg_dn_but"

chair_ns = cg.esphome_ns.namespace("chair")
Chair = chair_ns.class_("Chair", cg.Component, cg.PollingComponent)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Chair),
            cv.Required(CONF_PIN_BACK_UP): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_BACK_DN): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_LEG_UP): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_LEG_DN): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_BACK_UP_BUT): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_BACK_DN_BUT): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_LEG_UP_BUT): pins.gpio_output_pin_schema,
            cv.Required(CONF_PIN_LEG_DN_BUT): pins.gpio_output_pin_schema,
            cv.Required(CONF_NAME): cv.string,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    pin_back_up = await cg.gpio_pin_expression(config[CONF_PIN_BACK_UP])
    cg.add(var.set_pin_back_up(pin_back_up))
    pin_back_dn = await cg.gpio_pin_expression(config[CONF_PIN_BACK_DN])
    cg.add(var.set_pin_back_dn(pin_back_dn))
    pin_leg_dn = await cg.gpio_pin_expression(config[CONF_PIN_LEG_DN])
    cg.add(var.set_pin_leg_dn(pin_leg_dn))
    pin_leg_up = await cg.gpio_pin_expression(config[CONF_PIN_LEG_UP])
    cg.add(var.set_pin_leg_up(pin_leg_up))
    pin_back_up_but = await cg.gpio_pin_expression(config[CONF_PIN_BACK_UP_BUT])
    cg.add(var.set_pin_back_up_but(pin_back_up_but))
    pin_back_dn_but = await cg.gpio_pin_expression(config[CONF_PIN_BACK_DN_BUT])
    cg.add(var.set_pin_back_dn_but(pin_back_dn_but))
    pin_leg_dn_but = await cg.gpio_pin_expression(config[CONF_PIN_LEG_DN_BUT])
    cg.add(var.set_pin_leg_dn_but(pin_leg_dn_but))
    pin_leg_up_but = await cg.gpio_pin_expression(config[CONF_PIN_LEG_UP_BUT])
    cg.add(var.set_pin_leg_up_but(pin_leg_up_but))
