#!/usr/bin/env ruby

#
# quote.rb
# Retrieves quotes from devhat's db
#

searchterm = ARGV.join(" ")

if (ARGV.size() > 0)
	if (ARGV[0] == "random")
		print "http://quotes.devhat.net/?action=list&o=random&m=1&mr=1"
	else
		print "http://quotes.devhat.net/kwotes.pl?action=show&id=" + ARGV[0]
	end
else
	print "http://quotes.devhat.net/"
end

