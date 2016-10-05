//
//	HeadMovementModule.cc		This file is a part of the IKAROS project
//
//    Copyright (C) 2012 <Author Name>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//    See http://www.ikaros-project.org/ for more information.
//
//  This example is intended as a starting point for writing new Ikaros modules
//  The example includes most of the calls that you may want to use in a module.
//  If you prefer to start with a clean example, use he module MinimalModule instead.
//

#include "HeadMovementModule.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;

void
HeadMovementModule::SetSizes() // Infer output size from data if none is given
{
    if(GetValue("outputsize"))
    {
        Module::SetSizes();
        return;
    }
    
    if(GetValue("outputsize_x"))
    {
        Module::SetSizes();
        return;
    }
    
    if(GetValue("outputsize_y"))
    {
        Module::SetSizes();
        return;
    }
    
    int sx, sy;
    float ** m = create_matrix(GetValue("data"), sx, sy); // get the sizes but ignore the data
    SetOutputSize("OUTPUT", sx, sy);
    destroy_matrix(m);
}


void
HeadMovementModule::Init()
{
    
    output          =	GetOutputMatrix("OUTPUT");
    outputsize_x	=	GetOutputSizeX("OUTPUT");
    outputsize_y	=	GetOutputSizeY("OUTPUT");
    prev_output = GetOutputMatrix("OUTPUT");
    i = 0;
    j = 0;
    output[0][0] = 180;
    output[0][1] = 180;
    output[0][2] = 180;
    output[0][3] = 180;
    
    
    Bind(data, outputsize_x, outputsize_y, "data");
}





void
HeadMovementModule::Tick()
{
// max värdern
    //nacke up och ner
//        output[0][0] = 230;
    //huvud sida åt sida
//        output[0][1] = 240;
    //ögon
//        output[0][2] = 200;
//        output[0][3] = 200;
    
// min värdern
//        output[0][0] = 130;
//        output[0][1] = 120;
//        output[0][2] = 160;
//        output[0][3] = 160;
    
    
    if(i==0 && output[0][1]<240){
        output[0][1]++;
        if(output[0][1]==240){
            i = 1;
        }
        
    }else{
        output[0][1]= output[0][1]-1;
        if(output[0][1]==130){
            i= 0;
        }
        
    }
    
    
//    for(i;i < 100 && i> 1;i++){
//    output[0][0]=prev_output[0][0]+1;
//    output[0][0]=prev_output[0][0];
//    output[0][1]=prev_output[0][1]+1;
//    output[0][1]=prev_output[0][1];
//    output[0][2]=prev_output[0][2]+1;
//    output[0][2]=prev_output[0][2];
//    output[0][3]=prev_output[0][3]+1;
//    output[0][3]=prev_output[0][3];
//    
//    }
    
    
}



// Install the module. This code is executed during start-up.

static InitClass init("HeadMovementModule", &HeadMovementModule::Create, "Source/UserModules/HeadMovementModule/");


