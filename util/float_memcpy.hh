#ifndef MTPLZ_UTIL_FLOAT_MEMCPY_HH_
#define MTPLZ_UTIL_FLOAT_MEMCPY_HH_

namespace mtplz {
namespace util {

// This is a workaround for the EXC_ARM_DA_ALIGN error
// which occurs on both iOS and Android devices if
// architecture is ARMv7.
// * http://stackoverflow.com/questions/15925287/exc-arm-da-align-crash
// * http://www.splinter.com.au/what-do-do-with-excarmdaalign-on-an-iphone-ap
inline void float_memcpy(float& to, const float& from) {
#if defined(__ARM_ARCH_7A__)
  memcpy(&to, &from, sizeof(float));
#else
  to = from;
#endif
}

} // namespace util
} // namespace mtplz

#endif // MTPLZ_UTIL_FLOAT_MEMCPY_HH_
