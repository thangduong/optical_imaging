
//#define DBG_HOSTACQ

#ifdef DBG_HOSTACQ 

int IfxDbgPrint(const char * format, ...);
void IfxDbgFlush(void);

#define DBG_PRINT(arg) IfxDbgPrint arg
#define DBG_FLUSH IfxDbgFlush();



#else
#define DBG_PRINT(arg)
#define DBG_FLUSH 
#endif
