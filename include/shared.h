#ifndef TINYTCP_SHARED_H
#define TINYTCP_SHARED_H

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef TINYTCP_CONFIG_BUILDING
#define TINYTCP_SHARED_API __declspec(dllexport)
#else
#define TINYTCP_SHARED_API __declspec(dllimport)
#endif // TINYTCP_CONFIG_BUILDING
#else
#define TINYTCP_SHARED_API // Not needed on POSIX
#endif // _WIN32

#ifdef _MSC_VER
#define restrict __restrict
#endif // _MSC_VER

#endif // TINYTCP_SHARED_H
