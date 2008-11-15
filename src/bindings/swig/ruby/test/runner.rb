#!/usr/bin/env ruby
#
# Main unit test suite runner for BioLib (Ruby)
#
# Running a specific test:
#
# It's possible to run just one (or more) tests out of a full test case:
# 
# >> ruby -w tc_Number2.rb --name test_method
# Loaded suite tc_Number2
#
require 'optparse'
require 'ostruct'

$test_cwd = File.dirname(__FILE__)
$: << $test_cwd << $test_cwd+'/..' 

options = OpenStruct.new()
opts = OptionParser.new() { |opts|
	opts.on_tail("-h", "--help", "Print this message") {
		print(opts)
		exit()
	}

	# opts.on("-c", "--create", "create data for regression tests") {
	# 		options.create = true
	# }

}
opts.parse(ARGV)

# Remove these, otherwise the unit test handler balks...
ARGV.delete('--create')
ARGV.delete('-c')

require 'test/unit'

if(Process.euid == 0)
	print("You are running the tests with root priviliges!\n")
end

# print "Use the -c switch to create new regression tests\n"

# require 'libcfenjin/test/regression'
# Cfruby.regressiontest_create(options.create)

require 'test_affyio'

