#pragma once
#ifndef SRC_UTIL_DLL_DECLSPEC_HPP_
#define SRC_UTIL_DLL_DECLSPEC_HPP_

#ifdef TEST

#define DLL

#else

#ifdef tes_money_EXPORTS
#define TES_MONEY_DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

#endif
#endif  // SRC_UTIL_DLL_DECLSPEC_HPP_
