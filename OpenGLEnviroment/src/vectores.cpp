#include "Vectores.h"

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(float* vec)
{
	x = vec[0];
	y = vec[1];
	z = vec[2];
}

Vector::Vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vector::~Vector()
{
}

Vector Vector::operator *(Vector& vec)
{
	Vector temp;
	temp.x = x * vec.x;
	temp.y = y * vec.y;
	temp.z = z * vec.z;
	return temp;
}

Vector Vector::operator *(float vec)
{
	Vector temp;
	temp.x = x * vec;
	temp.y = y * vec;
	temp.z = z * vec;
	return temp;
}

Vector Vector::operator +(Vector& vec)
{
	Vector temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	temp.z = z + vec.z;
	return temp;
}

Vector *Vector::operator +(Vector* vec)
{
	x+vec->x;
	y+vec->y;
	z+vec->z;

	return this;
}

Vector *Vector::operator +=(Vector* vec)
{
	x+=vec->x;
	y+=vec->y;
	z+=vec->z;

	return this;
}

Vector *Vector::operator -=(Vector* vec)
{
	x-=vec->x;
	y-=vec->y;
	z-=vec->z;

	return this;
}

Vector Vector::operator +=(Vector& vec)
{
	x+=vec.x;
	y+=vec.y;
	z+=vec.z;

	return *this;
}

Vector Vector::operator =(Vector& v2)
{
	x=v2.x;
	y=v2.y;
	z=v2.z;

	return *this;
}

Vector& Vector::operator =(float *vec)
{
	x=vec[0];
	y=vec[1];
	z=vec[2];
	return *this;
}

Vector& Vector::operator -(float *vec)
{
	x-=vec[0];
	y-=vec[1];
	z-=vec[2];
	return *this;
}

Vector Vector::operator -(Vector& vec)
{
	Vector temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	temp.z = z - vec.z;
	return temp;
}

void Vector::set_start_angle(float Teta, float Phi)
{
	teta = Teta;
	phi = Phi;
}

void Vector::rotacion(angulos eje, float grados, float radio)
{
	switch (eje)
	{
	case angulos::PHI:
		{
			float diferencia = 0;
			bool calculado = false;

			if(phi+grados < 0)
			{
				diferencia = grados-(359-phi);
				phi = 359-diferencia;
				calculado = true;
			}
			if(phi+grados > 359)
			{
				diferencia = grados-(359-phi);
				phi = 0+diferencia;
				calculado = true;
			}
			if(!calculado)
				phi += grados;

			x = (radio)*((float) sin((teta)*(PI/180)))*((float)sin((phi)*(PI/180)));
			y = (radio)*((float) cos((teta)*(PI/180)));
			z = (radio)*((float) sin((teta)*(PI/180)))*((float)cos((phi)*(PI/180)));
			break;
		}
	case angulos::TETA:
		{
			float diferencia = 0;
			bool calculado = false;

			if(teta+grados < 0)
			{
				diferencia = grados-(179-teta);
				teta = 0+diferencia;
				calculado = true;
			}
			if(teta+grados > 179)
			{
				diferencia = grados-(179-teta);
				teta = 179-diferencia;
				calculado = true;
			}
			if(!calculado)
				teta += grados;

			x = (radio)*((float) sin((teta)*(PI/180)))*((float)sin((phi)*(PI/180)));
			y = (radio)*((float) cos((teta)*(PI/180)));
			z = (radio)*((float) sin((teta)*(PI/180)))*((float)cos((phi)*(PI/180)));
			break;
		}
	default:
		break;
	}
}

float Vector::distancia_puntos3D(Vector a, Vector b)
{
	float dist = sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2)+pow(b.z-a.z,2));
	return dist;
}

float Vector::distancia_puntos3D(float *a, float *b)
{
	float dist = sqrt(pow(b[0]-a[0],2)+pow(b[1]-a[1],2)+pow(b[2]-a[2],2));
	return dist;
}

float Vector::punto(Vector v1, Vector v2)
{
	float resul = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return resul;
}

Vector Vector::cruz(Vector v1, Vector v2)
{
	Vector temp;

	temp.x = v1.y * v2.z - v1.z * v2.y;
	temp.y = v1.z * v2.x - v1.x * v2.z;
	temp.z = v1.x * v2.y - v1.y * v2.x;

	return temp;
}

Vector Vector::genNormal(float *v1, float *v2, float *v3)
{
	Vector vec1, vec2;

	vec1.x = *v2 - *v1;
	vec1.y = *( v2 + 1 ) - *( v1 + 1 );
	vec1.z = *( v2 + 2 ) - *( v1 + 2 );

	vec2.x = *v3 - *v1;
	vec2.y = *( v3 + 1 ) - *( v1 + 1 );
	vec2.z = *( v3 + 2 ) - *( v1 + 2 );

	return cruz( vec1, vec2 );
}

void Vector::normaliza()
{
	float maginitud = sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z));
	this->x /= maginitud;
	this->y /= maginitud;
	this->z /= maginitud;
}

void Vector::normaliza(Vector *v)
{
	float maginitud = sqrt((v->x*v->x) + (v->y*v->y) + (v->z*v->z));
	v->x /= maginitud;
	v->y /= maginitud;
	v->z /= maginitud;
}

Vector Vector::normaliza(Vector v)
{
	float maginitud = sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
	v.x /= maginitud;
	v.y /= maginitud;
	v.z /= maginitud;
	return v;
}

void Vector::normaliza(float *v)
{
	float maginitud = sqrt((v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2]));
	v[0] /= maginitud;
	v[1] /= maginitud;
	v[2] /= maginitud;
}

void Vector::sumaVec(Vector *v1, Vector *v2)
{
	v1->x+=v2->x;
	v1->y+=v2->y;
	v1->z+=v2->z;
}

void Vector::sumaVec(float *v1, float *v2)
{
	v1[0]+=v2[0];
	v1[1]+=v2[1];
	v1[2]+=v2[2];
}

float Vector::clampnum(float num, float min, float max)
{
	if(num < min)
		num = min;
	else
	{
		if(num > max)
			num = max;
	}
	return num;
}

void Vector::invierteNormales(float *coord)
{
	coord[0] = coord[0]*(-1);
	coord[1] = coord[1]*(-1);
	coord[2] = coord[2]*(-1);
}

