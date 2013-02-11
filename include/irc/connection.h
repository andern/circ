/**
 * @file    connection.h
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
 * A connection contains all the necessary details needed to connect to and
 * authenticate with an IRC server.
 */
#ifndef _CIRC_CONNECTION_H
#define _CIRC_CONNECTION_H

#include "irc/user.h"

struct ci_connection {
        struct ci_user user;
        char *server;
        int port;
};

/**
 *
 * Connect to the server stored in the connection struct and authenticate using
 * the stored authentication details in the connection struct.
 */
void ci_connect(struct ci_connection *con);

#endif
