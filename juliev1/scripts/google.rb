#!/usr/bin/env ruby

#
# google.rb
# Downloads a google page to get search results
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

	# Replacea &amp;
	str = str.gsub('&amp;', '&')

	# Replace &quot;
	str = str.gsub('&quot;', '"')

	# Replace <em>
	str = str.gsub('<em>', ''.concat(0x0002))
	str = str.gsub('</em>', ''.concat(0x000f))
	str = str.gsub('&#39;', '\'')

	str = str.gsub('<b>', ''.concat(0x0002))
	str = str.gsub('</b>', ''.concat(0x000f))

	str = str.gsub('&nbsp', ' ')

	return str;

end

def removeLinks (str)
	str = str.gsub(/<a .*>.*<\/a>/, '')
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

searchterm = ARGV.join("%20")

if searchterm.include? "video" or searchterm.include? "youtube" then
	searchingVideos = true
else
	searchingVideos = false
end

if searchterm [0 .. 9] == "translate:" then
	if searchterm.index(' ') == 10 then
		searchterm = searchterm [searchterm.index(' ')+1 .. searchterm.length()]
	else
		searchterm = searchterm [10 .. searchterm.length()]
	end

	lang_start = searchterm [0 .. searchterm.index(' ')-1]
	searchterm = searchterm [searchterm.index(' ')+1 .. searchterm.length()]
	lang_end = searchterm [0 .. searchterm.index(' ')-1]
	searchterm = searchterm [searchterm.index(' ')+1 .. searchterm.length()]

	searchterm = replaceSpecial(searchterm)

	data='sl='+lang_start+'&tl='+lang_end+'&text='+searchterm

	# Now the fun part, get the webpage with sending POST requests
	url = URI.parse('http://translate.google.com/')
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.post('/', data)
	}

	body = StringIO.new(res.body)
	while !body.eof
		curline = body.readline()

		if curline.index('result_box') != nil then
			str = curline[curline.index('id=result_box') .. curline.length()]
			str = str[str.index('>')+1 .. str.index('</div>')-1]
			str = str[str.index('>')+1 .. str.index('</span>')-1] # Remove span javascript

			# Fix &#39
			while str.index('&#39;') != nil
				str [str.index('&#39;'), '&#39;'.length()] = "'"
			end

			puts "[translate: " + lang_start + " | " + lang_end + " ] " + str
			exit
		end
	end

elsif searchterm [0 .. 4] == "news:" then

	searchterm = replaceSpecial(searchterm)
	searchterm = searchterm [5 .. searchterm.length()]

	url = URI.parse('http://news.google.com/news?hl=en&ned=tus&q=' + searchterm + '&btnG=Search+News')
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.get('/news?hl=en&ned=tus&q=' + searchterm + '&btnG=Search+News')
	}

	body = StringIO.new(res.body)

	while !body.eof
		curline = body.readline()

		# Look for a news entry
		if curline.index('<td valign=top class=j>') != nil then

			# Parse!
			curline = curline[curline.index('<td valign=top class=j>') + '<td valign=top class=j>'.length() + 2 .. curline.length()]
			url = curline[curline.index('"')+1 .. curline.length()]
			url = url[0 .. url.index('"')-1]

			curline = curline[curline.index('"')+1 .. curline.length()]

			description = curline[curline.index('>')+1 .. curline.index('</a>')-1]

			puts "[news] " + description + " : " + url
			exit
		end
	end

	puts "[news] None found"
	exit

elsif searchterm [0 .. 5] == "image:" then
	searchterm = replaceSpecial(searchterm)

	searchterm = searchterm [6 .. searchterm.length()]

	url = URI.parse('http://images.google.com/images?hl=en&q=' + searchterm + '&btnG=Search+images&gbv=1')
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.get('/images?hl=en&q=' + searchterm + '&btnG=Search+images&gbv=1')
	}

	body = StringIO.new(res.body)

	while !body.eof
		curline = body.readline()

		# Look for a google image's url
		if curline.index("/imgres?imgurl=") != nil then
			# Parse!
			curline = curline[curline.index("<a href=/imgres?imgurl=")+ 23 .. curline.length()]
			url = "http://images.google.com/imgres?imgurl=" + curline[0 .. curline.index('>')]
			curline = curline[curline.index('>') + 1 .. curline.length()] # Move past the url
			curline = curline[curline.index('<font face=arial,sans-serif size=-1>') + '<font face=arial,sans-serif size=-1>'.length() .. curline.length()] # Move to the font stuff
			description = curline[0 .. curline.index('</font>') - 1]

			# Now remove html stuff
			while description.index("<b>") != nil
				description [description.index("<b>"), '<b>'.length()] = ''
			end

			while description.index("</b>") != nil
				description [description.index("</b>"), '</b>'.length()] = ''
			end

			while description.index("<br>") != nil
				description [description.index("<br>"), '<br>'.length()] = ' '
			end

			while description.index('&nbsp;') != nil
				description [description.index('&nbsp;'), '&nbsp;'.length()] = ''
			end

			while description.index('<font color=#008000>') != nil
				description [description.index('<font color=#008000>'), '<font color=#008000>'.length()]= ''
			end

			while description.index('<font color=green>') != nil
				description [description.index('<font color=green>'), '<font color=green>'.length()]= ''

			end
			puts "[image] " + tinyURLize(url) + " : " + description
			exit
		end
	end

