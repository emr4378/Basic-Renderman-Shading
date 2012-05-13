#include "rmannotes.sl"

surface 
EdPhong (float Ka = 0.8, Kd = 0.7, Ks = .2, roughness = 0.1;
		color specularcolor = 1;) 
{
color surface_color;
color surface_opac;
vector Nf, V;


Nf = faceforward(normalize(N), I);
V = - normalize(I);

surface_color = color(.3, .3, .3);
surface_opac = Os;
					
surface_color = surface_color * (Ka * ambient() + Kd * diffuse(Nf))
				+ specularcolor * Ks * specular(Nf, V, roughness);


/* Output */
Oi = surface_opac;
Ci = surface_color * surface_opac;
}