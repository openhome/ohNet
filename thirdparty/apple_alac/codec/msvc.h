#ifndef MSVC_H
#define MSVC_H

/*
* CHANGELOG:
*
* 26-02-2016 Gregg Hamilton
* - #define inline __inline when MSVC detected.
*/

#if _MSC_VER
#define inline __inline
#endif

#endif
