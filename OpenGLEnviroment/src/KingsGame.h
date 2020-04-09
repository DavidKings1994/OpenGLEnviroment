#ifndef _KINGS_GAME_H_
#define _KINGS_GAME_H_

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "vectores.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace KingsGame
{
	namespace Geometry
	{
		struct Vertex
		{
			Vector vertex;
			Vector normal;
			Vector uv;
			Vector color;
		};

		struct Mesh
		{
			Vertex *mesh;
			unsigned int *index;
		};

		static class Meshes
		{
		public:
			static void drawCube(float size) {

				glScalef(size, size, size);

				glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
				// Top face (y = 1.0f)
				// Define vertices in counter-clockwise (CCW) order with normal pointing out
				glNormal3f(0, 1, 0);
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);

				// Bottom face (y = -1.0f)
				glNormal3f(0, -1, 0);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);

				// Front face  (z = 1.0f)
				glNormal3f(0, 0, 1);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);

				// Back face (z = -1.0f)
				glNormal3f(0, 0, -1);
				glVertex3f(1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);

				// Left face (x = -1.0f)
				glNormal3f(-1, 0, 0);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);

				// Right face (x = 1.0f)
				glNormal3f(1, 0, 0);				
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
				glEnd();  // End of drawing color-cube
			}

			static void drawPiramid(float size) {

				glScalef(size, size, size);

				glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
				// Front
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);

				// Right
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);

				// Back
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);

				// Left
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glEnd();   // Done drawing the pyramid
			}
		};
	};

	namespace Objects
	{
		class GameObject
		{
		private:
			Vector *position;
			float modelHeight;
			float scale;

		public:
			GameObject(Vector *position, char modelPath[], WCHAR texturePath[], float scale)
			{
				this->modelHeight = 0.5;
				this->scale = scale;
				this->position = position;
			}

			~GameObject()
			{
			}

			void draw()
			{
				glPushMatrix();
				glTranslatef(position->x, position->y + modelHeight, position->z);
				glScalef(scale,scale,scale);
				glPopMatrix();

			}

			float getModelHeight()
			{
				return modelHeight;
			}

			void setModelHeight(float modelHeight)
			{
				this->modelHeight = modelHeight;
			}

			Vector *getPosition()
			{
				return this->position;
			}

			void setPosition(Vector *position)
			{
				this->position = position;
			}
		};
	};

	class Terrain
	{
	private:
		Geometry::Vertex *vertex;
		float width;
		float height;
		int tile;

		void loadHeightMap()
		{
		}

	public:
		Terrain(int height, int width, int tile)
		{
			this->height = height;
			this->width = width;
			this->tile = tile;
		}

		~Terrain()
		{
		}

		void draw()
		{
			float x = width / 2;
			float z = height / 2;

			glBegin(GL_QUADS);
			glColor3f(0, 1, 0);
			glNormal3f(0, 1, 0);
			//glTexCoord2f(0,0);
			glVertex3f(-x, 0, -z);
			//glTexCoord2f(tile,0);
			glVertex3f(x, 0, -z);
			//glTexCoord2f(tile,tile);
			glVertex3f(x, 0, z);
			//glTexCoord2f(0,tile);
			glVertex3f(-x, 0, z);
			glEnd();
		}
	};

	class SkyCamera
	{
	public:
		enum STATE {IDLE, ZOOMING};

	private:
		Vector *position;
		Vector *direction;
		int zoom;
		float speed;
		STATE state;
		bool thirdPerson;

	public:
		SkyCamera(Vector *position, Vector *direction)
		{
			this->position = position;
			this->direction = direction;
			this->zoom = 1;
			this->speed = 1;
			this->thirdPerson = false;
		}

		~SkyCamera()
		{
		}

		void update()
		{
			switch(zoom)
			{
			case 3:
				{
					if(this->position->y > 5)
					{
						this->position->operator+=(this->direction);
					}
					else
						this->state = IDLE;
					break;
				}
			case 2:
				{
					if(this->position->y > 10)
					{
						this->position->operator+=(this->direction);
					}
					else if(this->position->y < 10)
					{
						this->position->operator-=(this->direction);
					}
					else
						this->state = IDLE;
					break;
				}
			case 1:
				{
					if(this->position->y < 25)
					{
						this->position->operator-=(this->direction);
					}
					else
						this->state = IDLE;
					break;
				}
			}
		}

		void placeCamera()
		{
			gluLookAt(
				position->x, 
				position->y, 
				position->z, 
				position->x + direction->x, 
				position->y + direction->y, 
				position->z + direction->z, 
				0, 1, 0);
		}

		void smoothFollowPoint(Vector *point)
		{
			int maxDistance;
			int distance;
			switch(zoom)
			{
			case 1:
				{
					distance = 20;
					maxDistance = 10;
					break;
				}
			case 2:
				{
					distance = 10;
					maxDistance = 6;
					break;
				}
			case 3:
				{
					distance = 5;
					maxDistance = 3;
					break;
				}
			}
			if(point->x > this->getPosition()->x + maxDistance)
			{
				moveRight();
			}
			if(point->x < this->getPosition()->x - maxDistance)
			{
				moveLeft();
			}
			if(point->z + distance > this->getPosition()->z + maxDistance - 2)
			{
				moveDown();
			}
			if(point->z + distance < this->getPosition()->z - maxDistance + 2)
			{
				moveUp();
			}
		}

		void zoomIn()
		{
			if(this->state == IDLE)
			{
				if(zoom < 3)
				{
					zoom++;
					this->state = ZOOMING;
				}
			}
		}

		void zoomOut()
		{
			if(this->state == IDLE)
			{
				if(zoom > 1)
				{
					zoom--;
					this->state = ZOOMING;
				}
			}
		}

		void moveUp()
		{
			this->position->z -= speed;
		}

		void moveDown()
		{
			this->position->z += speed;
		}

		void moveRight()
		{
			this->position->x += speed;
		}

		void moveLeft()
		{
			this->position->x -= speed;
		}

		int getZoom()
		{
			return this->zoom;
		}

		void setSpeed(float speed)
		{
			this->speed = speed;
		}

		float getSpeed()
		{
			return this->speed;
		}

		Vector *getPosition()
		{
			return this->position;
		}

		STATE getState()
		{
			return this->state;
		}

		void setState(STATE state)
		{
			this->state = state;
		}
	};

	class Game
	{
	private:
		Terrain *field;
		SkyCamera* camera;
		bool paused;
		float rot = 0;

		void setObstacles()
		{
			for(int i = 0; i < 10; i++)
			{
				int x = rand()%29;
				int y = rand()%29;
			}
		}

	public:
		Game()
		{
			reshape(1000,800);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
			glClearDepth(1.0f);                   // Set background depth to farthest
			glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
			glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
			glShadeModel(GL_SMOOTH);   // Enable smooth shading
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

			//glEnable(GL_NORMALIZE);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_COLOR_MATERIAL);
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_LIGHT_MODEL_LOCAL_VIEWER);

			paused = false;
			field = new Terrain(50, 50, 25);
			camera = new SkyCamera(new Vector(0, 0, 0), new Vector(0, 0, -1));
		}

		~Game()
		{
		}

		void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
			// Compute aspect ratio of the new window
			if (height == 0) height = 1;                // To prevent divide by 0
			GLfloat aspect = (GLfloat)width / (GLfloat)height;

			// Set the viewport to cover the new window
			glViewport(0, 0, width, height);

			// Set the aspect ratio of the clipping volume to match the viewport
			glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
			glLoadIdentity();             // Reset
			// Enable perspective projection with fovy, aspect, zNear and zFar
			gluPerspective(45.0f, aspect, 0.1f, 100.0f);
			//glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 100);
		}

		void update()
		{
			camera->update();
			rot += 2;
		}

		void draw()
		{
			//glMatrixMode(GL_PROJECTION);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			//glClearDepth(1.0f);
			glClearColor(1, 1, 1, 0);
			glLoadIdentity();

			GLfloat LightAmb2[] = { 1, 1, 1, 1.0 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb2);
			LightAmb2[0] = 0.2; LightAmb2[1] = 0.2; LightAmb2[2] = 0.2; LightAmb2[3] = 0.0;
			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb2);
			GLfloat LightPos[] = { 400.0, -500.0,10.0, 1.0 };
			glLightfv(GL_LIGHT2, GL_POSITION, LightPos);

			//camera->placeCamera();
			
			glRotatef(rot, 0, 1, 0);
			//glTranslatef(0, 0, 0);

			glPushMatrix();
			glTranslatef(0,-1,0);
			field->draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, 0, 4);
			glRotatef(rot, 1, 1, 0);
			glColor3f(0.0f, 0.0f, 1.0f);     // Blue
			KingsGame::Geometry::Meshes::drawCube(.5);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, 0, -4);
			glRotatef(rot, 1, 1, 0);
			glColor3f(0.0f, 0.0f, 1.0f);     // Blue
			KingsGame::Geometry::Meshes::drawCube(.5);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(4, 0, 0);
			glRotatef(rot, 1, 1, 0);
			glColor3f(0.0f, 0.0f, 1.0f);     // Blue
			KingsGame::Geometry::Meshes::drawPiramid(.5);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-4, 0, 0);
			glRotatef(rot, 1, 1, 0);
			glColor3f(0.0f, 0.0f, 1.0f);     // Blue
			KingsGame::Geometry::Meshes::drawPiramid(.5);
			glPopMatrix();

			glFlush();
		}

	};
};

#endif