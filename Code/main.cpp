#include <string>
#include <ri.h>

using namespace std;



RtInt	frame_width			= 1024;
RtInt	frame_height		= 768;
RtInt	samples_x			= 2;
RtInt	samples_y			= 2;
RtFloat fov				= 80;

RtFloat l1_intensity	= 0.5;

RtFloat l2_intensity	= 15000;
RtFloat l2_begin[]		= {40, 20, 50};
RtFloat l2_end[]		= {0, 0, 0};


int main(int argc, char** argv) {
	srand(0);

	RtFloat seed;
	RtFloat scale;
	RtFloat iter;

	RiBegin(RI_NULL);
		//RiDisplay ("ExportFilePath.tiff","file","rgb",RI_NULL);
		RiDisplay("Eduardo Rodrigues", "framebuffer", "rgb", RI_NULL);
		RiFormat(frame_width, frame_height, 1);
		RiPixelSamples(samples_x, samples_y);
		RiProjection ("perspective", "fov", &fov, RI_NULL);

		RiWorldBegin();

		RiLightSource("ambientlight", "intensity", &l1_intensity, RI_NULL);

		RiLightSource("pointlight", "from", l2_begin, "intensity", &l2_intensity, RI_NULL);



		//moon
		RiAttributeBegin();
			RiTranslate(-.5, 0, 6);
			//RiTranslate(1, -1, 2);
			RiRotate(-15, 1, 1, 0);

			seed = 1243;
			scale = 0.10;
			iter = 10;
			RtFloat seaLevel = -5;
			RiDisplacement("EdDisplacement", "Km", &scale,
									"seed", &seed,
									"iter", &iter,
									"seaLevel", &seaLevel,
									RI_NULL);
			RiSurface("EdPhong", RI_NULL);

			RiSphere(1,-1,1,360,RI_NULL);
		RiAttributeEnd();

		//planet
		RiAttributeBegin();
			RiTranslate(-1, -.5, 2);
			RiRotate(15, 0, 1, 0);

			seed = 5243;
			scale = 0.25;
			iter = 20;
			RiDisplacement("EdDisplacement", "Km", &scale,
									"seed", &seed,
									"iter", &iter, RI_NULL);

			RiSurface("EdSurface", "Km", &scale,
								"seed", &seed,
								"iter", &iter, RI_NULL);
			
			RiSphere(1,-1,1,360,RI_NULL);
		RiAttributeEnd();

		//lens flare
		RiAttributeBegin();
			float off = .5;
			
			RtFloat points[] = {-(off*1.5), -(off*1.5), off,
								-(off*1.5), (off*1.5), off,
								(off*1.5), (off*1.5), off,
								(off*1.5), -(off*1.5), off};

			RtFloat intense = 0.05;
			RiSurface("EdLensFlare", "intensity", &intense, RI_NULL);
			
			RiPolygon(4, "P", points, RI_NULL);
		RiAttributeEnd();

		RiWorldEnd();
	RiEnd();

	return 0;
}