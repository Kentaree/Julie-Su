#
# plugins/quote
# Quote plugin
#

project (quote)

	set (quote_SOURCES ${quote_SOURCE_DIR}/quote.cpp)
	set (quote_INCLUDES ${quote_SOURCE_DIR}/quote.h)

	add_library(quote MODULE ${quote_SOURCES} ${quote_INCLUDES})
	set_target_properties (quote PROPERTIES PREFIX "")

