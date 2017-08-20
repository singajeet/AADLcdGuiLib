// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _AADLcdGuiLib_H_
#define _AADLcdGuiLib_H_
#include "Arduino.h"
#include <AADFontsLib.h>
//add your includes for the project AADLcdGuiLib here

class GUIObject{
	private:
		byte _id;
		int _bgColor;
		int _fgColor;
		
	public:
		GUIObject();
		GUIObject(int bgColor, int fgColor);
		virtual int getBgColor() const;
		virtual void setBgColor(int bgColor);
		virtual int getFgColor() const;
		virtual void setFgColor(int fgColor);
		virtual byte getId() const;
		virtual void draw(void);
		virtual void show(void);
		virtual void hide(void);
		virtual void move_to(byte x, byte y);
		virtual void resize_to(byte x, byte y);

		virtual ~GUIObject(){}
};

class RawPanel : public GUIObject {
	private:
		byte _panelId;
		byte _x;
		byte _y;
		byte _height;
		byte _width;
		byte _border;
		byte _borderType;
		int _borderColor;
		AADFonts* _defaultFont;
		int* _bgPixelMap;

		virtual void _initPixelMap(void);
		
	public:
		RawPanel(byte x, byte y, byte height, byte width);
		virtual byte getBorder() const;
		virtual void setBorder(byte border);
		virtual int getBorderColor() const;
		virtual void setBorderColor(int borderColor);
		virtual byte getBorderType() const;
		virtual void setBorderType(byte borderType);
		virtual byte getHeight() const;
		virtual void setHeight(byte height);
		virtual byte getPanelId() const;
		virtual byte getWidth() const;
		virtual void setWidth(byte width);
		virtual byte getX() const;
		virtual void setX(byte x);
		virtual byte getY() const;
		virtual void setY(byte y);
		virtual const AADFonts*& getDefaultFont() const;
		virtual void setDefaultFont(const AADFonts*& defaultFont);
		virtual int* getPanelBgPixelMap() const;
};

class TitlePanel : public RawPanel{
	private:
		String* _title;

	public:
		TitlePanel(byte x, byte y, byte height, byte width, String* title);
		virtual const String*& getTitle() const;
		virtual void setTitle(const String*& title);
};

class Widget : public RawPanel{
	private:
		byte _widgetId;
};

class Panel : public RawPanel{
	private:
		TitlePanel* _titlePanel;
		byte _level;
		Widget* _widgets[];
		byte _widgetCounter;

	public:
		Panel(byte x, byte y, byte height, byte width);
		Panel(byte x, byte y, byte height, byte width, String* title);
		virtual void setTitle(String* title);
		virtual byte getLevel(void);
		virtual void setLevel(byte level);
		virtual void add(Widget* widget);
		virtual void remove(Widget* widget);
		virtual Widget* findWidget(int widgetId);
		virtual void refresh(void);
};

class DesktopPane : public RawPanel{
	private:
		int* _displayPixelMap;
		Panel* _panels[];
		byte _panelCounter = 0;
		byte _maxWidth = 161;
		byte _maxHeight = 131;

	public:
		DesktopPane();
		virtual int* getDesktopPixelMapFor(byte x, byte y, byte height, byte width);
		virtual void add(Panel* panel);
		virtual void remove(Panel* panel);
		virtual Panel* findPanel(int panelId);
		virtual void refresh(void);
};


class Image : public Widget{
	private:
		int* _imageMap;
		String* _imageFileName;
		String* _imageFilePath;

	public:
		Image(String* imageFileName, String* imageFilePath);

};

//Do not add code below this line
#endif /* _AADLcdGuiLib_H_ */
