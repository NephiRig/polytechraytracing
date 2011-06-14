/*
 * Material.h
 *
 *  Created on: 01.06.2011
 *      Author: nb-gyglim
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

class Material {
public:
	Material(double k_a = 0, double k_d = 0, double k_s = 0, double n_s = 0, double k_reflex =0);
	virtual ~Material();

	double k_a, k_d, k_s, n_s, k_reflex;
	// k_a: ambiant
	// k_d: diffuse
	
};

#endif /* MATERIAL_H_ */
