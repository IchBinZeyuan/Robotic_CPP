file(REMOVE_RECURSE
  "state_maschine_group3_automoc.cpp"
  "testconnect_automoc.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/std_msgs_generate_messages_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()