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
# Note: this runner script is not used in the cmake build framework
#
#

# Use runner from its own directory
cwd = File.dirname(__FILE__)
Dir.chdir(cwd)

$UNITTEST=true

require 'test/unit'
# require 'test_fasta'
require 'test_rqtl'
require 'test_rqtl_mqm'

# --- now run the doctests

# Kernel.system('../../../../tools/rubydoctest/bin/rubydoctest test_rqtl.rb')

