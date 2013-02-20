/**
 * @file    error.h
 * @author  Andreas Halle <andern@gmail.com>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * This file is part of circ.
 *
 * circ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * circ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with circ.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * Contains error codes and error descriptions.
 */
#ifndef _CIRC_ERROR_H
#define _CIRC_ERROR_H

typedef enum err_code
{
    E_SUCCESS,
    E_NICK_MAXLEN,
    E_URESOLVED_HOSTNAME,
    E_OOM
} error_t;

static char success[]     = "";
static char nick_maxlen[] = "Nickname reached maximum length";
static char ures_host[]   = "Could not resolve hostname";
static char oom[]         = "Out of memory";

struct err_desc {
    error_t code;
    char* message;
} err_desc[] = {
    { E_SUCCESS, success },
    { E_NICK_MAXLEN, nick_maxlen},
    { E_URESOLVED_HOSTNAME, ures_host},
    { E_OOM, oom}
};

#endif
