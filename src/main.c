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
        puts("Creating user");
        struct ci_user user = {"cbot", "cbot", "cbot", ""};

        puts("Creating connection");
        struct ci_connection con = {user, "195.159.0.90", 6667};

        puts("Connecting to server");
        ci_connect(&con);

        return (EXIT_SUCCESS);
}
