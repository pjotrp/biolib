
require 'rubygems'

spec = Gem::Specification.new do |s|

   s.name = 'biolib'
   s.version = `cat VERSION`
   s.platform = Gem::Platform::RUBY
   s.required_ruby_version = ">=1.8.0"

   s.summary = "BioLib"
	 s.description = "BioLib"

   # s.files = Dir.glob("{doc,ext,lib,test}/**/*")
   s.files = Dir.glob("{doc}/*")
   s.files.concat [ "LICENSE", "README" ]

   # s.require_path = 'lib'

   s.extensions << 'Rakefile'

   s.has_rdoc = false
   # s.extra_rdoc_files = [ "README.rdoc" ]
   # s.rdoc_options = [ "--main", "README.rdoc" ]

   # s.test_suite_file = "test/tests.rb"

   s.author = "Pjotr Prins"
   s.email = "pjotr.public03@thebird.nl"
   s.homepage = "http://biolib.open-bio.org/"

end


if $0==__FILE__
  Gem.manage_gems
  Gem::Builder.new(spec).build
end

