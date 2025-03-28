/*
 * libvirt-common.h
 * Summary: common macros and enums for the libvirt and libvirt-admin library
 * Description: Provides common macros and enums needed by both libvirt and
 *              libvirt-admin libraries
 *
 * Copyright (C) 2015 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#if !defined __VIR_LIBVIRT_H_INCLUDES__ && !defined __VIR_ADMIN_H_INCLUDES__
# error "Don't include this file directly"
#endif

#ifndef __VIR_VIRCOMMON_H__
# define __VIR_VIRCOMMON_H__

# include <sys/types.h>

# ifdef __cplusplus
extern "C" {
# endif

# ifndef VIR_DEPRECATED
  /* The feature is present in gcc-3.1 and newer.  */
#  if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#   define VIR_DEPRECATED __attribute__((__deprecated__))
#  else
#   define VIR_DEPRECATED /* nothing */
#  endif
# endif /* VIR_DEPRECATED */

# ifdef WIN32
#  ifdef LIBVIRT_STATIC
#   define VIR_EXPORT_VAR extern
#  else
#   ifdef IN_LIBVIRT
#    define VIR_EXPORT_VAR __declspec(dllexport) extern
#   else
#    define VIR_EXPORT_VAR __declspec(dllimport) extern
#   endif
#  endif
# else
#  define VIR_EXPORT_VAR extern
# endif

/* General note - in the header files, any linear enumeration which
 * might be expanded in the future has an optional *_LAST value that
 * gives the size of the enum at the time of compilation, if the user
 * defines VIR_ENUM_SENTINELS.  Enumerations for bit values do not
 * have a *_LAST value, but additional bits may be defined.  */

/* library versioning */

/**
 * LIBVIR_VERSION_NUMBER:
 *
 * Macro providing the version of the library as
 * version * 1,000,000 + minor * 1000 + micro
 *
 * Since: 0.0.1
 */
# define LIBVIR_VERSION_NUMBER 11001000

/**
 * LIBVIR_CHECK_VERSION:
 * @major: major component of the version number
 * @minor: minor component of the version number
 * @micro: micro component of the version number
 *
 * Macro for developers to easily check what version of the library
 * their code is compiling against.
 * e.g.
 *   #if LIBVIR_CHECK_VERSION(1,1,3)
 *     // some code that only works in 1.1.3 and newer
 *   #endif
 *
 * Since: 1.2.0
 */
# define LIBVIR_CHECK_VERSION(major, minor, micro) \
    ((major) * 1000000 + (minor) * 1000 + (micro) <= LIBVIR_VERSION_NUMBER)

/*
 * virFreeCallback:
 * @opaque: opaque user data provided at registration
 *
 * Type for a callback cleanup function to be paired with a callback.  This
 * function will be called as a final chance to clean up the @opaque
 * registered with the primary callback, at the time when the primary
 * callback is deregistered.
 *
 * It is forbidden to call any other libvirt APIs from an
 * implementation of this callback, since it can be invoked
 * from a context which is not re-entrant safe. Failure to
 * abide by this requirement may lead to application deadlocks
 * or crashes.
 *
 * Since: 0.5.0
 */
typedef void (*virFreeCallback)(void *opaque);

/**
 * virConnectCloseReason:
 *
 * Since: 0.10.0
 */
typedef enum {
    VIR_CONNECT_CLOSE_REASON_ERROR     = 0, /* Misc I/O error (Since: 0.10.0) */
    VIR_CONNECT_CLOSE_REASON_EOF       = 1, /* End-of-file from server (Since: 0.10.0) */
    VIR_CONNECT_CLOSE_REASON_KEEPALIVE = 2, /* Keepalive timer triggered (Since: 0.10.0) */
    VIR_CONNECT_CLOSE_REASON_CLIENT    = 3, /* Client requested it (Since: 0.10.0) */

# ifdef VIR_ENUM_SENTINELS
    VIR_CONNECT_CLOSE_REASON_LAST /* (Since: 0.10.0) */
# endif
} virConnectCloseReason;

/**
 * virTypedParameterType:
 *
 * Express the type of a virTypedParameter
 *
 * Since: 0.9.2
 */
typedef enum {
    VIR_TYPED_PARAM_INT     = 1, /* integer case (Since: 0.9.2) */
    VIR_TYPED_PARAM_UINT    = 2, /* unsigned integer case (Since: 0.9.2) */
    VIR_TYPED_PARAM_LLONG   = 3, /* long long case (Since: 0.9.2) */
    VIR_TYPED_PARAM_ULLONG  = 4, /* unsigned long long case (Since: 0.9.2) */
    VIR_TYPED_PARAM_DOUBLE  = 5, /* double case (Since: 0.9.2) */
    VIR_TYPED_PARAM_BOOLEAN = 6, /* boolean(character) case (Since: 0.9.2) */
    VIR_TYPED_PARAM_STRING  = 7, /* string case (Since: 0.9.8) */

# ifdef VIR_ENUM_SENTINELS
    VIR_TYPED_PARAM_LAST /* (Since: 0.9.10) */
# endif
} virTypedParameterType;

