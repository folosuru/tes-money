#ifndef SRC_DLL_DECLSPEC_HPP
#define SRC_DLL_DECLSPEC_HPP

#ifdef TEST

#define DLL

#else

#ifdef tes_money_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

#endif
#endif  // SRC_DLL_DECLSPEC_HPP
