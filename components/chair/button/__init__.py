import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import button
from esphome.const import (
    CONF_ID,
)

CONF_BUT_ID = "but_id"

from .. import chair_ns, Chair

ChairButton = chair_ns.class_(
    "ChairButton", button.Button, cg.Component
)

CONFIG_SCHEMA = (
	button.button_schema(ChairButton)
	.extend({
	    cv.GenerateID("chair_id"): cv.use_id(Chair),
        cv.Required(CONF_BUT_ID): cv.int_
	}).extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    hub = await cg.get_variable(config["chair_id"])
    var = cg.new_Pvariable(config[CONF_ID], hub)
    await cg.register_component(var, config)
    await button.register_button(var, config)

    but_id = config[CONF_BUT_ID];
    cg.add(var.set_but_id(but_id))
