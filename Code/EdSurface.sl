#include "rmannotes.sl"

surface 
EdSurface (float Ka = 0.8, Kd = 0.7, roughness = 0.1;
		color specularcolor = 1;
		float Km = .02;
		float seed = 0;
		float iter = 5;
		float seaLevel = 0;) 
{
color surface_color, layer_color;
color surface_opac, layer_opac;
float surface_mag, layer_mag;		//magnitude of displacement
point PP;							//current point on object
vector Nf, V;


Nf = faceforward(normalize(N), I);
V = - normalize(I);

surface_color = color(.3, .3, .3);
surface_opac = Os;
surface_mag = 0;



layer_mag = 0;
PP = transform ("shader", P);

float s;
float scale = 1;
float rough = .5;
float i;
for (i = 0; i < iter; i++) {
	layer_mag += snoise(seed + PP * scale) / scale;
	scale /= rough;
}
if (layer_mag > seaLevel) {
	surface_mag += layer_mag;
	
	float latitude = abs (ycomp (normalize(PP))) * .5 + layer_mag / (1 + Km);
	//layer_color = color(0, 1, 0);
	layer_color = spline(length(latitude), color(.5, .4, .2),
							color(.5, .4, .2),
							color(.2, .4, 0),
							color(.1, .4, .1),
							color(0, .5, .1),
							color(.4, .45, .38),
							color(.6, .57, .61),
							color(1, 1, 1),
							color(1, 1, 1));
							
	surface_color = specularcolor * 0.08 * specular(Nf, V, roughness);
} else {
	//layer_mag *= Km;
	//layer_mag = max(layer_mag, - (1 + Km));
	layer_color = color(.1,.2,.5) * (1 + layer_mag - seaLevel);
	
	surface_color = specularcolor * 0.2 * specular(Nf, V, roughness);
}



						
surface_color += layer_color * (Ka * ambient() + Kd * diffuse(Nf));









/* Output */
Oi = surface_opac;
Ci = surface_color * surface_opac;
}