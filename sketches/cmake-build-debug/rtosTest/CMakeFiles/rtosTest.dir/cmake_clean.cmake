file(REMOVE_RECURSE
  "rtosTest.pdb"
  "rtosTest"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/rtosTest.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
