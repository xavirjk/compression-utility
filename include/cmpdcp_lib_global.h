#ifdef CMPDCPLIB_EXPORT
#define HCAPI __declspec(dllexport)
#else
#define HCAPI __declspec(dllimport)
#endif
