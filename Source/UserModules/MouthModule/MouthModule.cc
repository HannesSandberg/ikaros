//
//	MouthModule.cc		This file is a part of the IKAROS project
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

#include "MouthModule.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
MouthModule::SetSizes() // Infer output size from data if none is given
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
//    SetOutputSize("OUTPUT2", sx, sy);
    SetOutputSize("OUTPUTRED", sx, sy);
    SetOutputSize("OUTPUTGREEN", sx, sy);
    SetOutputSize("OUTPUTBLUE", sx, sy);
    SetOutputSize("OUTPUTRED2", sx, sy);
    SetOutputSize("OUTPUTGREEN2", sx, sy);
    SetOutputSize("OUTPUTBLUE2", sx, sy);
    destroy_matrix(m);
}



void
MouthModule::Init()
{
    
    output          =	GetOutputMatrix("OUTPUT");
    outputsize_x	=	GetOutputSizeX("OUTPUT");
    outputsize_y	=	GetOutputSizeY("OUTPUT");
    prev_output     =   GetOutputMatrix("OUTPUT");
    outputRED       =	GetOutputMatrix("OUTPUTRED");
    outputGREEN     =	GetOutputMatrix("OUTPUTGREEN");
    outputBLUE      =	GetOutputMatrix("OUTPUTBLUE");
    outputRED2       =	GetOutputMatrix("OUTPUTRED2");
    outputGREEN2     =	GetOutputMatrix("OUTPUTGREEN2");
    outputBLUE2      =	GetOutputMatrix("OUTPUTBLUE2");
    
    Bind(data, outputsize_x, outputsize_y, "data");
    
//    input_color_array = GetInputArray("INPUTCOLOR");
//    input_color_array_size = GetInputSize("INPUTCOLOR");
    
    input_pattern_array = GetInputArray("INPUTPATTERN");
    input_pattern_array_size = GetInputSize("INPUTPATTERN");
}



void
MouthModule::Tick()
{
    
    if(input_pattern_array[0] == 0){
        //Standard
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = 0.5;
            outputGREEN[0][k] = 0.5;
            outputBLUE[0][k] = 0.5;
            outputRED2[0][k] = 0.5;
            outputGREEN2[0][k] = 0.5;
            outputBLUE2[0][k] = 0.5;
        }
    }else if(input_pattern_array[0] == 1){
        //Loading

    }else if(input_pattern_array[0] == 2){
        //Angry
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = 0.5;
            outputRED2[0][k] = 0.5;
        }
    }else if(input_pattern_array[0] == 3){
        //Happy

    }else if(input_pattern_array[0] == 4){
        //Dont understand

    }else if (input_pattern_array[0] == 5){
        //bored

    }else if(input_pattern_array[0] == 6){
        //Sad

    }
    
    if(input_pattern_array[0] != 4){
//        errorTick = 0;
    }
    
    if(input_pattern_array[0] != 4 && input_pattern_array[0] != 1){
        for(int k = 0; k < outputsize_x; k++ ){
            for(int k = 0; k < outputsize_x; k++ ){
                for(int f = 0; f < outputsize_y; f++ ){
                    output[f][k] = 0;
                }
            }
        }
    }
    
}


// Install the module. This code is executed during start-up.

static InitClass init("MouthModule", &MouthModule::Create, "Source/UserModules/MouthModule/");
