set (SRCS
  matmul.cpp
)

add_library (lecture_matmul SHARED ${SRCS})

install (TARGETS lecture_matmul DESTINATION lib)
