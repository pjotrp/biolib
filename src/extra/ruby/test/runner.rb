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

# require 'test/unit'

# require 'test_rqtl'

# --- now run the doctests

Kernel.system('../../../../tools/rubydoctest/bin/rubydoctest test_rqtl.rb')

