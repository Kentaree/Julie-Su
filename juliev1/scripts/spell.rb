#!/usr/bin/env ruby

#
# spell.rb
# Spell checks a word
#
# Usuage : spell.rb <word>
#

require 'net/http' # HTTP
require 'uri' # URI
require 'stringio' # Strings

searchterm = ARGV.join(" ")

if /^([0-9]|[a-z]|[A-Z]| )*$/.match(searchterm)
else
	print "Invalid characters : try again"
	exit 0
end

results = %x[echo "#{searchterm}" | aspell -a]

results.each do | result|
	if result.index("&") != nil;
		result[0 .. result.index(":") + ":".length()] = ""
		print result
		exit 0
	end
end

print "Spelled correctly"
