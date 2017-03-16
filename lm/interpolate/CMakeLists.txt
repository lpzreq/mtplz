hunter_add_package(Eigen)
find_package(Eigen3 CONFIG REQUIRED)

set(KENLM_INTERPOLATE_SOURCE
    backoff_reunification.cc
    bounded_sequence_encoding.cc
    merge_probabilities.cc
    merge_vocab.cc
    normalize.cc
    pipeline.cc
    split_worker.cc
    tune_derivatives.cc
    tune_instances.cc
    tune_weights.cc
    universal_vocab.cc)

if(NOT IOS)
  find_package(OpenMP)
  if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  else()
    message(STATUS "OpenMP support would be nice for parallelizing matrix operations.")
  endif()
endif()

add_library(kenlm_interpolate ${KENLM_INTERPOLATE_SOURCE})
target_link_libraries(kenlm_interpolate PUBLIC Eigen3::Eigen Boost::boost)

set(KENLM_INTERPOLATE_EXES
    interpolate
    streaming_example)

if (NOT MSVC)
  set(THREADS pthread)
endif()

set(KENLM_INTERPOLATE_LIBS
    kenlm_interpolate kenlm kenlm_util Boost::boost ${THREADS})

AddExes(EXES ${KENLM_INTERPOLATE_EXES}
        LIBRARIES ${KENLM_INTERPOLATE_LIBS})

if(BUILD_TESTING)
    AddTests(TESTS backoff_reunification_test bounded_sequence_encoding_test normalize_test tune_derivatives_test
             LIBRARIES ${KENLM_INTERPOLATE_LIBS} pthread)

    # tune_instances_test needs an extra command line parameter
    KenLMAddTest(TEST tune_instances_test
                 LIBRARIES ${KENLM_INTERPOLATE_LIBS}
                 TEST_ARGS -- ${CMAKE_CURRENT_SOURCE_DIR}/../common/test_data/toy0.1)

    foreach(test_file test1 test2 test3 test_bad_order test_no_unk)
      set(KENLM_MERGE_TESTS_PATH ${KENLM_MERGE_TESTS_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/merge_test/${test_file})
    endforeach(test_file)

    KenLMAddTest(TEST merge_vocab_test
                 LIBRARIES ${KENLM_INTERPOLATE_LIBS}
                 TEST_ARGS ${KENLM_MERGE_TESTS_PATH})
endif()
