#pragma once

/*
	Propuesta de macro para no tener que escribir declspec
	y que funcione el mismo include del motor tanto en Linux
	como en Windows
*/

#if defined(_MSC_VER)
		//  Microsoft 
		#define EXPORT __declspec(dllexport)
		#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
		//  GCC
		#define EXPORT __attribute__((visibility("default")))
		#define IMPORT
#else
		//  do nothing and hope for the best?
		#define EXPORT
		#define IMPORT
		#pragma warning Unknown dynamic link import/export semantics.
#endif

//Define PTSD_COMPILING if you are compiling a PTSD module. Ex PTSD-Input, PTSD-Render...
//Add PTSD_API to any API function/class. Ex:
//namespace PTSD {
// 	PTSD_API void test();
//}

#if PTSD_COMPILING
		#define PTSD_API EXPORT
#else
		#define PTSD_API IMPORT
#endif

namespace PTSD {
	PTSD_API void test();
}