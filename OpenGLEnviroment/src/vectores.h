#ifndef _vect_R_
#define _vect_R_

#include <math.h>

#define PI 3.1416
#define DEG2RAD 3.141593f / 180

class Vector
{
public:
	float x;
	float y;
	float z;
	float teta, phi;

	enum Ejes{EjeX, EjeY, EjeZ};
	enum angulos{TETA,PHI};

public:
	Vector();

	Vector(float* vec);
		
	Vector(float X, float Y, float Z);

	~Vector();

	Vector operator *(Vector& vec);

	Vector operator *(float vec);

	Vector operator +(Vector& vec);

	Vector *operator +(Vector* vec);

	Vector *operator +=(Vector* vec);

	Vector *operator -=(Vector* vec);

	Vector operator +=(Vector& vec);

	Vector operator =(Vector& v2);

	Vector& operator =(float *vec);

	Vector& operator -(float *vec);
		
	Vector operator -(Vector& vec);
		
	void set_start_angle(float Teta, float Phi);
		
	void rotacion(angulos eje, float grados, float radio);
		
	float distancia_puntos3D(Vector a, Vector b);
		
	float distancia_puntos3D(float *a, float *b);
		
	float punto(Vector v1, Vector v2);
		
	Vector cruz(Vector v1, Vector v2);
		
	Vector genNormal(float *v1, float *v2, float *v3);
	
	void normaliza();

	void normaliza(Vector *v);

	Vector normaliza(Vector v);
		
	void normaliza(float *v);
		
	void sumaVec(Vector *v1, Vector *v2);
		
	void sumaVec(float *v1, float *v2);

	float clampnum(float num, float min, float max);

	void invierteNormales(float *coord);
};

#endif