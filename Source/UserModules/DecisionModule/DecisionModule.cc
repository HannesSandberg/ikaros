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
#include "iostream"
#include "pthread.h"
#include "unistd.h"
// use the ikaros namespace to access the math library
// this is preferred to using <cmath>

using namespace ikaros;
using namespace std;

int  inputFromTerminal = 0;
int  nextProgram = 0;
float       startingTime;
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
    nextId          = 0;
    
    Bind(data, outputsize_x, outputsize_y, "data");
    
    input_marker_matrix = GetInputMatrix("INPUTMARKERS");
    input_marker_matrix_size_x = GetInputSizeX("INPUTMARKERS");
    input_marker_matrix_size_y = GetInputSizeY("INPUTMARKERS");
    output[0][0] = 0;
//    timer = new Timer();
    startingTime = 0;
    inputFromTerminal = 0;
}



void
DecisionModule::Tick()
{
    Timer  *timer = new Timer();
//    pthread_t t;
    if(thread == NULL){
        int rc;
        rc = pthread_create(&thread, NULL, DecisionModule::InputTerminal, NULL);
    }
//    Thread * t;
//    t = new Thread();
//    t->Create(DecisionModule::InputTerminal, NULL);

    
    int id = input_marker_matrix[0][16];
    id = id/10;
    
    if(nextId != 0 && id == 0){
        id = nextId;
    }
    
    if(startingTime == 0 && id != 0){
        startingTime = timer->GetTime();
    }
    
    if(timer->GetTime() - startingTime < 250 && id != 0){
        output[0][0] = 10;
        nextId = id;
    }else if(id == 150){
        //Angry
        output[0][0] = 2;
        nextId = 0;
    }else if(id == 122){
        //Happy
        output[0][0] = 3;
        nextId = 0;
    }else if(id == 196){
        //Thinking
        output[0][0] = 1;
        nextId = 0;
    }else if (id == 102){
        //Confused
        output[0][0] = 4;
        nextId = 0;
    }else if (id == 199){
        //Indiferent
        output[0][0] = 5;
        nextId = 0;
    }else if (id == 156){
        //Sad
        output[0][0] = 6;
        nextId = 0;
    }
    
    if((timer->GetTime() - startingTime)/1000 >= 10){
        if(id == 0){
            output[0][0] = 0;
            startingTime = 0;
//            inputFromTerminal = 0;
        }
    }
    
    if(inputFromTerminal != 0){
        if(nextProgram == 0){
            nextProgram = inputFromTerminal;
            output[0][0] = 0;
        }else{
            output[0][0] = nextProgram;
//            nextProgram = 0;
        }
    }else{
        output[0][0] = 0;
        startingTime = 0;
        id = 0;
        nextId = 0;
    }
}

void
*DecisionModule::InputTerminal(void *)
{
    Timer  *timer = new Timer();
//    int i;
    while(true){
        cout << "Please enter an integer value for different mental states, 1: Thinking, 2: Angry, 3: Happy, 4: Confused 5: Indiferent, 6: Sad : ";
        startingTime = timer->GetTime();
        cin >> inputFromTerminal;
        nextProgram = 0;
//        sleep(10);
//        inputFromTerminal = 0;
    }
//    pthread_exit(NULL);
}

// Install the module. This code is executed during start-up.

static InitClass init("DecisionModule", &DecisionModule::Create, "Source/UserModules/DecisionModule/");
