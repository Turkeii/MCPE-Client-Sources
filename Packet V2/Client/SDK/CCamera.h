#pragma once

#include "../Utils/HMath.h"

class C_Camera {
private:
	char pad_0000[128];  //0x0000
public:
	bool renderPlayerModel;         //0x0080
	bool renderFirstPersonObjects;  //0x0081
private:
	char pad_0082[26];  //0x0082
public:
	float fov;                //0x009C
	float nearClippingPlane;  //0x00A0
	float farClippingPlane;   //0x00A4
private:
	char pad_00A8[104];  //0x00A8
public:
	bool facesPlayerFront;  //0x0110

	void getForwardVector(vec3_t*);
	void getEulerAngles(vec3_t*);
	void getPlayerRotation(vec2_t*);
	void setOrientation(float pitch, float yaw, float roll);
	void setOrientationDeg(float pitch, float yaw, float roll) {
		setOrientation((-yaw - 180) * RAD_DEG, -pitch * RAD_DEG, roll * RAD_DEG);
	}
};

class C_CameraManager {
public:
	C_Camera* getCameraOrDebugCamera();
};