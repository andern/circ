/*
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
 */
#include <stdio.h>
#include <stdlib.h>

#include "irc/user.h"
#include "irc/connection.h"

int main(void)
{
        struct ci_user user;
        struct ci_connection con;

        char nick[] = "cbot";
        char ident[] = "cbot";
        char name[] = "cbot";
        char host[] = "";

        char servhost[] = "irc.homelien.no";

        user.nick = nick;
        user.ident = ident;
        user.name = name;
        user.host = host;

        puts("Creating connection");
        con.user = user;
        con.server.host = servhost;
        con.server.port = 6667;

        ci_connect(&con);

        return (EXIT_SUCCESS);
}
