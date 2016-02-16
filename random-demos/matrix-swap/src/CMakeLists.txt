set (SRCS
  matmul.c
)

add_library (lecture_matmul SHARED ${SRCS})

install (TARGETS lecture_matmul DESTINATION lib)
