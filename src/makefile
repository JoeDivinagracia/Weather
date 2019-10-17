weather: weather.cpp GUI.cpp
	g++ weather.cpp GUI.cpp -lcurl -o weather `pkg-config --cflags --libs gtkmm-3.0`

debug: weather.cpp GUI.cpp
	g++ -ggdb weather.cpp GUI.cpp -lcurl -o debug `pkg-config --cflags --libs gtkmm-3.0`
