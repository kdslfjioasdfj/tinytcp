#ifndef TINYTCP_SHARED_H
#define TINYTCP_SHARED_H

#ifdef _WIN32
#ifdef TINYTCP_CONFIG_SHARED
#ifdef TINYTCP_CONFIG_BUILDING
#define TINYTCP_SHARED_API __declspec(dllexport)
#else
#define TINYTCP_SHARED_API __declspec(dllimport)
#endif // TINYTCP_CONFIG_BUILDING
#else
#define TINYTCP_SHARED_API // Not needed on Windows static builds (.lib)
#endif                     // TINYTCP_CONFIG_SHARED
#else
#define TINYTCP_SHARED_API // Not needed outside Windows
#endif                     // _WIN32

#ifdef _MSC_VER
#define restrict __restrict
#endif // _MSC_VER

#endif // TINYTCP_SHARED_H
