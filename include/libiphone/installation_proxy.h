/**
 * @file libiphone/installation_proxy.h
 * @brief Implementation to talk to the installation proxy on a device
 * \internal
 *
 * Copyright (c) 2009 Nikias Bassen All Rights Reserved.
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef INSTALLATION_PROXY_H
#define INSTALLATION_PROXY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libiphone/libiphone.h>

/* Error Codes */
#define INSTPROXY_E_SUCCESS                0
#define INSTPROXY_E_INVALID_ARG           -1
#define INSTPROXY_E_PLIST_ERROR           -2
#define INSTPROXY_E_CONN_FAILED           -3
#define INSTPROXY_E_OP_IN_PROGRESS        -4
#define INSTPROXY_E_OP_FAILED             -5

#define INSTPROXY_E_UNKNOWN_ERROR       -256

typedef int16_t instproxy_error_t;

typedef enum {
    INSTPROXY_APPTYPE_ALL = 0,
    INSTPROXY_APPTYPE_SYSTEM = 1,
    INSTPROXY_APPTYPE_USER = 2
} instproxy_apptype_t;

#define INSTPROXY_ARCHIVE_APP_ONLY (1 << 0)
#define INSTPROXY_ARCHIVE_SKIP_UNINSTALL (1 << 1)

struct instproxy_client_int;
typedef struct instproxy_client_int *instproxy_client_t;

typedef void (*instproxy_status_cb_t) (const char *operation, plist_t status);

/* Interface */
instproxy_error_t instproxy_client_new(iphone_device_t device, uint16_t port, instproxy_client_t *client);
instproxy_error_t instproxy_client_free(instproxy_client_t client);

instproxy_error_t instproxy_browse(instproxy_client_t client, instproxy_apptype_t apptype, plist_t *result);
instproxy_error_t instproxy_install(instproxy_client_t client, const char *pkg_path, plist_t sinf, plist_t metadata, instproxy_status_cb_t status_cb);
instproxy_error_t instproxy_upgrade(instproxy_client_t client, const char *pkg_path, plist_t sinf, plist_t metadata, instproxy_status_cb_t status_cb);
instproxy_error_t instproxy_uninstall(instproxy_client_t client, const char *appid, instproxy_status_cb_t status_cb);

instproxy_error_t instproxy_lookup_archives(instproxy_client_t client, plist_t *result);
instproxy_error_t instproxy_archive(instproxy_client_t client, const char *appid, uint32_t options, instproxy_status_cb_t status_cb);
instproxy_error_t instproxy_restore(instproxy_client_t client, const char *appid, instproxy_status_cb_t status_cb);
instproxy_error_t instproxy_remove_archive(instproxy_client_t client, const char *appid, instproxy_status_cb_t status_cb);

#ifdef __cplusplus
}
#endif

#endif
