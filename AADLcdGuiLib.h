// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _AADLcdGuiLib_H_
#define _AADLcdGuiLib_H_
#include "Arduino.h"
#include <AADFontsLib.h>
#include <AADColorsLib.h>
#include <AADConfigLib.h>
#include <AADFontsLibDefault8x15.h>
#include <AADDriversInterface.h>
#include <AADNokia1616LCDDriver.h>
//add your includes for the project AADLcdGuiLib here

class GUIObject{
	private:
		byte _id;
		int _bgColor;
		int _fgColor;
		
	public:
		GUIObject();
		GUIObject(int bgColor, int fgColor);
		virtual int getBgColor() ;
		virtual void setBgColor(int bgColor);
		virtual int getFgColor() ;
		virtual void setFgColor(int fgColor);
		virtual byte getId() ;
		virtual void draw(void) = 0;
		virtual void show(void);
		virtual void hide(void);
		virtual void move_to(byte x, byte y);
		virtual void resize_to(byte width, byte height);

		virtual ~GUIObject(){}
};

class DesktopPane;

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
		DesktopPane* _desktopPane;
		
	public:
		RawPanel(byte x, byte y, byte width, byte height);
		virtual byte getBorder();
		virtual void setBorder(byte border);
		virtual int getBorderColor();
		virtual void setBorderColor(int borderColor);
		virtual byte getBorderType();
		virtual void setBorderType(byte borderType);
		virtual byte getHeight();
		virtual void setHeight(byte height);
		virtual byte getPanelId();
		virtual byte getWidth();
		virtual void setWidth(byte width);
		virtual byte getX();
		virtual void setX(byte x);
		virtual byte getY();
		virtual void setY(byte y);
		virtual AADFonts* getDefaultFont();
		virtual void setDefaultFont(AADFonts* defaultFont);
		virtual int* getPanelBgPixelMap();
		virtual void setDesktopPane(DesktopPane* pane);
		virtual void draw(void);
};

class TitlePanel : public RawPanel{
	private:
		String* _title;

	public:
		TitlePanel(byte x, byte y, byte width, byte height, String* title);
		virtual  String* getTitle() ;
		virtual void setTitle( String* title);
		virtual void draw(void);
};

class Panel;

class Widget : public RawPanel{
	private:
		byte _widgetId;
		Panel* _panel;

	public:
		virtual byte getWidgetId(void);
		virtual void setPanel(Panel* panel);
		virtual Panel* getPanel(void);
};

class Panel : public RawPanel{
	private:
		TitlePanel* _titlePanel;
		byte _level;
		Widget* _widgets[];
		byte _widgetCounter;


	public:
		Panel(byte x, byte y, byte width, byte height);
		Panel(byte x, byte y, byte width, byte height, String* title);
		virtual void setTitle(String* title);
		virtual byte getLevel(void);
		virtual void setLevel(byte level);
		virtual void add(Widget* widget);
		virtual void remove(Widget* widget);
		virtual Widget* findWidget(int widgetId);
		virtual void refresh(void);
		virtual void drawWidgets(void);
		virtual void draw(void);
};

class DesktopPane : public RawPanel{
	private:
		int* _displayPixelMap;
		Panel* _panels[];
		byte _panelCounter = 0;
		byte _maxWidth = 161;
		byte _maxHeight = 131;
		AADLCDDriversInterface* _driver;

	public:
		DesktopPane();
		virtual int* getDesktopPixelMapFor(byte x, byte y, byte width, byte height);
		virtual void add(Panel* panel);
		virtual void remove(Panel* panel);
		virtual Panel* findPanel(int panelId);
		virtual void refresh(void);
		virtual AADLCDDriversInterface* getDriver(void);
		virtual void pixel(byte x, byte y, int color);
		virtual void print_char(byte x, byte y, unsigned char c, unsigned int color);
		virtual void print_string(byte x, byte y, char *str, unsigned int color);
		virtual void line(byte x0, byte y0, byte x1, byte y1, unsigned int color);
		virtual void circle(byte x0, byte y0, byte r, unsigned int color);
		virtual void v_line(byte x, byte y, byte h, unsigned int color);
		virtual void h_line(byte x, byte y, byte w, unsigned int color);
		virtual void rectangle(byte x, byte y, byte w, byte h, unsigned int color);
		virtual void fill(byte x, byte y, byte w, byte h, unsigned int color);
		virtual void bitmap(byte x, byte y, const byte *bitmap, byte w, byte h, unsigned int color);
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
