#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_UTIL_DLL_DECLSPEC_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_UTIL_DLL_DECLSPEC_HPP_

#ifdef TEST
#define TES_DLL
#else

#ifdef tes_EXPORTS
#define TES_DLL __declspec(dllexport)
#else
#define TES_DLL __declspec(dllimport)
#endif

#endif

#endif  // TES_COUNTRY_HEADER_COUNTRY_UTIL_DLL_DECLSPEC_HPP_
