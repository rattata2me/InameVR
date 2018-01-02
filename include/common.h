#ifndef INAME_SRC_COMMON_H_

#define INAME_SRC_COMMON_H_

#define INAME_MAJOR_VERSION 0
#define INAME_MINOR_VERSION 1
#define INAME_PATCH_VERSION 12

#include <iostream>

const unsigned int INAME_VERSION_NUMBER = ((INAME_MAJOR_VERSION & 0xff) << 0xf) + ((INAME_MINOR_VERSION & 0xff) << 0x8) + (INAME_PATCH_VERSION & 0xff);


#endif