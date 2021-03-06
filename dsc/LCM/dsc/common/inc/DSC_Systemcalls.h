/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
 */

/*============================================================================
 * NOTE: This file must be includable from within C files.  
 * Only put C++ stuff in a '#fidef __cplusplus' wrapper.
 *============================================================================
 */
#ifndef _DSC_SYSTEMCALLS_H
#define _DSC_SYSTEMCALLS_H
#include <nits.h>
#include <MI.h>
#include <micodec.h>
#include <pal/memory.h>
#include <pal/alloc.h>
#include "MSFT_DSCMetaConfiguration.h"

#ifdef __cplusplus
extern "C" {
#endif


static __inline void *DSC_malloc(size_t length, NitsCallSite callSite)
{
    
    void *memoryVar = PAL_MallocCallsite(callSite, length);
    if( memoryVar) 
        memset(memoryVar, 0, length);
    
    return memoryVar;
}

#if defined(_MSC_VER)
static __inline HANDLE DSC_CreateFile(_In_      LPCTSTR lpFileName,
                                      _In_      DWORD dwDesiredAccess,
                                      _In_      DWORD dwShareMode,
                                      _In_opt_  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                      _In_      DWORD dwCreationDisposition,
                                      _In_      DWORD dwFlagsAndAttributes,
                                      _In_opt_  HANDLE hTemplateFile,
                                      NitsCallSite callSite)
{
    if (NitsShouldFault(callSite, NitsAutomatic))
    {
        NitsTrace(L"DSC_CreateFile faulted");
        SetLastError(ERROR_FILE_NOT_FOUND);
        return INVALID_HANDLE_VALUE;
    }
    return CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                        dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

static __inline DWORD DSC_GetFileSize(_In_       HANDLE hFile,
                                      _Out_opt_  LPDWORD lpFileSizeHigh,
                                      NitsCallSite callSite)
{
    if (NitsShouldFault(callSite, NitsAutomatic))
    {
        if(lpFileSizeHigh != NULL)
        {
            *lpFileSizeHigh = 0;
        }
        return INVALID_FILE_SIZE;
    }
    return GetFileSize(hFile, lpFileSizeHigh);
}

#endif

static __inline MI_Result DSC_MI_Class_GetElementCount(
        _In_  const MI_Class* self,
        _Out_ MI_Uint32* count)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Class_GetElementCount(self, count);     
}

static __inline MI_Result MI_CALL DSC_MI_Instance_GetClassName(
    _In_ const MI_Instance* self, 
    _Outptr_result_maybenull_z_ const MI_Char** className)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Instance_GetClassName(self, className);       
}
static __inline MI_Result DSC_MI_QualifierSet_GetQualifier(
    _In_ const MI_QualifierSet *self,
    _In_z_ const MI_Char *name,
    _Out_ MI_Type *qualifierType,
    _Out_ MI_Uint32 *qualifierFlags,    /* scope information */
    _Out_ MI_Value *qualifierValue,
    _Out_ MI_Uint32 *index)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_QualifierSet_GetQualifier(self, name, qualifierType, qualifierFlags, qualifierValue , index);       
}
static __inline MI_Result DSC_MI_Class_GetElement(
        _In_      const MI_Class* self, 
        _In_z_    const MI_Char* name,
        _Out_opt_ MI_Value* value,
        _Out_opt_ MI_Boolean* valueExists,
        _Out_opt_ MI_Type* type,
        _Outptr_opt_result_maybenull_z_ MI_Char **referenceClass,
        _Out_opt_ MI_QualifierSet *qualifierSet,
        _Out_opt_ MI_Uint32* flags,
        _Out_opt_ MI_Uint32* index)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Class_GetElement(self, name, value, valueExists, type, referenceClass, qualifierSet, flags , index);     
}
static __inline  MI_Result  DSC_MI_Instance_AddElement(
    _Inout_ MI_Instance* self,
    _In_z_ const MI_Char* name,
    _In_opt_ const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Instance_AddElement(self, name, value, type, flags);       
}
static __inline  MI_Result DSC_MI_Application_NewInstance(
    _In_     MI_Application *application,
    _In_z_ const MI_Char *className,
    _In_opt_ const MI_ClassDecl *classRTTI,
    _Outptr_    MI_Instance **instance)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Application_NewInstance(application, className, classRTTI, instance);    
}

static __inline MI_Result  DSC_MI_Instance_Clone(
    _In_ const MI_Instance* self,
    _Outptr_ MI_Instance** newInstance)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Instance_Clone(self, newInstance);
}
static __inline  MI_Result  DSC_MI_Instance_GetElement(
    _In_ const MI_Instance* self, 
    _In_z_ const MI_Char* name,
    _Out_opt_ MI_Value* value,
    _Out_opt_ MI_Type* type,
    _Out_opt_ MI_Uint32* flags,
    _Out_opt_ MI_Uint32* index)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Instance_GetElement(self, name, value, type, flags,index);        
}

static __inline  MI_Result  DSC_MSFT_DSCMetaConfiguration_Clone(
    _In_ const MSFT_DSCMetaConfiguration* self,
    _Outptr_ MSFT_DSCMetaConfiguration** newInstance)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MSFT_DSCMetaConfiguration_Clone(self, newInstance);        
}


static __inline  MI_Result DSC_MI_Application_NewSession(
    _In_     MI_Application *application, 
    _In_opt_z_ const MI_Char *protocol,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_ MI_DestinationOptions *options,
    _In_opt_ MI_SessionCallbacks *callbacks,
    _Outptr_result_maybenull_ MI_Instance **extendedError,
    _Out_    MI_Session *session)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Application_NewSession(application, protocol, destination, options, callbacks,extendedError, session );      
    
}
static __inline MI_Result DSC_MI_Application_NewOperationOptions(
        _In_  MI_Application *application,
          MI_Boolean mustUnderstand,
    _Out_ MI_OperationOptions *options)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Application_NewOperationOptions(application, mustUnderstand, options);    
}

static __inline MI_Result DSC_MI_OperationOptions_SetString(
    _Inout_   MI_OperationOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_z_ const MI_Char *value,
    MI_Uint32 flags)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_OperationOptions_SetString(options, optionName, value, flags);       
}

static __inline MI_Result  DSC_MI_Application_NewDeserializer_Mof(
        _Inout_ MI_Application *application, 
        MI_Uint32 flags,
        _In_z_ MI_Char *format, 
        _Out_ MI_Deserializer *deserializer)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Application_NewDeserializer_Mof(application, flags, format, deserializer);      
}

static __inline MI_Result DSC_MI_Application_Initialize(
                                    MI_Uint32 flags,
                                    _In_opt_z_ const MI_Char *applicationID,
                                    _Outptr_result_maybenull_ MI_Instance **extendedError,
                                    _Out_    MI_Application *application)
{
    if (NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    return MI_Application_Initialize(flags, applicationID, extendedError, application);
}


static __inline void *DSC_realloc(_In_ void *originalBuffer, size_t length, NitsCallSite callSite)
{
    if (originalBuffer == NULL)
    {
        return DSC_malloc(length, callSite);
    }
    
    return PAL_ReallocCallsite(callSite, originalBuffer, length);
}


static __inline void DSC_free(void *buffer)
{
    PAL_Free(buffer);
}


#ifdef __cplusplus
} // end of extern C 
#endif   // __cplusplus

#endif //_DSC_SYSTEMCALLS_H