else # Default parser : use normal google

	searchterm = replaceSpecial(searchterm)
	
	url = URI.parse('http://www.google.com/search?hl=en&q=' + searchterm + '&btnG=Google+Search')
	res = Net::HTTP.start(url.host, url.port) {|http|
		http.get('/search?hl=en&q=' + searchterm + '&btnG=Google+Search', {"User-Agent" => "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_2) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7" })
	}
	
	#puts url

	body = StringIO.new(res.body)

	fullText = ''
	while !body.eof
		curline = body.readline()
		fullText += curline
	end

	if fullText != '' then
		curline = fullText

		while curline.index("\n") != nil
			curline[curline.index("\n"), "\n".length()] = ''
		end

		#
		# Calculator
		#
		if curline.index("/images/icons/onebox/calculator-40.gif") != nil then
			# Calculator call : get the operation/answer
			curline = curline [curline.index('/images/icons/onebox/calculator-40.gif') + 22 .. curline.length()]
			curline = curline [curline.index('<h2') + 3 .. curline.length()]
			curline = curline [curline.index('>') + 1 .. curline.length()]
			equation = curline [0 .. curline.index('</h2') - 1]
	

			# Replace spaces (<font size=-2> </font>) in answer
			while equation.index('<font size=-2>') != nil
				equation [equation.index('<font size=-2>'), '<font size=-2> </font>'.length()] = ''
			end
	
			# Replace sup with stuff
			while equation.index('</sup>') != nil
				equation [equation.index('</sup>'), '</sup>'.length()] = ''
			end
			while equation.index('<sup>') != nil
				equation[equation.index('<sup>'), '<sup>'.length()] = '^'
			end

			# Replace multiplication symbol
			while equation.index('&#215;') != nil
				equation[equation.index('&#215;'), '&#215;'.length()] = 'x'
			end

			# Replace 160 (html space hack) with real space
			while equation.index(160.chr) != nil
				equation[equation.index(160.chr), 1] = ' '
			end

			# Remove random bols that might be there
			while equation.index('<b>') != nil
				equation[equation.index('<b>'), '<b>'.length()] = ''
			end

			puts "[calc] " + equation + " "
			exit
		end
	
		#
		# Currency
		#
		if curline.index('class="currency g"') != nil then
			curline = curline [curline.index('class="currency g"') .. curline.length()]
		#	curline = curline[curline.index("<b>") + 3 .. curline.length()]
		#	curline = curline[0 .. curline.index("</b>")]

			puts "[currency] " + curline
			exit
		end

		#
		# Weather search
		#
		if searchterm [0 .. 7] == "weather:" then
			if curline.index('Weather</b> for') != nil then

				c = curline
				c = c[c.index('Weather</b> for') .. c.length()]
				c = c[c.index('<b>') + 3 .. c.length()]
				place = c[0 .. c.index('</b>') - 1]

				c = c[c.index('<tr>') .. c.length()]

				s = c.index('rowspan=2')
				if (s == nil) then
					s = c.index('rowspan="2"')
				end

				c = c[s .. c.length()]
				c = c[c.index('>') + 1 .. c.length()]
				temperature = c[0 .. c.index(' ')]

				c = c[c.index('Wind:') .. c.length()]		
				wind = c[0 .. c.index('<td>') - 1]

				c = c[c.index('Humidity: ') + 'Humidity: '.length() .. c.length()]
				humidity = 'Humidity: ' + c[0 .. c.index('<td') - 1]

				type = 'Unknown'

				# Calculate C for temperature
				temperature_int = temperature.to_i

				# If your in the USA, defaults to F : convert to C
				#temperature_c = (temperature_int - 32) * 5/9
				#puts "[weather] " + place + " : " + temperature + " (#{temperature_c} C) : " + type + " : " + wind + " : " + humidity

				# Otherwise, convert to F
				temperature_f = temperature_int * 9/5 + 32;
				puts "[weather] " + place + " : #{temperature_int} C" + " (#{temperature_f} F) : " + type + " : " + wind + " : " + humidity

				# And thats all
	
				exit
			end
	
		#
		# Phonebook
		#
	
		# Not weather, due to chicago, IL
		if searchterm [0 .. 7] != "weather:" then
			if curline.index("Phonebook results for") != nil then
				# Phonebook results
				number = curline [curline.index('<b>') + 3 .. curline.index('</b>') - 1]
				curline = curline [curline.index('Phonebook results for') .. curline.length()]
				curline = curline [curline.index('<tr><td>') + 8 .. curline.length()]
		
				name = curline [0 .. curline.index('<td>') - 1]
				curline = curline [curline.index('<td>') + 4 .. curline.length()]
				curline = curline [curline.index('<td>') + 4 .. curline.length()]
				address = curline [0 .. curline.index('<td') - 1]
		
				# Replace &nbsp; in address
				while address.index('&nbsp;') != nil
					address [address.index('&nbsp;'), '&nbsp;'.length()] = ''
				end
		
				puts "[phone] " + name + " : " + number + " :" + address
			end
		end
	
		#
		# Define search
		#
		elsif searchterm [0 .. 6] == "define:" then
			# Parse differently
		
			if curline.index('<div class=s>') != nil then
				
				# Search for : Definitions of
				curline = curline[curline.index('<div class=s>') .. curline.length()]
				curline = curline[curline.index('<td>') + 4 .. curline.length()]
	
				definition = curline[0 .. curline.index('</td>') - 1]
	
				definition = removeLinks(definition);

				definition = replaceHtmlSymbols(definition);

				printf "[define] "
				printf "%s", definition
				puts " : " + index_li + " : " + index_br
				exit
	
			end
		#
		# Standard Search
		#
		#elsif curline.index('<h3 class=r>') != nil then
		elsif curline.index('<div id=ires>') != nil or curline.index('<div id="ires">') != nil then
			# Is this a youtube video/image link?
			if curline.index('Videos for') != nil and searchingVideos == true then
				# Video link : diff parsing
				# Chop everything before out
				curline = curline[curline.index('<div id=resultStats') .. curline.length()]

				# Chop off  till div
				curline = curline[curline.index('video_result') .. curline.length()]

				# Chop off til td
				curline = curline[curline.index('play_c.gif') .. curline.length()]

				# Now till <tr>
