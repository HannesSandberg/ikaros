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
    i = 1;
    j = 0;
    Bind(data, outputsize_x, outputsize_y, "data");
    
//    input_color_array = GetInputArray("INPUTCOLOR");
//    input_color_array_size = GetInputSize("INPUTCOLOR");
    
    input_pattern_array = GetInputArray("INPUTPATTERN");
    input_pattern_array_size = GetInputSize("INPUTPATTERN");
}



void
MouthModule::Tick()
{
//    for(int k = 0; k < outputsize_x; k++ ){
//        outputRED[0][k] = 0;
//        outputGREEN[0][k] = 0;
//        outputBLUE[0][k] = 0;
//        outputRED2[0][k] = 0;
//        outputGREEN2[0][k] = 0;
//        outputBLUE2[0][k] = 0;
//    }
    if(input_pattern_array[0] == 0){
        //Standard
            for(int k = 0; k < outputsize_x; k++ ){
                outputRED[0][k] = 0;
                outputGREEN[0][k] = 0;
                outputBLUE[0][k] = 0;
                outputRED2[0][k] = 0;
                outputGREEN2[0][k] = 0;
                outputBLUE2[0][k] = 0;
            }
//        for(int k = 3; k < 5; k++ ){
////            outputRED[0][k] = 1;
////            outputGREEN[0][k] = 0;
////            outputBLUE[0][k] = 0;
//            outputRED2[0][k] = 1;
//            outputGREEN2[0][k] = 1;
//            outputBLUE2[0][k] = 0;
//        }
//        outputRED2[0][1] = 0.5;
//        outputGREEN2[0][1] = 0.5;
//        outputRED2[0][6] = 0.5;
//        outputGREEN2[0][6] = 0.5;
//        outputRED2[0][2] = 0.75;
//        outputGREEN2[0][2] = 0.75;
//        outputRED2[0][5] = 0.75;
//        outputGREEN2[0][5] = 0.75;

    
    }else if(input_pattern_array[0] == 1){
//        //Loading
//        outputBLUE2[0][i-2] = outputBLUE2[0][i]-0.5;
//        outputBLUE[0][i-2] = outputBLUE[0][i]-0.5;
//        outputBLUE2[0][i-1] = outputBLUE2[0][i]-0.5;
//        outputBLUE[0][i-1] = outputBLUE[0][i]-0.5;
//        outputBLUE2[0][i] = outputBLUE2[0][i]+0.5;
//        outputBLUE[0][i] = outputBLUE[0][i]+0.5;
//        outputBLUE2[0][i+1] = outputBLUE2[0][i+1]+0.5;
//        outputBLUE[0][i+1] = outputBLUE[0][i+1]+0.5;
        if (i>8){i=0;}
        if (j>8){j=0;}
        if(outputBLUE[0][i]<1){
            outputBLUE[0][i] = prev_output[0][i] + 0.5;
            outputBLUE[0][j] = prev_output[0][j] - 0.5;
            outputBLUE2[0][i] = prev_output[0][i] + 0.5;
            outputBLUE2[0][j] = prev_output[0][j] - 0.5;
            prev_output[0][i] = outputBLUE[0][i];
            //            outputBLUE[0][i] = output[0][i];
        }else{
            i++;
            j++;
        }
//        for(int k = 0; k < outputsize_x; k++ ){
//            for(int k = 0; k < outputsize_x; k++ ){
//                for(int f = 0; f < outputsize_y; f++ ){
//                    outputBLUE[f][k] = output[f][k];
//                    outputGREEN[f][k] = 0;
//                    outputRED[f][k] = 0;
//                }
//            }
//        }
//
    }else if(input_pattern_array[0] == 2){
//        //Angry
    //        outputBLUE2[0][1] = 1;
        
        outputRED[0][2] = 0.5;
        outputRED[0][5] = 0.5;
        outputRED[0][3] = 1;
        outputRED[0][4] = 1;
        
        outputRED2[0][2] = 0.5;
        outputRED2[0][5] = 0.5;
        outputRED2[0][3] = 1;
        outputRED2[0][4] = 1;
//    for(int a = 1; a<7; a++){
//        outputRED[0][a] = 1;
//    }
    }else if(input_pattern_array[0] == 3){
//        //Happy
        outputGREEN[0][1] = 0.7;
        outputGREEN[0][6] = 0.7;
    for(int a = 2; a<6; a++){
        outputGREEN2[0][a] = 0.7;
    }
//
    }else if(input_pattern_array[0] == 4){
        for(int k = 1; k < 7; k++){
        outputRED[0][k] = ikaros::random(0, 0.7);
        outputRED2[0][k] = ikaros::random(0, 0.7);
        outputBLUE[0][k] = ikaros::random(0, 0.7);
        outputBLUE2[0][k] = ikaros::random(0, 0.7);
        outputGREEN[0][k] = ikaros::random(0, 0.7);
        outputGREEN2[0][k] = ikaros::random(0, 0.7);
        }
//        //Dont understand
//
    }else if (input_pattern_array[0] == 5){
        //bored
        outputRED[0][2] = 1;
        outputRED[0][4] = 1;
        outputRED[0][6] = 1;
        
        outputRED2[0][1] = 1;
        outputRED2[0][3] = 1;
        outputRED2[0][5] = 1;

    }else if(input_pattern_array[0] == 6){
//        //Sad
    outputBLUE2[0][1] = 1;
    outputBLUE2[0][6] = 1;
    for(int a = 2; a<6; a++){
        outputBLUE[0][a] = 1;
    }
//
    }
    
//    if(input_pattern_array[0] != 4){
////        errorTick = 0;
//    }
//    
//    if(input_pattern_array[0] != 4 && input_pattern_array[0] != 1){
//        for(int k = 0; k < outputsize_x; k++ ){
//            for(int k = 0; k < outputsize_x; k++ ){
//                for(int f = 0; f < outputsize_y; f++ ){
//                    output[f][k] = 0;
//                }
//            }
//        }
//    }
    i++;
    j++;
}


// Install the module. This code is executed during start-up.

static InitClass init("MouthModule", &MouthModule::Create, "Source/UserModules/MouthModule/");
