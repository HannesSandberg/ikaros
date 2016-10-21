//
//	DecisionModule.cc		This file is a part of the IKAROS project
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

#include "DecisionModule.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
DecisionModule::SetSizes() // Infer output size from data if none is given
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
DecisionModule::Init()
{
    output          =	GetOutputMatrix("OUTPUT");
    outputsize_x	=	GetOutputSizeX("OUTPUT");
    outputsize_y	=	GetOutputSizeY("OUTPUT");
    prev_output     =   GetOutputMatrix("OUTPUT");
    i               = 0;
    j               = -3;
    startTick       = 0;
    nextId          = 0;
    
    Bind(data, outputsize_x, outputsize_y, "data");
    
    input_marker_matrix = GetInputMatrix("INPUTMARKERS");
    input_marker_matrix_size_x = GetInputSizeX("INPUTMARKERS");
    input_marker_matrix_size_y = GetInputSizeY("INPUTMARKERS");
    output[0][0] = 0;
}



void
DecisionModule::Tick()
{

    

    int id = input_marker_matrix[0][16];
    
    if(nextId != 0 && id == 0){
        id = nextId;
    }
    
    if(startTick < 5 && id != 0){
        output[0][0] = 10;
        startTick++;
        i = 2;
        nextId = id;
    }else if(id == 1502){
        //Angry
        output[0][0] = 2;
        i = 2;
        nextId = 0;
    }else if(id == 1503){
        //Happy
        output[0][0] = 3;
        i = 2;
        nextId = 0;
    }else if(id == 1505){
        //Loading
        output[0][0] = 1;
        i = 2;
        nextId = 0;
    }else if (id == 1504){
        //error
        output[0][0] = 4;
        i = 2;
        nextId = 0;
    }else if (id == 1501){
        //error
        output[0][0] = 5;
        i = 2;
        nextId = 0;
    }
    
    if(i % 105 == 1){
        if(id == 0){
            output[0][0] = 0;
            startTick = 0;
        }
    }
    
    i++;
     
}


// Install the module. This code is executed during start-up.

static InitClass init("DecisionModule", &DecisionModule::Create, "Source/UserModules/DecisionModule/");
