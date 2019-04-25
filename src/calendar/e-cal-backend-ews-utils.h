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

#ifndef E_CAL_BACKEND_EWS_UTILS_H
#define E_CAL_BACKEND_EWS_UTILS_H

#include <libecal/libecal.h>

#include "server/e-ews-connection.h"
#include "server/e-ews-item-change.h"

#include "e-cal-backend-ews.h"

G_BEGIN_DECLS

#define MINUTES_IN_HOUR 60
#define SECS_IN_MINUTE 60

typedef struct {
	EEwsConnection *connection;
	ETimezoneCache *timezone_cache;
	ICalTimezone *default_zone;
	gchar *user_email;
	gchar *response_type; /* Accept */
	GSList *users;
	ECalComponent *comp;
	ECalComponent *old_comp;
	ICalComponent *icomp;
	ICalComponent *vcalendar; /* can be NULL, parent of icomp, where timezones can be eventually found */
	gchar *item_id;
	gchar *change_key;
	EEwsItemChangeType change_type;
	gint index;
	time_t start;
	time_t end;
} EwsCalendarConvertData;

const gchar *e_ews_collect_organizer (ICalComponent *comp);
void e_ews_collect_attendees (ICalComponent *comp, GSList **required, GSList **optional, GSList **resource, gboolean *out_rsvp_requested);

void ewscal_set_timezone (ESoapMessage *msg, const gchar *name, EEwsCalendarTimeZoneDefinition *tzd);
void ewscal_set_meeting_timezone (ESoapMessage *msg, ICalTimezone *icaltz);
void ewscal_set_reccurence (ESoapMessage *msg, ICalProperty *rrule, ICalTime *dtstart);
void ewscal_set_reccurence_exceptions (ESoapMessage *msg, ICalComponent *comp);
gchar *e_ews_extract_attachment_id_from_uri (const gchar *uri);
void ews_set_alarm (ESoapMessage *msg, ECalComponent *comp, ETimezoneCache *timezone_cache, ICalComponent *vcalendar, gboolean with_due_by);
gint ews_get_alarm (ECalComponent *comp);
void e_ews_clean_icomponent (ICalComponent *icomp);

const gchar *e_cal_backend_ews_tz_util_get_msdn_equivalent (const gchar *ical_tz_location);
const gchar *e_cal_backend_ews_tz_util_get_ical_equivalent (const gchar *msdn_tz_location);
void e_cal_backend_ews_populate_windows_zones (void);
void e_cal_backend_ews_unref_windows_zones (void);

gboolean e_cal_backend_ews_convert_calcomp_to_xml (ESoapMessage *msg, gpointer user_data, GError **error);
gboolean e_cal_backend_ews_convert_component_to_updatexml (ESoapMessage *msg, gpointer user_data, GError **error);
gboolean e_cal_backend_ews_clear_reminder_is_set (ESoapMessage *msg, gpointer user_data, GError **error);
gboolean e_cal_backend_ews_prepare_set_free_busy_status (ESoapMessage *msg,gpointer user_data, GError **error);
gboolean e_cal_backend_ews_prepare_accept_item_request (ESoapMessage *msg, gpointer user_data, GError **error);

guint e_cal_backend_ews_rid_to_index (ICalTimezone *timezone, const gchar *rid, ICalComponent *comp, GError **error);

ICalTime *	e_cal_backend_ews_get_datetime_with_zone	(ETimezoneCache *timezone_cache,
								 ICalComponent *vcalendar,
								 ICalComponent *comp,
								 ICalPropertyKind prop_kind,
								 ICalTime * (* get_func) (ICalProperty *prop));

G_END_DECLS

#endif
