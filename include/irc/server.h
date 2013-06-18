/**
 * @file    server.h
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
 * A server contains various settings that are important for a client to know
 * in order to behave properly.
 */
#ifndef _CIRC_SERVER_H
#define _CIRC_SERVER_H

struct ci_server {
        char* host;
        char* ip;
        int port;

        /*
         * IRC server settings. Taken from here:
         * http://www.irc.org/tech_docs/005.html
         */
        /* The supported channel prefixes. */
        char* chantypes;

        /*
         * This is a list of channel modes according to 4 types.
         * A = Mode that adds or removes a nick or address to a list. Always has
         *     a parameter.
         * B = Mode that changes a setting and always has a parameter.
         * C = Mode that changes a setting and only has a parameter when set.
         * D = Mode that changes a setting and never has a parameter.
         *
         * Note: Modes of type A return the list when there is no parameter
         *       present.
         * Note: Some clients assumes that any mode not listed is of type D.
         * Note: Modes in PREFIX are not listed but could be considered type B.
         */
        char* chanmodes;

        /* The IRC network name. */
        char* network;

        /* Maximum number of channels allowed to join by channel prefix. */
        int chanlimit;

        /* Maximum channel name length. */
        int channellen;

        /* Maximum nickname length. */
        int nicklen;

        /* Maximum topic length. */
        int topiclen;
};

#endif
