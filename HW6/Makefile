CXX         = g++
CXXFLAGS    = -Wall -Wextra -g -L.
LDFLAGS     = -fPIC -shared

APP_SOURCES = main.cpp
LIB_SOURCES = string.cpp field.cpp port.cpp ip.cpp
LIB_OTHER   = input

DEST_APP    = firewall.exe
DEST_LIB    = firewall

all: ${DEST_APP}

${DEST_LIB}:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIB_SOURCES) -o lib$(DEST_LIB).so

${DEST_APP}:
 	$(CXX) $(CXXFLAGS) $(APP_SOURCES) -o $(DEST_APP) -l$(DEST_LIB) -l$(input)
 	
clean:
	rm -f $(DEST_APP) $(DEST_LIB)
