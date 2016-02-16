set (SRCS
  lecture.c
)

add_library (lecture SHARED ${SRCS})

install (TARGETS lecture DESTINATION lib)
