file(REMOVE_RECURSE
  "CMakeFiles/YourProjectName_autogen"
  "YourProjectName_autogen/mocs_compilation.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/YourProjectName_autogen.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
