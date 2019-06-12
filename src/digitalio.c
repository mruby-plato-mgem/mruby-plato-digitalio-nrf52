#ifndef NO_NRFSDK
  #include "sdk_config.h"
  #include "boards.h"
  #include "app_util_platform.h"
  #include "nrf_gpio.h"
  #include "nrf_delay.h"
  #include "nrf_log.h"
#endif /* NO_NRFSDK */

#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include <stdbool.h>

// static mrb_value
// mrb_dio_init(mrb_state *mrb, mrb_value self)
// {
//   mrb_int pin;
//   mrb_sym io = mrb_intern_lit(mrb, "output");
//   mrb_bool out = true;

//   mrb_get_args(mrb, "i|n", &pin, &io);

//   mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@pin"), mrb_fixnum_value(pin));
// #ifndef NO_NRFSDK
//   if (io == mrb_intern_lit(mrb, "output")) {
//     nrf_gpio_cfg_output(pin);
//     out = true;
//   }
//   else if (io == mrb_intern_lit(mrb, "input")) {
//     nrf_gpio_cfg_input(pin);
//     out = false;
//   }
//   else {
//     mrb_raisef(mrb, E_ARGUMENT_ERROR, "Illegal input/output mode. (%S)", mrb_symbol_value(io));
//   }
// #endif /* NO_NRFSDK */
//   mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@out"), mrb_bool_value(out));

//   return self;
// }

static mrb_value
mrb_dio_read(mrb_state *mrb, mrb_value self)
{
  mrb_value vpin, vout;
  mrb_int v = 0;

  vpin = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@pin"));
  vout = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@out"));

#ifndef NO_NRFSDK
  if (mrb_nil_p(vout) || mrb_bool(vout)) {
    /* configure pin to digital-in */
    nrf_gpio_cfg_input(mrb_fixnum(vpin), NRF_GPIO_PIN_NOPULL);
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@out"), mrb_false_value());
  }
  v = nrf_gpio_pin_read(mrb_fixnum(vpin));
#endif /* NO_NRFSDK */

  return mrb_fixnum_value(v);
}

static mrb_value
mrb_dio_write(mrb_state *mrb, mrb_value self)
{
  mrb_value vpin, vout;
  mrb_int v;

  mrb_get_args(mrb, "i", &v);

  vpin = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@pin"));
  vout = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@out"));

#ifndef NO_NRFSDK
  if (mrb_nil_p(vout) || !mrb_bool(vout)) {
    /* configure pin to digital-out */
    nrf_gpio_cfg_output(mrb_fixnum(vpin));
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@out"), mrb_true_value());
  }
  nrf_gpio_pin_write(mrb_fixnum(vpin), v);
#endif /* NO_NRFSDK */

  return mrb_fixnum_value(v);
}

void
mrb_mruby_plato_digitalio_nrf52_gem_init(mrb_state *mrb)
{
  struct RClass *plato  = mrb_module_get(mrb, "Plato");
  struct RClass *gpio   = mrb_class_get_under(mrb, plato, "GPIO");
  struct RClass *dio    = mrb_define_class_under(mrb, plato, "DigitalIO", gpio);

  // mrb_define_method(mrb, dio, "initialize", mrb_dio_init,   MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, dio, "read",       mrb_dio_read,   MRB_ARGS_NONE());
  mrb_define_method(mrb, dio, "write",      mrb_dio_write,  MRB_ARGS_REQ(1));
}

void
mrb_mruby_plato_digitalio_nrf52_gem_final(mrb_state *mrb)
{
}
