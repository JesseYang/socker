# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'socker/version'

Gem::Specification.new do |spec|
  spec.name          = "socker"
  spec.version       = Socker::VERSION
  spec.authors       = ["JesseYang"]
  spec.email         = ["jesse.yang1985@gmail.com"]
  spec.summary       = %q{Socket tools in C.}
  spec.description   = %q{Socket tools in C.}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib", "ext"]

  spec.add_development_dependency "bundler", "~> 1.6"
  spec.add_development_dependency "rake"

  spec.platform = Gem::Platform::CURRENT
end
