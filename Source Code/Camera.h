#pragma once

#include "OpenGL.h"

class Camera
{
public:
	Camera();
	~Camera();

	int GetCamWidth() const   { return width; };
	int GetCamHeight() const  { return height; };
	void SetCamWidth(int w)   { width = w; };
	void SetCamHeight(int h)  { height = h; };

	int GetCamCenterX() const		{ return centerX; };
	int GetCamCenterY() const		{ return centerY; };
	void SetCamCenter(int x, int y) { centerX = x; centerY = y; };

	int GetCamTopLeftX() const { return centerX - width / 2; };
	int GetCamTopLeftY() const { return centerY - height / 2; };

	float GetZoom()	const	{ return worldPosX; };
	void  SetZoom(float z)  { zoom = z; };

	float GetRotation() const   { return rotation;  };
	void SetRotation(float rot) { rotation = rot;  };

	void MoveCam(int x, int y) { centerX = centerX + x; centerY = centerY + y; };

private:

	MAT2 transformMatrix;

	int centerX, centerY;

	int width, height;
	int worldPosX, WorldPosY;

	float zoom, rotation;
};

