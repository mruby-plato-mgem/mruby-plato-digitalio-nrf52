# mruby-plato-digitalio-nrf52   [![Build Status](https://travis-ci.org/mruby-plato-mgem/mruby-plato-digitalio-nrf52.svg?branch=master)](https://travis-ci.org/mruby-plato-mgem/mruby-plato-digitalio-nrf52)

Plato::GPIO class

## install by mrbgems

- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

  # ... (snip) ...

  conf.gem :git => 'https://github.com/mruby-plato-mgem/mruby-plato-gpio'
  conf.gem :git => 'https://github.com/mruby-plato-mgem/mruby-plato-gpio-nrf52'
  conf.gem :git => 'https://github.com/mruby-plato-mgem/mruby-plato-digitalio'
  conf.gem :git => 'https://github.com/mruby-plato-mgem/mruby-plato-digitalio-nrf52'
end
```

## example

```ruby
io1 = Plato::DigitalIO.new(Plato::GPIO.pin(0, 10))
io2 = Plato::DigitalIO.new(Plato::GPIO.pin(1, 20))
io2.write(io1.low? ? 0 : 1)
```

## License

under the MIT License:

- see LICENSE file
