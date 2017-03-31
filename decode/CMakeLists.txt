set(DECODE_SOURCE
  chart.cc
  coverage.cc
  distortion.cc
  filter.cc
  future.cc
  hypothesis_builder.cc
  lexro.cc
  lm.cc
  output.cc
  objective.cc
  system.cc
  score_collector.cc
  stacks.cc
  vocab_map.cc
  weights.cc
  chart.hh
  coverage.hh
  distortion.hh
  feature.hh
  feature_init.hh
  filter.hh
  future.hh
  hypothesis.hh
  hypothesis_builder.hh
  id.hh
  lexro.hh
  lm.hh
  objective.hh
  output.hh
  passthrough.hh
  phrase_count_feature.hh
  pt_features.hh
  score_collector.hh
  source_phrase.hh
  stacks.hh
  system.hh
  types.hh
  vocab_map.hh
  weights.hh
  word_insert.hh
)

add_library(mtplz_decode ${DECODE_SOURCE})
target_link_libraries(mtplz_decode mtplz_search mtplz_pt kenlm kenlm_util ${Boost_LIBRARIES})
target_compile_features(mtplz_decode PUBLIC cxx_range_for)
target_include_directories(mtplz_decode PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>")

string(COMPARE EQUAL "${MTPLZ_DECODE_VALUE_COUNT}" "" is_empty)
if(NOT is_empty)
  target_compile_definitions(
      mtplz_decode PUBLIC "-DMTPLZ_DECODE_VALUE_COUNT=${MTPLZ_DECODE_VALUE_COUNT}"
  )
endif()

install(
    TARGETS mtplz_decode
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

set(DECODE_LIBS mtplz_decode mtplz_search mtplz_pt kenlm kenlm_util ${Boost_LIBRARIES})

AddExes(EXES decode LIBRARIES ${DECODE_LIBS})

if(BUILD_TESTING)
  AddTests(TESTS coverage_test chart_test lexro_test LIBRARIES ${DECODE_LIBS})
endif()
