cc_library(
  infermeta
  SRCS nullary.cc unary.cc binary.cc ternary.cc multiary.cc fusion.cc
  DEPS convert_utils meta_tensor infermeta_utils xxhash)
cc_library(
  backward_infermeta
  SRCS backward.cc
  DEPS meta_tensor convert_utils)
add_subdirectory(strings)
add_subdirectory(sparse)
