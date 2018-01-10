#include "Ground.h"

const float NORAML[3] = {0, 1, 0, };
const float COLOR[3] = {0.1, 0.4, 0.6, };
const float GROUND_COORDS[4][3] = {
	{ 100, 0, 100, },
	{ 100, 0, -100, },
	{ -100, 0, -100, },
	{ -100, 0, 100 },
};

void CGround::Update(GLdouble time) {}

void CGround::Render() {
	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; ++ i) {
		glColor3fv(COLOR);
		glNormal3fv(NORAML);
		glVertex3fv(GROUND_COORDS[i]);
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3fv(COLOR);
	glVertex3f(0, 0, 0);
	glColor3fv(COLOR);
	glVertex3f(0, 100, 0);
	glEnd();
	//glEnable(GL_TEXTURE_2D);
}