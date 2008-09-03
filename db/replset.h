/**
*    Copyright (C) 2008 10gen Inc.
*  
*    This program is free software: you can redistribute it and/or  modify
*    it under the terms of the GNU Affero General Public License, version 3,
*    as published by the Free Software Foundation.
*  
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*  
*    You should have received a copy of the GNU Affero General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* ReplSet is a pair of db servers replicating to one another and cooperating.

   Only one member of the pair is active at a time; so this is a smart master/slave
   configuration basically.

   You may read from the slave at anytime though (if you don't mind the slight lag).

   todo: Could be extended to be more than a pair, thus the name 'Set' -- for example, 
   a set of 3...
*/

class ReplSet { 

public:
	int remotePort;
	string remoteHost;

	ReplSet(const char *remoteEnd);

};

ReplSet::ReplSet(const char *remoteEnd) {
	remotePort = DBPort;
	remoteHost = remoteEnd;
	const char *p = strchr(remoteEnd, ':');
	if( p ) { 
		remoteHost = string(remoteEnd, p-remoteEnd);
		remotePort = atoi(p+1);
		uassert("bad port #", remotePort > 0 && remotePort < 0x10000 );
	}
}
