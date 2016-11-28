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
    timer = new Timer();
    output          =	GetOutputMatrix("OUTPUT");
    outputsize_x	=	GetOutputSizeX("OUTPUT");
    outputsize_y	=	GetOutputSizeY("OUTPUT");
    prev_output = GetOutputMatrix("OUTPUT");
    i = 0;
    j = 0;
    startingTime = 0;
    output[0][0] = 180;
    output[0][1] = 180;
    output[0][2] = 180;
    output[0][3] = 180;
    running = false;
    input_pattern_array = GetInputArray("INPUTPATTERN");
    input_pattern_array_size = GetInputSize("INPUTPATTERN");
    tickTime = 0;
    prevTickTime = timer -> GetTime();
    Bind(data, outputsize_x, outputsize_y, "data");
}





void
HeadMovementModule::Tick()
{
     UpdateTickTime();
    
    
      
   
    
    if(input_pattern_array[0] == 0){
        //Nothing (standard white eyes
        output[0][0] = 180;
        output[0][1] = 180;
        output[0][2] = 180;
        output[0][3] = 180;
        running = false;
        InitStartTime();
        
    }else if(input_pattern_array[0] == 1){
        //Loading
        // Copy every iteration if parameter changed through the binding

//        if(output[0][0] > 160){
//            output[0][0] = output[0][0] - 2;
//        }
        output[0][2] = output[0][2] + MoveTo(output[0][2], 200, 1-GetTimeDiff());
        output[0][3] = output[0][3] + MoveTo(output[0][3], 200, 1-GetTimeDiff());
        output[0][0] = 180;
        output[0][1] = 180;
       
       
    }else if(input_pattern_array[0] == 2){
        //Angry
        output[0][0] = 180;
        output[0][2] = 180;
        output[0][3] = 180;
        output[0][1] = 180;
        if(!running){
        InitStartTime();
            running = true;
        }
        // TODO: fixa så den kör mili secunder istället
        if(GetTimeDiff()<0.5){
            output[0][1] = 140;
            //output[0][1]= output[0][1]+MoveTo(output[0][1],140,0.5-GetTimeDiff());
            
        }else if(GetTimeDiff()<1 && GetTimeDiff()>0.5){
           output[0][1]= 220;
            //output[0][1]=output[0][1] + MoveTo(output[0][1],220,1-GetTimeDiff());
        
        }else{
            output[0][1] = 180;
            if(GetTimeDiff()>1){
                InitStartTime();
                
            }
            //output[0][1] = 180;
            
            
        
        }
        i++;
        j++;
       
    }else if(input_pattern_array[0] == 3){
        //Happy
        if(!running){
            InitStartTime();
            running = true;
        }
        if(GetTimeDiff()<2){
        output[0][0] = output[0][0] + MoveTo(output[0][0],165,2-GetTimeDiff());
        }
        output[0][2]= 183;
        output[0][3]= 177;
        
        
//        if(output[0][0] > 160){
//            output[0][0] = output[0][0] - 2;
//        }
        
        
        
    }else if(input_pattern_array[0] == 4){
        output[0][3]= 190;
        output[0][2]= 170;
        //Don't understand / wrong imput
        if(!running){
            InitStartTime();
            running = true;
        }
        if(GetTimeDiff()<1){
//        output[0][3] = output[0][3] + MoveTo(output[0][3], 210,1   - GetTimeDiff());
//        output[0][4] = output[0][4] + MoveTo(output[0][4], 140,1   - GetTimeDiff());
            output[0][3]= 200;
            output[0][2]= 160;
           
        }else if(GetTimeDiff()<2){
//            output[0][3] = output[0][3] + MoveTo(output[0][3], 140,1   - GetTimeDiff());
//            output[0][4] = output[0][4] + MoveTo(output[0][4], 210,1   - GetTimeDiff());
            output[0][3]= 160;
            output[0][2]= 200;
            
            
        }
//        if(GetTimeDiff()<1){
//            output[0][0] = output[0][0] + MoveTo(output[0][0], 210,1- GetTimeDiff());
//            //output[0][1] = output[0][1] + MoveTo(output[0][1], 210, GetTimeDiff());
//            //output[0][0]= 210;
//          //  output[0][1]= 210;
//        }else if(GetTimeDiff()>1 && GetTimeDiff()<2){
//            output[0][0] = output[0][0] + MoveTo(output[0][0], 150, 2-GetTimeDiff());
//            //output[0][0]= 150;
//           // output[0][1]= 210;
//        }else if(GetTimeDiff()>2 && GetTimeDiff()<3){
//            output[0][0] = output[0][0] + MoveTo(output[0][0], 150,3 - GetTimeDiff());
//            //printf("%.6f",MoveTo(output[0][0], 150,2 - GetTimeDiff());
//            //output[0][1] = output[0][1] + MoveTo(output[0][1], 150,2 - GetTimeDiff());
//            //output[0][0]= 150;
//            //output[0][1]= 150;
//        }else if(GetTimeDiff()>3 &&GetTimeDiff()<4){
//            output[0][0] = output[0][0] + MoveTo(output[0][0], 210,4 - GetTimeDiff());
//
           // output[0][0]= 210;
            //output[0][1]= 150;
        
        else{
            InitStartTime();
            
//            output[0][1]= 180;
            }
//        if(j<40 && output[0][0] > 160){
//           output[0][0] = output[0][0] - 2;
//        }
//        if(j>40 && j < 50){
//            output[0][0] = output[0][0]+2;
//        }
//        
//    if(i>50 && i < 55)
//    {
//        output[0][0] = 180;
//        //output[0][1]= 700;
//        
//        output[0][1] = 220;
//        
//    }else if(i>55 && i< 63){
//        output[0][1] = 140;
//        //output[0][1]= -500 ;
//        //        output[0][1] = 250;
//        
//    } else{
//        if(i>63){
//            i=45;
//        }
//        output[0][1] = 180;
//        
//        //        }
//        
//    }
//    i++;
//    j++;
    }else if(input_pattern_array[0] == 5){
        //bored
//        if(j<15){
//            output[0][2] = output[0][2] +4;
//            output[0][3] = output[0][3] +4;
//            
//        }
//        if(j > 15 && j < 30){
//            output[0][2] = output[0][2] -4;
//            output[0][3] = output[0][3] -4;
//            
//        }
//        if(j>30&&j<40){
//            output[0][2] = 180;
//            output[0][3] = 180;
//        }
//        if(j>40 && j < 60){
//            output[0][2] = output[0][2] -2;
//            output[0][3] = output[0][3] -2;
//            output[0][1] = output[0][1] - 4;
//        }
//        
//        if(j>60 && j < 80)
//        {
//            output[0][2] = output[0][2] +4;
//            output[0][3] = output[0][3] +4;
//            
//        }
//        if(j > 80){
//            output[0][1] = output[0][1] + 2;
//            output[0][2] = output[0][2] -4;
//            output[0][3] = output[0][3] -4;
//            
//            if(output[0][2]<=180){
//                output[0][2]=180;
//                output[0][3]=180;
//                
//            }
        
        
        
        i++;
        j++;
    } else if(input_pattern_array[0] == 6){
        //Sad robot is sad
        //TODO: fixa till sekunder
        if(!running){
            InitStartTime();
            running = true;
        }
        if(GetTimeDiff()<7){
        output[0][2] = output[0][2] + MoveTo(output[0][2], 200, 1-GetTimeDiff());
        output[0][3] = output[0][3] + MoveTo(output[0][3], 160, 1-GetTimeDiff());
        output[0][0] = output[0][0] + MoveTo(output[0][0], 200, 3-GetTimeDiff());
        output[0][1] = output[0][1] + MoveTo(output[0][1], 210, 4-GetTimeDiff());
        }
        
//        if(i < 20){
//            output[0][2]= output[0][2] +3;
//            output[0][3]= output[0][3] -3;
//        }else if(i < 80 && i> 20){
//            if(output[0][0] < 200){
//            output[0][0]= output[0][0] +1;
//            }
//            output[0][1]= output[0][1] +0.5;
//        }
//        i++;
        
    }else{
        running = false;
        InitStartTime();
    }
if(input_pattern_array[0] != 1 && input_pattern_array[0] != 5 && input_pattern_array[0] != 6 && input_pattern_array[0] != 2){
    i=0;
    j=0;
}
    

    
    
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
    
//    röra huvudet höger till vänster
//    if(i==0 && output[0][1]<240){
//        output[0][1]++;
//        
//        if(output[0][1]==240){
//            i = 1;
//                   }
//        
//    }else{
//        output[0][1]= output[0][1]-1;
//        
//        if(output[0][1]==130){
//            i= 0;
//           
//        }
//        
//    }
//
  
//    ögon höger till vänster
//    if(j%6 == 1){
//    
//    if(i==0 && output[0][2]<200){
//                output[0][2]++;
//                output[0][3]++;
//        
//                if(output[0][2]>=200){
//                    i = 1;
//                           }
//        
//            }else{
//                output[0][2]= output[0][2]-1;
//                output[0][3]= output[0][3]-1;
//        
//                if(output[0][2]<=160 ){
//                    i= 0;
//                    output[0][2]= 160;
//                    output[0][3]= 160;
//                   
//                }
//                
//            }
//        }
//    j++;
//    
    
    
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

float
HeadMovementModule::GetTimeDiff()
{
    return (((timer->GetTime())-startingTime)/1000);
}

void
HeadMovementModule::InitStartTime()
{
    startingTime = timer->GetTime();
}
float
HeadMovementModule::MoveTo(float current,float goal, float timeLeft)
{
    if(timeLeft>0){
    float ticks = timeLeft/tickTime;
    float movementLeft = goal - current;
    printf("%.1f",(movementLeft));
    return movementLeft/ticks;
    }
    return 0;
}
void
HeadMovementModule::UpdateTickTime()
{
    tickTime = ((timer->GetTime())-(prevTickTime))/1000;
    prevTickTime = timer ->GetTime();
            
}





// Install the module. This code is executed during start-up.

static InitClass init("HeadMovementModule", &HeadMovementModule::Create, "Source/UserModules/HeadMovementModule/");


