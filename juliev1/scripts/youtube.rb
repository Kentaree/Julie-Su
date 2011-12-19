#!/usr/bin/env ruby

#
# youtube.rb
# Downloads a youtube page to get search results
# Usuage : youtube.rb <searchterms>
#

require 'net/http' # HTTP lib
require 'uri' # URI lib
require 'stringio' # Strings
require 'cgi'

def replaceSpecial (searchterm)
	# Replace spaces
	while searchterm.index(' ') != nil
		searchterm [searchterm.index(' ')] = '%20'
	end
	
	# Replace +s
	while searchterm.index('+') != nil
		searchterm [searchterm.index('+')] = '%2B'
	end
	
	# Replace &s
	while searchterm.index('&') != nil
		searchterm [searchterm.index('&')] = '%26'
	end
	
	# Replace "s
	while searchterm.index('"') != nil
		searchterm [searchterm.index('"')] = '%22'
	end
	
	# Replace 's
	while searchterm.index("'") != nil
		searchterm [searchterm.index("'")] = '%27'
	end
	
	# Replace ^s
	while searchterm.index("^") != nil
		searchterm [searchterm.index("^")] = '%5E'
	end
	
	# Replace <s
	while searchterm.index("<") != nil
		searchterm [searchterm.index("<")] = '%3C'
	end
	
	# Replace >s
	while searchterm.index(">") != nil
		searchterm [searchterm.index(">")] = '%3E'
	end

	return searchterm
end

searchterm = ARGV.join("%20")

searchterm = replaceSpecial(searchterm)

# Grab the search from youtube.com, or recent if we dont have a term
if searchterm != "" then
	url = URI.parse('http://www.youtube.com/results?search_query=' + searchterm + '&search=Search')
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.get('/results?search_query=' + searchterm + '&search=Search')
	}
else
	url = URI.parse('http://www.youtube.com/browse?s=mr&t=t&c=0&l=')
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.get('/browse?s=mr&t=t&c=0&l=')
	}
end

# Read the page
body = StringIO.new(res.body)

while !body.eof
	curline = body.readline()

	# Look for a youtube link
	if curline.index("<a href=\"/watch?") != nil and curline.index("vlcontainer") != nil then
		# Parse!
		curline=curline[curline.index("a href") .. curline.length()]

		curline=curline[curline.index("\"")+1 .. curline.length()]
		localurl=curline[0 .. curline.index("\"")-1]

		description = curline[curline.index("title") .. curline.length()]
		description = description[description.index("\"")+1 .. description.length()]
		description = description[0 .. description.index("\"")-1]

		if searchterm != "" then
			puts description + " : http://www.youtube.com" + localurl
		else
			puts "[recent] " + description + " : http://www.youtube.com" + localurl
		end

		exit
	end
end

# No results
puts "No results found."
