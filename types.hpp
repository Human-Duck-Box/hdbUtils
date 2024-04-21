#ifndef HDB_TYPES_HPP
#define HDB_TYPES_HPP

#include <cstdint>

#define defInt(size) typedef int##size##_t int##size; typedef uint##size##_t uint##size

namespace hdb {

typedef int8_t byte;
typedef uint8_t ubyte;
typedef int16_t word;
typedef uint16_t uword;
typedef int32_t dword;
typedef uint32_t udword;
typedef int64_t qword;
typedef uint64_t uqword;

defInt(8);
defInt(16);
defInt(32);
defInt(64);

}

#endif
