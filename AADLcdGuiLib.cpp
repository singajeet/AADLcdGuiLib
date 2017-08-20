// Do not remove the include below
#include "AADLcdGuiLib.h"


int GUIObject::getBgColor() const {
	return _bgColor;
}

void GUIObject::setBgColor(int bgColor) {
	_bgColor = bgColor;
}

int GUIObject::getFgColor() const {
	return _fgColor;
}

void GUIObject::setFgColor(int fgColor) {
	_fgColor = fgColor;
}

byte GUIObject::getId() const {
	return _id;
}

byte RawPanel::getBorder() const {
	return _border;
}

void RawPanel::setBorder(byte border) {
	_border = border;
}

int RawPanel::getBorderColor() const {
	return _borderColor;
}

void RawPanel::setBorderColor(int borderColor) {
	_borderColor = borderColor;
}

byte RawPanel::getBorderType() const {
	return _borderType;
}

void RawPanel::setBorderType(byte borderType) {
	_borderType = borderType;
}

byte RawPanel::getHeight() const {
	return _height;
}

void RawPanel::setHeight(byte height) {
	_height = height;
}

byte RawPanel::getPanelId() const {
	return _panelId;
}

byte RawPanel::getWidth() const {
	return _width;
}

void RawPanel::setWidth(byte width) {
	_width = width;
}

byte RawPanel::getX() const {
	return _x;
}

void RawPanel::setX(byte x) {
	_x = x;
}

byte RawPanel::getY() const {
	return _y;
}

void RawPanel::setY(byte y) {
	_y = y;
}

const AADFonts*& RawPanel::getDefaultFont() const {
	return _defaultFont;
}

void RawPanel::setDefaultFont(const AADFonts*& defaultFont) {
	_defaultFont = defaultFont;
}

int* RawPanel::getPanelBgPixelMap() const {
	return _bgPixelMap;
}

const String*& TitlePanel::getTitle() const {
	return _title;
}

void TitlePanel::setTitle(const String*& title) {
	_title = title;
}


