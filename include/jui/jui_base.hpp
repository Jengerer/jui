#ifndef JUI_BASE_HPP
#define JUI_BASE_HPP

#if defined(JUI_DLL)
#if defined(JUI_EXPORT)
#define JUI_API __declspec(dllexport)
#else
#define JUI_API __declspec(dllimport)
#endif
#else
#define JUI_API
#endif

#endif // JUI_BASE_HPP