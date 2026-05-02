#include "AssetPanel.hpp"

AssetPanel::AssetPanel(Scene* scene) : scene_(scene) {
	assetPanelTitle_.pos = { 0.0f, 1.0f - (1.0f / 4.0f) };
	assetPanelTitle_.scale = { 1.0f, 1.0f / 4.0f };

	assetPanelContext_.viewportX = 0;
	assetPanelContext_.viewportY = 0;
	assetPanelContext_.viewportWidth = OBJECTS_PANEL_W;
	assetPanelContext_.viewportHeight = OBJECTS_PANEL_H;
	assetPanelContext_.scrollOffsetX = 0.0f;
	assetPanelContext_.scrollOffsetY = 0.0f;
	assetPanelContext_.orthoLeft = -1.0f;
	assetPanelContext_.orthoRight = 1.0f;
	assetPanelContext_.orthoBottom = -1.0f;
	assetPanelContext_.orthoTop = 1.0f;

	const std::vector<std::string>& factoryOptions = AssetFactory::getInstance().getFactoryOptions();

	float areaOffset = ((1.0f / 4.0f) * 2);
	ViewportArea startArea = assetPanelTitle_;
	startArea.pos.y -= areaOffset;
	int i = 0;

	ColorRGB color1 = { 1.0f, 1.0f, 1.0f };
	ColorRGB color2 = { 0.8f, 0.8f, 0.8f };
	ColorRGB colors[2] = { color1, color2 };

	for (auto itr = factoryOptions.begin(); itr != factoryOptions.end(); ++itr) {
		assetButtons_.push_back(
			AssetButton(
				startArea,
				colors[i % 2],
				factoryOptions[i],
				AssetFactory::getInstance().getOptionPreviewSprite(factoryOptions[i])
			)
		);
		startArea.pos.y -= areaOffset;
		++i;
	}
}

void AssetPanel::draw() const {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(
		assetPanelContext_.orthoLeft,
		assetPanelContext_.orthoRight,
		assetPanelContext_.orthoBottom,
		assetPanelContext_.orthoTop,
		-1.0,
		1.0
	);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(
		assetPanelContext_.viewportX,
		assetPanelContext_.viewportY,
		assetPanelContext_.viewportWidth,
		assetPanelContext_.viewportHeight
	);

	// Draw Background
	drawRectangle(
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		0.0f,
		false,
		false,
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f }
	);

	glPushMatrix();
	glTranslatef(0, -assetPanelContext_.scrollOffsetY, 0);

	// Draw Asset Panel Buttons
	for (const auto& button : assetButtons_) {
		button.draw();
	}

	glPopMatrix();
	
	// Draw Title
	drawRectangle(
		assetPanelTitle_.pos,
		assetPanelTitle_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ assetPanelTitle_.pos.x - assetPanelTitle_.scale.x, assetPanelTitle_.pos.y },
		"Assets",
		0.0f,
		{ 1.0f, 1.0f, 1.0f }
	);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void AssetPanel::update(
	std::vector<std::unique_ptr<GameObject2D>>* hierarchyObjects_,
	GameObject2D* parentOfCurrentView,
	const std::function<void(int, GameObject2D*)>& onAssetCreated
) {
	// Dont bother doing input if we arent in hierarchy panel
	if (isInsideViewportContext(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), assetPanelContext_)) {
		float scrollSpeed = 0.1f;

		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLDOWN)) {
			assetPanelContext_.scrollOffsetY -= scrollSpeed;
		}
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLUP)) {
			assetPanelContext_.scrollOffsetY += scrollSpeed;
		}

		if (assetPanelContext_.scrollOffsetY > 0.0f) {
			assetPanelContext_.scrollOffsetY = 0.0f;
		}

		// Handle Clicking
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
			for (int i = 0; i < static_cast<int>(assetButtons_.size()); ++i) {
				auto& button = assetButtons_[i];
				std::unique_ptr<GameObject2D> temp = std::move(button.handleClick(assetPanelContext_));
				if (temp) {
					if (parentOfCurrentView == nullptr) {
						scene_->addRootGameObject2D(std::move(temp));
						scene_->getRootObjects()->back()->updateWorldTransform();
					}
					else {
						parentOfCurrentView->attachChild(std::move(temp));
						parentOfCurrentView->getChildren()->back()->updateWorldTransform();
					}

					if (onAssetCreated) {
						onAssetCreated(i, parentOfCurrentView);
					}
				}
				else {
					continue;
				}
			}
		}
	}
}

void AssetPanel::resetView() {
	assetPanelContext_.scrollOffsetX = 0.0f;
	assetPanelContext_.scrollOffsetY = 0.0f;
}