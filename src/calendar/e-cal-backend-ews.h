/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *
 * Copyright (C) 1999-2008 Novell, Inc. (www.novell.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 */

#ifndef E_CAL_BACKEND_EWS_H
#define E_CAL_BACKEND_EWS_H

#include <libedata-cal/e-cal-backend-sync.h>
#include <e-ews-connection.h>

G_BEGIN_DECLS

#define E_TYPE_CAL_BACKEND_EWS            (e_cal_backend_ews_get_type ())
#define E_CAL_BACKEND_EWS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), E_TYPE_CAL_BACKEND_EWS,	ECalBackendEws))
#define E_CAL_BACKEND_EWS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), E_TYPE_CAL_BACKEND_EWS,	ECalBackendEwsClass))
#define E_IS_CAL_BACKEND_EWS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), E_TYPE_CAL_BACKEND_EWS))
#define E_IS_CAL_BACKEND_EWS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), E_TYPE_CAL_BACKEND_EWS))

typedef struct _ECalBackendEws        ECalBackendEws;
typedef struct _ECalBackendEwsClass   ECalBackendEwsClass;

typedef struct _ECalBackendEwsPrivate ECalBackendEwsPrivate;

struct _ECalBackendEws {
	ECalBackendSync backend;

	/* Private data */
	ECalBackendEwsPrivate *priv;
};

struct _ECalBackendEwsClass {
	ECalBackendSyncClass parent_class;
};

typedef struct {
	ECalBackendEws *cbews;
	EEwsSendOptions *opts;
} EwsSettings;

GType   e_cal_backend_ews_get_type (void);
EEwsConnection* e_cal_backend_ews_get_connection (ECalBackendEws *cbews);
GHashTable* e_cal_backend_ews_get_categories_by_id (ECalBackendEws *cbews);
GHashTable* e_cal_backend_ews_get_categories_by_name (ECalBackendEws *cbews);
icaltimezone* e_cal_backend_ews_get_default_zone (ECalBackendEws *cbews);
void    e_cal_backend_ews_notify_error_code (ECalBackendEws *cbews, EEwsConnectionStatus status);
const gchar *e_cal_backend_ews_get_container_id (ECalBackendEws *cbews);
const gchar * e_cal_backend_ews_get_local_attachments_store (ECalBackendEws *cbews);
void e_cal_backend_ews_priv_lock (ECalBackendEws *cbews);
void e_cal_backend_ews_priv_unlock (ECalBackendEws *cbews);

G_END_DECLS

#endif
