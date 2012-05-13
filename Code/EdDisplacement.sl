#include "rmannotes.sl"

displacement
EdDisplacement (float Km = .02;
				float seed = 0;
				float iter = 5;
				float seaLevel = 0;) 
{
float surface_mag, layer_mag;		//magnitude of displacement
point PP;							//current point on object

surface_mag = 0;


//layer 1: The offsetting of points
layer_mag = 0;
PP = transform ("object", P);

float s;
float scale = 1;
float rough = .5;
float i;
for (i = 0; i < iter; i++) {
	//using just snoise(PP / scale) approaches 0 too quickly
	layer_mag += snoise(seed + PP * scale) / scale;
	scale /= rough;
}



if (layer_mag > seaLevel) {
	surface_mag += layer_mag;
}


/* Output */
point Ndiff = normalize(N) - normalize(Ng);
P += P * Km * surface_mag * normalize(N);
N = normalize(calculatenormal(P)) + Ndiff;
}