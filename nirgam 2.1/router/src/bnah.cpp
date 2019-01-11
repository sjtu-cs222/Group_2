
/*
 * XY_router.cpp
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 * Author: Lavina Jain
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file XY_router.cpp
/// \brief Implements XY routing algorithm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "bnah.h"
#include "../../config/extern.h"

////////////////////////////////////////////////
/// Method to set unique id
////////////////////////////////////////////////
void bnah_router::setID(UI id_tile)
{
    id = id_tile;
    initialize();
}

////////////////////////////////////////////////
/// Method that implements XY routing
/// inherited from base class router
/// Parameters:
/// - input direction from which flit entered the tile
/// - tileID of source tile
/// - tileID of destination tile
/// returns next hop direction
////////////////////////////////////////////////
UI bnah_router::calc_next(UI ip_dir, ULL source_id, ULL dest_id)
{
    int xco = id / num_cols;
    int yco = id % num_cols;
    int dest_xco = dest_id / num_cols;
    int dest_yco = dest_id % num_cols;
    int xdif = dest_xco-xco;
    int ydif = dest_yco-yco;
    if(xdif<0)xdif=-xdif;
    if(ydif<0)ydif=-ydif;
    if (xdif==0&&ydif==0){
	return C;
    }
	if(xdif>ydif){
		if(xco>dest_xco){
			return N; 
		}else{
			return S;
		}
	}else{
		if(yco>dest_yco){
			return W;
		}else{
			return E;
		}
	}
    return 0;
}

////////////////////////////////////////////////
/// Method containing any initializations
/// inherited from base class router
////////////////////////////////////////////////
// may be empty
// definition must be included even if empty, because this is a virtual function in base class
void bnah_router::initialize()
{

}

// for dynamic linking
extern "C"
{
    router *maker()
    {
        return new bnah_router;
    }
}
