//
//	MouthModule.h		This file is a part of the IKAROS project
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

#ifndef MouthModule_
#define MouthModule_

#include "IKAROS.h"

class MouthModule: public Module
{
public:
    static Module * Create(Parameter * p) { return new MouthModule(p); }
    
    float **	data;
    float **	output;
    float **	outputRED;
    float **	outputGREEN;
    float **	outputBLUE;
    float **	outputRED2;
    float **	outputGREEN2;
    float **	outputBLUE2;
    float **	prev_output;
    int         outputsize_x;
    int         outputsize_y;
    bool        blinkOn;

//    float *     input_color_array;
//    int         input_color_array_size;
    
    float *     input_pattern_array;
    int         input_pattern_array_size;
    
    MouthModule(Parameter * p) : Module(p) {}
    virtual	~MouthModule() {}
    
    void            SetSizes();
    
    void			Init();
    void			Tick();
//    void            Blink();
};

#endif