/**
 * virTypedParameterFlags:
 *
 * Flags related to libvirt APIs that use virTypedParameter.
 *
 * These enums should not conflict with those of virDomainModificationImpact.
 *
 * Since: 0.9.8
 */
typedef enum {
    /* 1 << 0 is reserved for virDomainModificationImpact */
    /* 1 << 1 is reserved for virDomainModificationImpact */

    /* Older servers lacked the ability to handle string typed
     * parameters.  Attempts to set a string parameter with an older
     * server will fail at the client, but attempts to retrieve
     * parameters must not return strings from a new server to an
     * older client, so this flag exists to identify newer clients to
     * newer servers.  This flag is automatically set when needed, so
     * the user does not have to worry about it; however, manually
     * setting the flag can be used to reject servers that cannot
     * return typed strings, even if no strings would be returned.
     *
     * Since: 0.9.8
     */
    VIR_TYPED_PARAM_STRING_OKAY = 1 << 2,

} virTypedParameterFlags;

/**
 * VIR_TYPED_PARAM_FIELD_LENGTH:
 *
 * Macro providing the field length of virTypedParameter name
 *
 * Since: 0.9.2
 */
# define VIR_TYPED_PARAM_FIELD_LENGTH 80

/**
 * virTypedParameter:
 *
 * A named parameter, including a type and value.
 *
 * The types virSchedParameter, virBlkioParameter, and
 * virMemoryParameter are aliases of this type, for use when
 * targeting libvirt earlier than 0.9.2.
 *
 * Since: 0.9.2
 */
typedef struct _virTypedParameter virTypedParameter;

struct _virTypedParameter {
    char field[VIR_TYPED_PARAM_FIELD_LENGTH];  /* parameter name */
    int type;   /* parameter type, virTypedParameterType */
    union {
        int i;                      /* type is INT */
        unsigned int ui;            /* type is UINT */
        long long int l;            /* type is LLONG */
        unsigned long long int ul;  /* type is ULLONG */
        double d;                   /* type is DOUBLE */
        char b;                     /* type is BOOLEAN */
        char *s;                    /* type is STRING, may not be NULL */
    } value; /* parameter value */
};

/**
 * virTypedParameterPtr:
 *
 * a pointer to a virTypedParameter structure.
 *
 * Since: 0.9.2
 */
typedef virTypedParameter *virTypedParameterPtr;

virTypedParameterPtr virTypedParamsGet(virTypedParameterPtr params,
                                       int nparams,
                                       const char *name);
int virTypedParamsGetInt(virTypedParameterPtr params,
                         int nparams,
                         const char *name,
                         int *value);
int virTypedParamsGetUInt(virTypedParameterPtr params,
                          int nparams,
                          const char *name,
                          unsigned int *value);
int virTypedParamsGetLLong(virTypedParameterPtr params,
                           int nparams,
                           const char *name,
                           long long *value);
int virTypedParamsGetULLong(virTypedParameterPtr params,
                            int nparams,
                            const char *name,
                            unsigned long long *value);
int virTypedParamsGetDouble(virTypedParameterPtr params,
                            int nparams,
                            const char *name,
                            double *value);
int virTypedParamsGetBoolean(virTypedParameterPtr params,
                             int nparams,
                             const char *name,
                             int *value);
int virTypedParamsGetString(virTypedParameterPtr params,
                            int nparams,
                            const char *name,
                            const char **value);

int virTypedParamsAddInt(virTypedParameterPtr *params,
                         int *nparams,
                         int *maxparams,
                         const char *name,
                         int value);
int virTypedParamsAddUInt(virTypedParameterPtr *params,
                          int *nparams,
                          int *maxparams,
                          const char *name,
                          unsigned int value);
int virTypedParamsAddLLong(virTypedParameterPtr *params,
                           int *nparams,
                           int *maxparams,
                           const char *name,
                           long long value);
int virTypedParamsAddULLong(virTypedParameterPtr *params,
                            int *nparams,
                            int *maxparams,
                            const char *name,
                            unsigned long long value);
int virTypedParamsAddDouble(virTypedParameterPtr *params,
                            int *nparams,
                            int *maxparams,
                            const char *name,
                            double value);
int virTypedParamsAddBoolean(virTypedParameterPtr *params,
                             int *nparams,
                             int *maxparams,
                             const char *name,
                             int value);
int virTypedParamsAddString(virTypedParameterPtr *params,
                            int *nparams,
                            int *maxparams,
                            const char *name,
                            const char *value);
int virTypedParamsAddStringList(virTypedParameterPtr *params,
                                int *nparams,
                                int *maxparams,
                                const char *name,
                                const char **values);
int virTypedParamsAddFromString(virTypedParameterPtr *params,
                                int *nparams,
                                int *maxparams,
                                const char *name,
                                int type,
                                const char *value);

void virTypedParamsClear(virTypedParameterPtr params,
                         int nparams);
void virTypedParamsFree(virTypedParameterPtr params,
                        int nparams);

# ifdef __cplusplus
}
# endif

#endif /* __VIR_VIRCOMMON_H__ */
