#!/usr/bin/env ruby
#
# phenny.rb
# Will run/build phenny services
#
# Usuage : ./phenny.rb cachefile nick args
#

require 'cgi'
require 'uri'

if ARGV.length() < 3
	puts "Usuage : phenny.rb [cachefile] [nick] [service] [args]"
	exit
end

phenny_url = "http://code.google.com/p/phenny-ws/wiki/ServiceDefinitions"
phenny_url2 = "http://wiki.github.com/nslater/oblique/"
phenny_tmpfile = "/tmp/phenny-services.html"
phenny_tmpfile2 = "/tmp/phenny-services2.html"

cachefile = ARGV[0]
nick = ARGV[1]
service = ARGV[2]
args = ARGV[3 .. -1].join(" ")

args = URI.escape(args)

if service == "refresh"
	system "wget -q " + phenny_url + " -O " + phenny_tmpfile
	system "wget -q " + phenny_url2 + " -O " + phenny_tmpfile2

	# Parse services, put them in cache
	services = File.new(phenny_tmpfile, "r")
	services2 = File.new(phenny_tmpfile2, "r")
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

	num_of_services2 = 0

	services2.each {|line|
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

					num_of_services2 += 1
				end
			end
		}
	}

	# Done
	services.close
	services2.close
	cache.close

	puts "[" + nick + "] Cache refreshed : Found #{num_of_services} services from old, #{num_of_services2} from new"

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
		puts "[" + nick + "] Service not found. See " + phenny_url
		exit
	end

	service_url = service_url.sub("${args}", args)
	service_url = service_url.sub("${nick}", nick)

	# Now that we have the service, query it
	
	system "wget -q \'" + service_url + "\' -O " + phenny_tmpfile

	result = ""
	# Read the tmpfile into result
	cache = File.new(phenny_tmpfile, "r")
	cache.each {|line|
		# Add to result
		result += line.strip + " "
	}

	# Call the service
	puts "[" + nick + "] " + result
end


