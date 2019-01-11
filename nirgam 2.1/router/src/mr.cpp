
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

#include "nah.h"
#include "../../config/extern.h"
#include "../../core/NoC.h"
#include "../../core/NWTile.h"

////////////////////////////////////////////////
/// Method to set unique id
////////////////////////////////////////////////
void nah_router::setID(UI id_tile)
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
UI nah_router::calc_next(UI ip_dir, ULL source_id, ULL dest_id)
{
    int xco = id / num_cols;
    int yco = id % num_cols;
    int dest_xco = dest_id / num_cols;
    int dest_yco = dest_id % num_cols;
    int xdif = dest_xco-xco;
    int ydif = dest_yco-yco;
    if (xdif==0 && ydif==0){
	return C;
    }
    int mesh[num_rows][num_cols];
    int i,j;
    for (i=0;i<num_cols;i++){
        for (j=0;j<num_rows;j++){
            if (i==dest_xco && j==dest_yco) mesh[i][j]=0;
            else mesh[i][j]=-1;
        }
    }
    int flag=1;
    while (flag){
        flag=0;
        for (i=0;i<num_cols;i++){
            for (j=0;j<num_rows;j++){
                int minf=-1;
                int tmp=thisnoc->nwtile[i][j]->return_total_flits();
		if (i>0){
                    if (mesh[i-1][j]!=-1){
                        if (minf==-1 || mesh[i-1][j]<minf) minf=mesh[i-1][j];
                    } 
                }
		if (i<num_rows-1){
                    if (mesh[i+1][j]!=-1){
                        if (minf==-1 || mesh[i+1][j]<minf) minf=mesh[i+1][j];
                    } 
                }
		if (j>0){
                    if (mesh[i][j-1]!=-1){
                        if (minf==-1 || mesh[i][j-1]<minf) minf=mesh[i][j-1];
                    } 
                }
		if (j<num_cols-1){
                    if (mesh[i][j+1]!=-1){
                        if (minf==-1 || mesh[i][j+1]<minf) minf=mesh[i][j+1];
                    } 
                }
                if (minf==-1) continue;
                if (mesh[i][j]==-1 || mesh[i][j]>minf+tmp){
                    mesh[i][j]=tmp+minf;
                    flag=1;
                }
            }
        }
    }
    int next;
    int minx=-1;
    if (xco>0){
        if (minx==-1 || mesh[xco-1][yco]<minx){
            minx=mesh[xco-1][yco];
            next=W;
        }
    }
    if (xco<num_rows-1){
        if (minx==-1 || mesh[xco+1][yco]<minx){
            minx=mesh[xco+1][yco];
            next=E;
        }
    }
    if (yco>0){
        if (minx==-1 || mesh[xco][yco-1]<minx){
            minx=mesh[xco][yco-1];
            next=N;
        }
    }
    if (xco<num_cols-1){
        if (minx==-1 || mesh[xco][yco+1]<minx){
            minx=mesh[xco][yco+1];
            next=S;
        }
    }
    return next;
}

////////////////////////////////////////////////
/// Method containing any initializations
/// inherited from base class router
////////////////////////////////////////////////
// may be empty
// definition must be included even if empty, because this is a virtual function in base class
void nah_router::initialize()
{

}

// for dynamic linking
extern "C"
{
    router *maker()
    {
        return new nah_router;
    }
}
