#include "./includes.h"
#include <Geode/modify/MenuLayer.hpp>

class TimeLabelNode : public CCLabelBMFont {
	SYSTEMTIME time;

	virtual bool init() {
		if (!CCLabelBMFont::initWithString("", "bigFont.fnt")) return false;
		updateLabel(0);
		schedule(schedule_selector(TimeLabelNode::updateLabel), 1);
		return true;
	}

	void updateLabel(float dt) {
		GetLocalTime(&time);
		setString((
				(int(time.wHour) < 10 ? "0" + std::to_string(time.wHour) : std::to_string(time.wHour)) + ":" +
				(int(time.wMinute) < 10 ? "0" + std::to_string(time.wMinute) : std::to_string(time.wMinute)) + ":" +
				(int(time.wSecond) < 10 ? "0" + std::to_string(time.wSecond) : std::to_string(time.wSecond))
			).c_str());
	}
public:
	static TimeLabelNode* create() {
		auto ret = new TimeLabelNode();
		if (ret && ret->init()) {
			ret->autorelease();
			return ret;
		}
		delete ret;
		return nullptr;
	}
};

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto timeLabel = TimeLabelNode::create();
		timeLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height });
		timeLabel->setAnchorPoint({ 1.1,1.1 });
		timeLabel->setScale(0.5);
		this->addChild(timeLabel);
		return 1;
	}
};