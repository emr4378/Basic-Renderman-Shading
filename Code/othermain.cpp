RtInt	frame_width			= 533;
RtInt	frame_height		= 400;
RtInt	samples_x			= 2;
RtInt	samples_y			= 2;
RtFloat fov				= 45;

RtFloat l1_intensity	= 0.5;

RtFloat l2_intensity	= 0.8;
RtFloat l2_begin[]		= {0, 1, 4};
RtFloat l2_end[]		= {0, 0, 0};

char *	fl_Shader		= "Z:\\Projects\\RendermanThing\\RendermanThing\\MRMand"; //Source: http://www.renderman.org/RMR/Shaders/MRShaders/index.html
//char *	fl_Shader		= "Z:\\Projects\\RendermanThing\\RendermanThing\\brick";
//RtFloat fl_BrickColor[] = {1.0, 0.5, 0.0};
//RtFloat fl_MortarColor[]= {0.0, 0.5, 1.0};
//RtFloat fl_BrickVary	= 0.8;
//RtFloat fl_RowVary		= 1.0;
//RtFloat fl_BrickWid		= 0.1;
//RtFloat fl_BrickHei		= 0.02;
//RtFloat fl_MortarThick	= 0.008;
RtFloat fl_Color[]		= {1.0, 1.0, 1.0};
RtFloat fl_Points[]		= {-5, -5, 0,
							5, -5, 0,
							5, 5, 0,
							-5, 5, 0};

char *	wl_Shader		= "Z:\\Projects\\RendermanThing\\RendermanThing\\JMlunette"; //Source: http://www.renderman.org/RMR/Shaders/JMShaders/index.html#JMlunette
//char *	wl_Shader		= "Z:\\Projects\\RendermanThing\\RendermanThing\\wood2";
//RtFloat wl_RingScale	= 10;
//RtFloat	wl_TxtScale		= 1;
//RtFloat wl_LightWood[]	= {0.6, 0.9, 0.5};
//RtFloat wl_DarkWood[]	= {0.4, 0.3, 0.8};
//RtFloat wl_Grainy		= .1;
RtFloat wl_Color[]		= {1.0, 1.0, 1.0};
RtFloat wl_Points[]		= {-5, -5, 5,
							5, -5, 5, 
							5, -5, -5,
							-5, -5, -5};

char *	sp_Shader		= "Z:\\Projects\\RendermanThing\\RendermanThing\\JMredapple"; //Source: http://www.renderman.org/RMR/Shaders/JMShaders/index.html#JMredapple
//char *	sp_Shader		= "Z:\\Projects\\RendermanThing\\RendermanThing\\plastic";
RtFloat sp_Color[]		= {0.0, 1.0, 0.06};

int main(int argc, char** argv) {
	RiBegin(RI_NULL);
		//RiDisplay ("C:\\Users\\CheEsus\\Desktop\\Renderman Pics\\Renderman-2b.tiff","file","rgb",RI_NULL);
		RiDisplay("Yeah!", "framebuffer", "rgba", RI_NULL);
		RiFormat(frame_width, frame_height, 1);
		RiPixelSamples(samples_x, samples_y);
		RiProjection ("perspective", "fov", &fov, RI_NULL);
		RiTranslate(0, -2, 8);
		RiRotate(-110, 1, 0, 0);

		RiWorldBegin();

		RiLightSource("ambientlight", "intensity", &l1_intensity, RI_NULL);

		RiLightSource("distantlight", "from", l2_begin, "to", l2_end, "intensity", &l2_intensity, RI_NULL);

		//brick floor
		RiAttributeBegin();
			RiColor(fl_Color);
		/*	RiSurface(fl_Shader, "brickwidth", &fl_BrickWid,
								"brickheight", &fl_BrickHei,
								"mortarthickness", &fl_MortarThick,
								"brickcolor", fl_BrickColor,
								"mortarcolor", fl_MortarColor,
								"brickvary", &fl_BrickVary,
								"rowvary", &fl_RowVary, RI_NULL);*/
			RtFloat maxiteration = 10;
			RiSurface(fl_Shader, "maxiteration", &maxiteration, RI_NULL);
			RiPolygon(4, "P", fl_Points, RI_NULL);
		RiAttributeEnd();

		//wood floor
		RiAttributeBegin();
			RiColor(wl_Color);
			//RiSurface(wl_Shader, "ringscale", &wl_RingScale,
			//					"txtscale", &wl_TxtScale,
			//					"lightwood", wl_LightWood,
			//					"darkwood", wl_DarkWood,
			//					"grainy", &wl_Grainy, RI_NULL);
			RtFloat colorA[] = {1.0, .5, 0.0};
			RtFloat colorB[] = {0.3, 1, 0.8};
			RtFloat noiseScale = .12;
			RtFloat ulinewidth = .1;
			RtFloat vlinewidth = .15;
			RtFloat lunacrity = .6;
			RiSurface(wl_Shader, "colorA", colorA,
								"colorB", colorB,
								"noiseScale", &noiseScale,
								"ulinewidth", &ulinewidth,
								"vlinewidth", &vlinewidth,
								"lunacrity", &lunacrity,
								RI_NULL);
			RiPolygon(4, "P", wl_Points, RI_NULL);
		RiAttributeEnd();

		//ball/sphere
		RiAttributeBegin();
			RiTranslate(0,0,2);
			RiRotate(10, 1, 0, 1);
			RiColor(sp_Color);

			RtFloat roughness = 1;
			RtFloat redness = 0.7;
			RtFloat label = 0.8;
			RtFloat txtscale = 0.1;
			RiSurface(sp_Shader, "roughness", &roughness,
								"label", &label,
								"txtscale", &txtscale,
								"redness", &redness, RI_NULL);

			RiSphere(1,-1,1,360,RI_NULL);
		RiAttributeEnd();

		RiWorldEnd();
	RiEnd();

	return 0;
}