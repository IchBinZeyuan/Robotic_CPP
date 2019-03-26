set(SRC_CPP
	testgui.cpp
	main.cpp
)

add_executable( testgui
	${SRC_CPP}
)

target_link_libraries( testgui
	Qt5::Widgets
	Qt5::Network
	referee
) 
