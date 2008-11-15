# Rake file for managing Ruby gems
#
# rake                # build test with cmake
# rake gem            # creates a gem

require 'rubygems'

require 'rake/testtask'
require 'rake/rdoctask'
require 'rake/gempackagetask'
 
PROJECT_NAME = "biolib"
BIOLIB_VERSION = `cat VERSION`

desc "Building BioLib for this system"
task :default => [:build, :test, :install]
 
task :build do
  # Dir.chdir('../..') do
    install_path = File.expand_path(File.dirname(__FILE__))
    sh "cmake -DBUILD_RUBY:BOOLEAN=TRUE -DCMAKE_INSTALL_PREFIX=/usr ."
    sh "make"
  # end
end
 
task :test do
  sh "make test"
end
 
task :install do
  # this may need to be adapted for a gem!
  sh "make install"
end
 
desc "Clean up everything"
task :clean => [:clobber] do
end
 
spec = Gem::Specification.new do |s|
  s.platform = Gem::Platform::CURRENT
  s.required_ruby_version = ">=1.8.0"
  s.name = PROJECT_NAME
  s.version = BIOLIB_VERSION
  s.summary = 'BioLib'
  s.homepage = 'http://biolib.open-bio.org/'
  s.author = 'Pjotr Prins'
  s.email = "pjotr.public03@thebird.nl"

  s.description = <<-END
	BioLib
END
  s.extensions << 'Rakefile'

  s.has_rdoc = false
  # s.extra_rdoc_files = [ "README.rdoc" ]
  # s.rdoc_options = [ "--main", "README.rdoc" ]

  # s.test_suite_file = "test/tests.rb"

  patterns = [
    'Rakefile',
		'**/CMakeLists.txt',
    'LICENSE', 'README', 'VERSION', 'INSTALL', 'TODO',
		'cmake_modules/*',
		'doc/*.txt',
		'src/clibs/biolib*/**/*.{h,c,txt}',
		'src/clibs/example-*/*.{h,c,txt}',
		'src/clibs/affyio-*/src/*.{h,c,txt}',
		'src/bindings/swig/*.i',
		'src/bindings/swig/ruby/**/*.{rb,i}',
		'src/test/**/*'
  ]
 
  s.files = patterns.map {|p| Dir.glob(p) }.flatten

  s.require_paths = ['.']
end
 
Rake::GemPackageTask.new(spec) do |pkg|
end


