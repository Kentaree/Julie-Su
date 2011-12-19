#!/usr/bin/env ruby

#
# google.rb
# Downloads a google page to get search results
# Based on SirFire's VB code
#
# Usuage : google.rb <searchterms>
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

def replaceHtmlSymbols (str)

	# Replace &lt;
	str = str.gsub('&lt;', '<')

	# Replace &gt;
	str = str.gsub('&gt;', '>')

	str = str.gsub('&amp;', '&')
	str = str.gsub('&#39;', '\'')
	str = str.gsub('&#8211;', '-')
	str = str.gsub('&ndash;', '-')
	str = str.gsub('&#8217;', '\'')
	str = str.gsub('&#8230;', '...')
	str = str.gsub('&#8220;', '"')
	str = str.gsub('&#8221;', '"')
	str = str.gsub('&hellip;', '...')
	str = str.gsub('&rsquo;', '\'')

	str = str.gsub('&raquo;', '>>')
	str = str.gsub('&quot;', '\'')

	# From youtube, no idea what it is
	str = str.gsub('&#x202a;', '')
	str = str.gsub('&#x202c;&rlm;', '')

	return str;

end

# TinyURL function
def tinyURLize (urlstr)
	# Destroy protocol on front, it if has it
	#if urlstr [0 .. 6] == "http://":
	#	urlstr = urlstr [7 .. urlstr.length()]
	#end

	urlstr = replaceSpecial(urlstr)

	# Put &s back in
	while urlstr.index('%26') != nil
		urlstr [urlstr.index('%26'), '%26'.length()] = "&"
	end

	url = URI.parse('http://tinyurl.com/create.php?url=' + urlstr)
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.get('/create.php?url=' + urlstr)
	}

	body = StringIO.new(res.body)

	while !body.eof
		curline = body.readline()
		if curline.index("<blockquote><b>http://tinyurl.com/") != nil:
			# Its this line!
			curline = curline[curline.index("<blockquote><b>") + "<blockquote><b>".length() .. curline.index("</b>") - 1]

			return curline
		end
	end
end

urlstr = ARGV.join("%20")

# Quick exit, if its dropbox just say dropbox
if urlstr.index("dl.dropbox.com/u/") != nil:
	puts "Dropbox";
	exit
end

	# Now the fun part, get the webpage with sending POST requests
	url = URI.parse(urlstr)
	res = Net::HTTP.get_response(url)

	resultCode = res.code

	if resultCode == '302' || resultCode == '301':
		# Retry : moved or found
		url = URI.parse(res["Location"])
		res = Net::HTTP.get_response(url)
	end

	body = res.body #StringIO.new(res.body)

	#puts body

	# We want <title> to </title>
	if body.index("<title>") == nil:
		exit
	end

	title = body[body.index("<title>") + "<title>".length() .. body.index("</title>")-1]

	# Cleanup
	title = title.gsub(/\n/, " " )
	title = title.gsub(/\t/, " " )

	while title.index("  ") != nil:
		title = title.gsub(/  /, " " )
	end

#	while title.index("\n") != nil:
#		title[title.index("\n") .. title.index("\n")+"\n".length()] = " "
#	end

#	while title.index("\t") != nil:
#		title[title.index("\t") .. title.index("\t") + "\t".length()]= " "
#	end

#	while title.index("  ") != nil:
#		title[title.index("  ") .. title.index("  ") + "  ".length()] = " "
#	end

	while title.index("&mdash;") != nil;
		title[title.index("&mdash;") .. title.index("&mdash;") + "&mdash;".length()] = "- "
	end

	title.strip!

	print replaceHtmlSymbols(title)
