# Executable
bin_PROGRAMS = boost_autoconf 

# Source files
boost_autoconf_SOURCES = main.cc

# Include files
AM_CPPFLAGS = -I$(srcdir)/include

# C++11 standard
#AM_CPPFLAGS += -std=c++11
AM_CPPFLAGS += -std=gnu++11

# boost
AM_CXXFLAGS = $(BOOST_CPPFLAGS)

# Warning and errors
AM_CPPFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual
AM_CPPFLAGS += -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations
AM_CPPFLAGS += -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual
AM_CPPFLAGS += -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel
AM_CPPFLAGS += -Wstrict-overflow=5 -Wswitch-default -Werror -Wno-unused
AM_CPPFLAGS += -Wuseless-cast
#-Wsign-conversion -Wold-style-cast -Wundef -Wzero-as-null-pointer-constant -Wctor-dtor-privacy
