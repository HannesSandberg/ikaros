//
//	EyeModule.cc		This file is a part of the IKAROS project
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

#include "EyeModule.h"

// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;


void
EyeModule::SetSizes() // Infer output size from data if none is given
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
    SetOutputSize("OUTPUT2", sx, sy);
    SetOutputSize("OUTPUTRED", sx, sy);
    SetOutputSize("OUTPUTGREEN", sx, sy);
    SetOutputSize("OUTPUTBLUE", sx, sy);
    destroy_matrix(m);
}



void
EyeModule::Init()
{
    
    output          =	GetOutputMatrix("OUTPUT");
    output2         =	GetOutputMatrix("OUTPUT2");
    outputsize_x	=	GetOutputSizeX("OUTPUT");
    outputsize_y	=	GetOutputSizeY("OUTPUT");
    prev_output     =   GetOutputMatrix("OUTPUT");
    i = 0;
    j = -3;
    errorTick       =   0;
    outputRED       =	GetOutputMatrix("OUTPUTRED");
    outputGREEN     =	GetOutputMatrix("OUTPUTGREEN");
    outputBLUE      =	GetOutputMatrix("OUTPUTBLUE");
    
    Bind(data, outputsize_x, outputsize_y, "data");
    
    input_color_array = GetInputArray("INPUTCOLOR");
    input_color_array_size = GetInputSize("INPUTCOLOR");
    
    input_pattern_array = GetInputArray("INPUTPATTERN");
    input_pattern_array_size = GetInputSize("INPUTPATTERN");
    
    blinkTick       = 0;
    timer = new Timer();
    blinkTime = 0;
}



void
EyeModule::Tick()
{
    
    if(input_pattern_array[0] == 0){
        //Nothing (standard white eyes
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = 0.5;
            outputGREEN[0][k] = 0.5;
            outputBLUE[0][k] = 0.5;
        }
    }else if(input_pattern_array[0] == 1){
        //Loading
        // Copy every iteration if parameter changed through the binding
        if (i>11){i=0;}
        if (j>11){j=0;}
        if(output[0][i]<1){
            output[0][i] = prev_output[0][i] + 0.25;
            output[0][j] = prev_output[0][j] - 0.25;
            prev_output[0][i] = output[0][i];
//            outputBLUE[0][i] = output[0][i];
        }else{
            i++;
            j++;
        }
        for(int k = 0; k < outputsize_x; k++ ){
            for(int k = 0; k < outputsize_x; k++ ){
                for(int f = 0; f < outputsize_y; f++ ){
                    outputBLUE[f][k] = output[f][k];
                    outputGREEN[f][k] = 0;
                    outputRED[f][k] = 0;
                }
            }
        }
//        blinkTick = 4;
        blinkTime = timer->GetTime();
    }else if(input_pattern_array[0] == 2){
        //Angry
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = 0.5;
            outputGREEN[0][k] = 0;
            outputBLUE[0][k] = 0;
        }
    }else if(input_pattern_array[0] == 3){
        //Happy
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = 0;
            outputGREEN[0][k] = 0.7;
            outputBLUE[0][k] = 0;
        }
    }else if(input_pattern_array[0] == 4){
        //Dont understand
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = ikaros::random(0, 1);
            outputGREEN[0][k] = ikaros::random(0, 1);
            outputBLUE[0][k] = ikaros::random(0, 1);
        }

//        if(errorTick < 40){
//            if (i>11){i=0;}
//            if (j>11){j=0;}
//            if(output[0][i]<1){
//                output[0][i] = prev_output[0][i] + 0.25;
//                output[0][j] = prev_output[0][j] - 0.25;
//                prev_output[0][i] = output[0][i];
//                //            outputBLUE[0][i] = output[0][i];
//            }else{
//                i++;
//                j++;
//            }
//            for(int k = 0; k < outputsize_x; k++ ){
//                for(int k = 0; k < outputsize_x; k++ ){
//                    for(int f = 0; f < outputsize_y; f++ ){
//                        outputBLUE[f][k] = output[f][k];
//                        outputGREEN[f][k] = 0;
//                        outputRED[f][k] = 0;
//                    }
//                }
//            }
//        }else{
//            for(int k = 0; k < outputsize_x; k++ ){
//                outputRED[0][k] = 0.5;
//                outputGREEN[0][k] = 0.5;
//                outputBLUE[0][k] = 0.5;
//            }
//            for(int k = 0; k < outputsize_x; k++ ){
//                for(int k = 0; k < outputsize_x; k++ ){
//                    for(int f = 0; f < outputsize_y; f++ ){
//                        output[f][k] = 0;
//                    }
//                }
//            }
//        }
//        if(errorTick == 50 || errorTick == 51 || errorTick == 52 || errorTick == 70 || errorTick == 71 || errorTick == 72|| errorTick == 90 || errorTick == 91 || errorTick == 92){
//            for(int k = 0; k < outputsize_x; k++ ){
//                outputRED[0][k] = 1;
//                outputGREEN[0][k] = 0;
//                outputBLUE[0][k] = 0;
//            }
//        }
////        blinkTick = 4;
//        blinkTime = timer->GetTime();
//        errorTick++;
    }else if (input_pattern_array[0] == 5){
        //bored
//        for(int k = 0; k < outputsize_x; k++ ){
//            outputRED[0][k] = 0.25;
//            outputGREEN[0][k] = 0.25;
//            outputBLUE[0][k] = 0.25;
//        }
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = ikaros::random(0, 1);
            outputGREEN[0][k] = ikaros::random(0, 1);
            outputBLUE[0][k] = ikaros::random(0, 1);
        }
    }else if(input_pattern_array[0] == 6){
        //Sad
        for(int k = 0; k < outputsize_x; k++ ){
            outputRED[0][k] = 0;
            outputGREEN[0][k] = 0;
            outputBLUE[0][k] = 0.3;
        }
    }
    
    if(input_pattern_array[0] != 4){
        errorTick = 0;
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
    float random = ikaros::random(0.8, 1.2);
    //Blink
//    if(blinkTick >= 70 * random){
//        blinkTick = 0;
//        random = ikaros::random(0.8, 1.2);
//    }
    if(timer->GetTime() - blinkTime >= 3529 * random){
        blinkTick = 0;
        blinkTime = timer->GetTime();
        random = ikaros::random(0.8, 1.2);
    }
    Blink();
    
}

void
EyeModule::Blink()
{
    if(blinkTick < 1){
        for(int a = 8; a <= 9; a++){
            outputRED[0][a] = 0;
            outputGREEN[0][a] = 0;
            outputBLUE[0][a] = 0;
        }
        for(int a = 2; a <= 3; a++){
            outputRED[0][a] = 0;
            outputGREEN[0][a] = 0;
            outputBLUE[0][a] = 0;
        }
    }else if(blinkTick < 2){
        for(int a = 7; a <= 10; a++){
            outputRED[0][a] = 0;
            outputGREEN[0][a] = 0;
            outputBLUE[0][a] = 0;
        }
        for(int a = 1; a <= 4; a++){
            outputRED[0][a] = 0;
            outputGREEN[0][a] = 0;
            outputBLUE[0][a] = 0;
        }
    }else if(blinkTick < 3){
        for(int a = 0; a <= 11; a++){
            outputRED[0][a] = 0;
            outputGREEN[0][a] = 0;
            outputBLUE[0][a] = 0;
        }
    }
    
    blinkTick++;
}

// Install the module. This code is executed during start-up.

static InitClass init("EyeModule", &EyeModule::Create, "Source/UserModules/EyeModule/");
