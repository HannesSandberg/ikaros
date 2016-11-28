//
//	PupilModule.cc		This file is a part of the IKAROS project
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
#include "PupilModule.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;

void
PupilModule::SetSizes() // Infer output size from data if none is given
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
PupilModule::Init()
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
    
    input_pattern_array = GetInputArray("INPUTPATTERN");
    input_pattern_array_size = GetInputSize("INPUTPATTERN");
    
    
    Bind(data, outputsize_x, outputsize_y, "data");
}





void
PupilModule::Tick()
{
    
    
    // min värdern
    
    if(input_pattern_array[0] == 10){
        //Before normal pattern
        output[0][0] = 200;
        output[0][1] = 200;
    }
   
    
    
    if(input_pattern_array[0] == 0){
        //Nothing (standard white eyes
        output[0][0] = 220;
        output[0][1] = 220;
       
    }else if(input_pattern_array[0] == 1){
        //Loading
        // Copy every iteration if parameter changed through the binding
        output[0][0] = 220;
        output[0][1] = 220;
    }else if(input_pattern_array[0] == 2){
        //Angry
        output[0][0] = 250;
        output[0][1] = 250;
    }else if(input_pattern_array[0] == 3){
        //Happy
        output[0][0] = 190;
        output[0][1] = 190;
        
    }else if(input_pattern_array[0] == 4){
        output[0][0] = 190;
        output[0][1] = 220;
    }else if(input_pattern_array[0] == 5){
        output[0][0] = 220;
        output[0][1] = 220;
    }

    
}



// Install the module. This code is executed during start-up.

static InitClass init("PupilModule", &PupilModule::Create, "Source/UserModules/PupilModule/");