#				curline = curline[curline.index('<tr>') .. curline.length()]

				# Now <a href
				curline = curline[curline.index('<a href') .. curline.length()]

				# Quote to quote
				curline = curline[curline.index('"') + 1 .. curline.length()]
				url = curline[0 .. curline.index('"') - 1]

				# Now just fry the stupid url beginning
#				url = url[url.index('=')+1 .. url.length()]

				# And now description
				curline = curline[curline.index('>') .. curline.length()]
				curline = curline[0 .. curline.index('</a>')-1]

				curline = replaceHtmlSymbols(curline)

				# and puts
				puts "[video] " + url + " - " + curline
			# Is this an images link?
#			elsif curline.index('Image results for') != nil then
				# Different parsing
				# chop everything before out
#				curline = curline[curline.index('<div><') .. curline.length()]
	
				# Pull the next a-href
#				curline = curline[curline.index('<a href') .. curline.length()]
#				curline = curline[curline.index('"') + 1 .. curline.length()]
#				url = curline[0 .. curline.index('"') - 1]

				# Retranslate &amp
#				while url.index('&amp;') != nil
#					url = url.gsub('&amp;', '&')
#				end
#
#				puts "[image] Image results : " + url
			else
				# Chop everything before this out
				curline = curline[curline.index('<div><') .. curline.length()]
			
				# Now we chop off till <div
				if (curline.index("<li class=g") != nil)
					curline = curline[curline.index("<li class=g") .. curline.length()]
				else
					curline = curline[curline.index("<li class=\"g\"") .. curline.length()]
				end

				curline = curline[curline.index(">") .. curline.length()]

				curline = curline[curline.index("href") .. curline.length()]

				# Now chopoff the quotes - url is quote to quote
				curline = curline[curline.index('"') + 1 .. curline.length()]
	
				url = curline[0 .. curline.index('"') - 1]
	
				# Now chop off till the last >
				curline = curline[curline.index('>') + 1 .. curline.length()]
	
				# Description is till </a>
				description = curline[0 .. curline.index('</a>') - 1]
	
				# Cut off <em>
				while description.index('<em>') != nil
					description [description.index('<em>'), '<em>'.length()] = ''
				end

				# Cut off </em>
				while description.index('</em>') != nil
					description [description.index('</em>'), '</em>'.length()] = ''
				end

				description = replaceHtmlSymbols(description)
				url = replaceHtmlSymbols(url)

				puts description + " : " + url
				exit
			end
		end
	end
end

puts "None found"
