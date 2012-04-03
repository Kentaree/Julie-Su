#!/usr/bin/env ruby
#
# meme.rb
# Web crawler for teh memes
#
# Usage : urm....
#

require 'cgi'
require 'uri'

if ARGV.length() < 2
	puts "Usage : meme.rb [cachefile] [service]"
	exit
end

meme_url = "https://github.com/Kentaree/Julie-Su/wiki/MemeDefinitions"
meme_tmpfile = "/tmp/meme_urls.html"

cachefile = ARGV[0]
service = ARGV[1]

if service == "refresh"
	system "wget -q " + meme_url + " -O " + meme_tmpfile

	# Parse services, put them in cache
	services = File.new(meme_tmpfile, "r")
	cache = File.new(cachefile, "w")

	result = {}

	r_item = Regexp.compile('(?i)<li>(.*?)</li>')
	r_tag = Regexp.compile('<[^>]+>')

	num_of_services = 0

	services.each {|line|
		line.scan(r_item) {|item|
			item = item.to_s
			item = item.sub(r_tag, '').strip();
			if item.index(' ') != nil
				command, template = item.split(' ', 2)

				if template != nil and template[0..6] == "http://"
					template = template.gsub('</a>', '')
					template = template.gsub('&amp;', '&')

					# write to cache
					cache.puts(command)
					cache.puts(template)

					num_of_services += 1
				end
			end
		}
	}

	# Done
	services.close
	cache.close

	puts "Cache refreshed : Found #{num_of_services} memes"
	exit
else
	# Read the cache
	service_url = ""

	next_is_right = false

	# Find the service
	cache = File.new(cachefile, "r")
	cache.each {|line|
		# If the last line was right, pull the url
		if next_is_right == true
			next_is_right = false
			service_url = line.strip
		end

		# If we havent found a service, and line is the service : next is right
		if line.strip == service.strip
			next_is_right = true
		end
	}

	cache.close()

	if service_url == ""
		puts "Not found, check https://github.com/Kentaree/Julie-Su/wiki/MemeDefinitions for options"
		exit
	end

	result = service_url

	# Call the service
	puts result
end


