require 'rbconfig'

# Print all available configuration options
Config::CONFIG.each do |k,v|
  puts "#{k}: #{v}"
end                                        

