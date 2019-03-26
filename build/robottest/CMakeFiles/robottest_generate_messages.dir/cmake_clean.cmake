file(REMOVE_RECURSE
  "state_maschine_group3_automoc.cpp"
  "testconnect_automoc.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/robottest_generate_messages.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
