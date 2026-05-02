#ifndef I_FIELD_BUTTON_HPP
#define I_FIELD_BUTTON_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <iostream>

#include "WindowConstants.hpp"
#include "DrawFunctions.hpp"
#include "VoidButton.hpp"
#include "InputManager.hpp"
#include "IField.hpp"

// Universal IFieldButtonBase
class IFieldButton {
public:
	IFieldButton();

	virtual ~IFieldButton() = default;

	const ViewportArea& getViewportArea() const { return viewportArea_; }
	virtual bool handleClick(const ViewportContext& context) = 0;
	virtual void handleKeyInput(const std::string& typedChars) {}
	virtual void draw() const = 0;

protected:
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string name_;
};

// bool IFieldButton
class BoolIFieldButton : public IFieldButton {
public:
	BoolIFieldButton();
	BoolIFieldButton(
		ViewportArea viewportArea,
		ColorRGB color,
		const std::string& name,
		BoolField* field
	);

	void draw() const override final;
	bool handleClick(const ViewportContext& context) override final;
	bool isInsideButton(int mouseX, int mouseY, const ViewportContext& context) const;

	// Handle click 
	// if inside buttonArea_ -> field->setValue(!field->getValue);
private:
	ViewportArea buttonArea_;
	
	BoolField* field_;
};

// int, char, float, std::string will derive
class TextEntryIFieldButton : public IFieldButton {
public:
	TextEntryIFieldButton();

	void draw() const override = 0;
	bool handleClick(const ViewportContext& context) override = 0;

	bool clickedTextEntryArea() const { return clickedTextEntryArea_; }
	void appendToBuffer(std::string newCharacters);
	void handleKeyPress(unsigned char key);
	void handleKeyInput(const std::string& typedChars) override;
	bool isInsideTextEntry(int mouseX, int mouseY, const ViewportContext& context) const;
	bool isInsideButton(int mouseX, int mouseY, const ViewportContext& context) const;

	// Inspector View
	// TextEntryIFieldButton* verify = dynamic_cast<TextEntryIFieldButton>(button;
	// if(verify)
	//		if verify->clickedTextEntryArea()
	//			verify->appendToBuffer(InputManager::getInstance().getBufferAdditions);

protected:
	TextEntryIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& name
	);

	// Automatically calculated based on viewportArea
	ViewportArea textEntryArea_;
	ViewportArea buttonArea_;
	std::string entryBuffer_;
	bool clickedTextEntryArea_;
};

// int
class IntIFieldButton : public TextEntryIFieldButton {
public:
	IntIFieldButton();
	IntIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& name,
		IntField* field
	);

	void draw() const override final;
	bool handleClick(const ViewportContext& context) override final;

	// Handle click
	// if inside buttonArea_ -> field->setValue(string_to_int(entryBuffer_))
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
private:
	IntField* field_;
};

// char
class CharIFieldButton : public TextEntryIFieldButton {
public:
	CharIFieldButton();
	CharIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& name,
		CharField* field
	);

	void draw() const override final;
	bool handleClick(const ViewportContext& context) override final;

	// Handle click
	// if inside buttonArea_ -> field->setValue(entryBuffer_[0]) // Will probably go with that
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
private:
	CharField* field_;
};

// float
class FloatIFieldButton : public TextEntryIFieldButton {
public:
	FloatIFieldButton();
	FloatIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string name,
		FloatField* field
	);

	void draw() const override final;
	bool handleClick(const ViewportContext& context) override final;

	// Handle click
	// if inside buttonArea_ -> field->setValue(string_to_float(entryBuffer_))
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
private:
	FloatField* field_;
};

// string
class StringIFieldButton : public TextEntryIFieldButton {
public:
	StringIFieldButton();
	StringIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& name,
		StringField* field
	);

	void draw() const override final;
	bool handleClick(const ViewportContext& context) override final;

	// Handle click
	// if inside buttonArea_ -> field->setValue(entryBuffer_)
	// else if inside textEntryArea_ -> clickedTextEntryArea_ = true
	// else -> clickedTextEntryArea_ = false
private:
	StringField* field_;
};

// Vector2D
class Vector2DIFieldButton : public IFieldButton {
public:
	Vector2DIFieldButton();
	Vector2DIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string name,
		Vector2DField* field
	);

	bool handleClick(const ViewportContext& context) override final;
	void handleKeyInput(const std::string& typedChars) override final;
	void draw() const override final;

	// Handle click
	// x_->handleClick();
	// y_->handleClick();

	// Draw
	// draw name
	// draw x_
	// draw y_
private:
	FloatIFieldButton x_;
	FloatIFieldButton y_;
};

// Transform2D
class Transform2DIFieldButton : public IFieldButton {
public:
	Transform2DIFieldButton();
	Transform2DIFieldButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& name,
		Transform2DField* field
	);

	bool handleClick(const ViewportContext& context) override final;
	void handleKeyInput(const std::string& typedChars) override final;
	void draw() const override final;

	// Handle click
	// if inside buttonArea_
	//		pos_->handleClick();
	//		scale_->handleClick();
	//		...

	// Draw
	// draw name
	// draw pos_
	// draw scale_
	// ...
private:
	Vector2DIFieldButton pos_;
	Vector2DIFieldButton scale_;
	FloatIFieldButton rotation_;
	BoolIFieldButton mirror_;
	BoolIFieldButton flip_;
};


#endif