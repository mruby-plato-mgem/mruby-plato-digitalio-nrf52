MRuby::Gem::Specification.new('mruby-plato-digitalio-nrf52') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Hiroshi Mimaki'
  spec.description = 'Plato::DigitaIO class for nRF52'

  spec.cc.defines << %w(NO_NRFSDK)

  spec.add_test_dependency('mruby-plato-gpio')
  spec.add_test_dependency('mruby-plato-digitalio')
end
