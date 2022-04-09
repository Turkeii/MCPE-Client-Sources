#include "Bhop.h"

void Bhop::onMove(C_MoveInputHandler* input) {
	cachedInput = *input;
	yes = input;
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr)
		return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	static auto Flight = moduleMgr->getModule<HiveFly>();

	if (hive) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};

		if (pressed && !Flight->isEnabled()) {
			player->setSprinting(true);
			if (player->onGround) {
				player->jumpFromGround();
			}
			C_MovePlayerPacket mpp(player, *player->getPos());
			mpp.onGround = player->onGround;
			mpp.pitch += 0.5f;
			mpp.yaw += 0.5f;
			mpp.headYaw += 0.5f;
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
			if (player->onGround)
				speedIndexThingyForHive = 0;
			float currentSpeed = epicHiveSpeedArrayThingy[speedIndexThingyForHive] * 0.9;
			moveVec.x = moveVec2d.x * currentSpeed;
			moveVec.y = player->velocity.y;
			moveVec.z = moveVec2d.y * currentSpeed;
			player->lerpMotion(moveVec);
			if (speedIndexThingyForHive < 30)
				speedIndexThingyForHive++;
		}
	} else {
		if (player->onGround && pressed && !Flight->isEnabled())
			player->jumpFromGround();
		float calcYaw = (player->yaw + 90) * (PI / 180);
		vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed && !Flight->isEnabled())
			player->lerpMotion(moveVec);
	}
}