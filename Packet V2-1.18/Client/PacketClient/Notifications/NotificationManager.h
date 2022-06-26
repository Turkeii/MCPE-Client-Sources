#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <set>
#include <string>

struct NotificationData {
	std::string title;
	std::string message;

	float duration = 0.f;
	bool isOpen = true;

	// wtf is this aids
	float fadeTarget = 1;
	float fadeVal = 0;

	NotificationData(std::string title, std::string message) : title(title), message(message) {};

	float fade() {
		fadeVal = fadeTarget - ((fadeTarget - fadeVal) * 0.65f);
		if (fadeTarget == 0 && fadeVal < 0.001f)
			isOpen = false;
		return true;
	}
};

class NotificationManager {
private:
	std::vector<std::shared_ptr<NotificationData>> notificationQueue;
public:
	std::shared_ptr<NotificationData> getFresh() {
		while (!this->notificationQueue.empty()) {
			auto state = this->notificationQueue.front();
			if (!state->isOpen) {
				this->notificationQueue.erase(this->notificationQueue.begin());
				continue;
			}
			return state;
		}
		return std::shared_ptr<NotificationData>();
	}

	inline std::vector<std::shared_ptr<NotificationData>>& getList() {
		while (!this->notificationQueue.empty()) {
			auto box = this->notificationQueue.front();
			if (!box->isOpen) {
				this->notificationQueue.erase(this->notificationQueue.begin());
				continue;
			}
			break;
		}
		return this->notificationQueue;
	}

	inline std::shared_ptr<NotificationData> addNotification(std::string title, std::string message) {
		auto notification = std::make_shared<NotificationData>(title, message);
		this->notificationQueue.push_back(notification);
		return notification;
	}
};