// Do not remove the include below
#include "AADLcdGuiLib.h"


int GUIObject::getBgColor()  {
	return _bgColor;
}

void GUIObject::setBgColor(int bgColor) {
	_bgColor = bgColor;
}

int GUIObject::getFgColor()  {
	return _fgColor;
}

void GUIObject::setFgColor(int fgColor) {
	_fgColor = fgColor;
}

byte GUIObject::getId()  {
	return _id;
}

/***********************************************************************************
 * 		RawPanel class
 ***********************************************************************************/

byte RawPanel::getBorder()  {
	return _border;
}

void RawPanel::setBorder(byte border) {
	_border = border;
}

int RawPanel::getBorderColor()  {
	return _borderColor;
}

void RawPanel::setBorderColor(int borderColor) {
	_borderColor = borderColor;
}

byte RawPanel::getBorderType()  {
	return _borderType;
}

void RawPanel::setBorderType(byte borderType) {
	_borderType = borderType;
}

byte RawPanel::getHeight()  {
	return _height;
}

void RawPanel::setHeight(byte height) {
	_height = height;
}

byte RawPanel::getPanelId()  {
	return _panelId;
}

byte RawPanel::getWidth()  {
	return _width;
}

void RawPanel::setWidth(byte width) {
	_width = width;
}

byte RawPanel::getX()  {
	return _x;
}

void RawPanel::setX(byte x) {
	_x = x;
}

byte RawPanel::getY()  {
	return _y;
}

void RawPanel::setY(byte y) {
	_y = y;
}

 AADFonts* RawPanel::getDefaultFont()  {
	return _defaultFont;
}

void RawPanel::setDefaultFont( AADFonts* defaultFont) {
	_defaultFont = defaultFont;
}

unsigned int* RawPanel::getPanelBgPixelMap()  {
	return _bgPixelMap;
}

RawPanel::RawPanel(byte x, byte y, byte width, byte height, DesktopPane* desktopPane) :
	_x(x), _y(y), _height(height), _width(width), _desktopPane(desktopPane){
	this->_border = 1;
	this->_borderColor = COL_BLACK;
	this->_borderType = 0;
	this->_defaultFont = CONF_DEFAULT_FONT;
	this->_panelId = rand();
	this->_bgPixelMap = NULL; //(int*)malloc(sizeof(int)*(this->_height*this->_width));
	//this->_desktopPane = desktopPane;
}

RawPanel::RawPanel(byte x, byte y, byte width, byte height) :
		_x(x), _y(y), _height(height), _width(width){
	this->_border = 1;
	this->_borderColor = COL_BLACK;
	this->_borderType = 0;
	this->_defaultFont = CONF_DEFAULT_FONT;
	this->_panelId = rand();
	this->_bgPixelMap = NULL; //(int*)malloc(sizeof(int)*(this->_height*this->_width));
	this->_desktopPane = NULL;
}

void RawPanel::setDesktopPane(DesktopPane* pane){
	_desktopPane = pane;
}

void RawPanel::draw(void){

	if(_desktopPane != NULL){

		//get the background pixels from desktop panel and save it for restoring it later
		//unsigned int* desktopPixelMap = _desktopPane->getDesktopPixelMapFor(_x, _y, _width, _height);
		if(_bgPixelMap != NULL)
			delete _bgPixelMap;

		_bgPixelMap = _desktopPane->getDesktopPixelMapFor(_x, _y, _width, _height);
		//memcpy(_bgPixelMap, desktopPixelMap, _height*_width);

		//Draw Panel on desktop's frame
		_desktopPane->rectangle(_x, _y, _width, _height, COL_BLACK);
		//white border on left & top for 3D effect
		_desktopPane->v_line(_x+1, _y+1, _height-2, COL_WHITE); //left border
		_desktopPane->h_line(_x+1, _y+1, _width-2, COL_WHITE); //top border
		//blue border on right & bottom for 3D effect
		_desktopPane->v_line(_x+_width-1, _y+2, _height-4, COL_BLUE); //right border
		_desktopPane->h_line(_x+2, _y+_height-1, _width-4, COL_BLUE); //bottom border
		//fill in the panel with background color
		_desktopPane->fill(_x+2, _y+2, _width-4, _height-4, _bgColor);
	}

}

RawPanel::~RawPanel(){
	if(_bgPixelMap != NULL)
		delete _bgPixelMap;
}

/**************************************************************************************
 * 		TitlePanel class
 *************************************************************************************/
TitlePanel::TitlePanel(byte x, byte y, byte width, byte height, String* title, DesktopPane* desktopPane) :
		RawPanel(x, y, width, height, desktopPane){
	_title = title;
}

 String* TitlePanel::getTitle()  {
	return _title;
}

void TitlePanel::setTitle( String* title) {
	_title = title;
}

void TitlePanel::draw(void)
{
	RawPanel::draw();
	if(_desktopPane != NULL)
		_desktopPane->print_string(_x+2, _y+2, (char*)_title, COL_BLACK);
}

/**************************************************************************************
 * 		Widget class
 **************************************************************************************/
Widget::Widget(byte x, byte y, byte width, byte height, Panel* panel) :
	RawPanel(x, y, width, height){
	_panel = panel;
	_desktopPane = _panel->_desktopPane;
	_widgetId = rand();
}

byte Widget::getWidgetId(void){
	return _widgetId;
}

void Widget::setPanel(Panel* panel){
	_panel = panel;

	if(_panel->_desktopPane != NULL)
		_desktopPane = _panel->_desktopPane;
}

Panel* Widget::getPanel(void){
	return _panel;
}

void Widget::draw(void){
	RawPanel::draw();
}

/**************************************************************************************
 * 		Panel class
 **************************************************************************************/

Panel::Panel(byte x, byte y, byte height, byte width, DesktopPane* desktopPane) :
		RawPanel(x, y, height, width, desktopPane)
{
	_titlePanel = new TitlePanel("");

	_titlePanel->setX(_x-TITLE_PANE_DEFAULT_HEIGHT);
	_titlePanel->setY(_y);
	_titlePanel->setHeight(TITLE_PANE_DEFAULT_HEIGHT);
	_titlePanel->setWidth(_width);
	_titlePanel->setDesktopPane(desktopPane);

	_level = 0;
	_widgetCounter = 0;
}

Panel::Panel(byte x, byte y, byte height, byte width, String* title, DesktopPane* desktopPane) :
		RawPanel(x, y, height, width, desktopPane)
{
	_titlePanel = new TitlePanel(title);

	_titlePanel->setX(_x-TITLE_PANE_DEFAULT_HEIGHT);
	_titlePanel->setY(_y);
	_titlePanel->setHeight(TITLE_PANE_DEFAULT_HEIGHT);
	_titlePanel->setWidth(_width);
	_titlePanel->setDesktopPane(desktopPane);

	_level = 0;
	_widgetCounter = 0;
}

void Panel::setTitle(String* title){
	if(_titlePanel != NULL)
		_titlePanel->setTitle(title);
}

byte Panel::getLevel(void){
	return _level;
}

void Panel::setLevel(byte level){
	_level = level;
}

void Panel::add(Widget* widget){

	if(_widgetCounter < CONF_MAX_WIDGETS){
		_widgets[_widgetCounter] = widget;
		_widgets[_widgetCounter++]->setPanel(this);
		//_widgets[_widgetCounter++]->draw();
	}
}

void Panel::remove(Widget* widget){
	if(_widgetCounter > 0){
		for(int i=0; i < _widgetCounter; i++){
			if(_widgets[i]->_widgetId == widget->_widgetId){
				/*********************************************
				 * TODO: Restore widget background pixels on desktop
				 *********************************************/

				delete _widgets[i];

				//push back the pointers to fill in the empty space
				for(int j=i; j < _widgetCounter - 1; j++){
					_widgets[j] = _widgets[j+1];
				}
				_widgetCounter--;
			}
		}
	}
}

Widget* Panel::findWidget(int widgetId){
	for(int i=0; i<_widgetCounter; i++){
		if(_widgets[i]->_widgetId == widgetId)
			return _widgets[i];
	}

	return NULL;
}

void Panel::draw(void){
	_titlePanel->draw();
	RawPanel::draw();
	drawWidgets();
}

void Panel::refresh(void){
	draw();
}

void Panel::drawWidgets(void){
	for(int i=0; i<_widgetCounter; i++){
		_widgets[_widgetCounter+1]->draw();
	}
}

/********************************************************************************************
 * 		DesktopPane class
 ********************************************************************************************/
DesktopPane::DesktopPane(){
	_driver = CONF_LCD_DRIVER;
	_maxWidth = _driver->getMaxWidth();
	_maxHeight = _driver->getMaxHeight();
	_totalPixels = (_maxWidth * _maxHeight);
	_displayPixelMap = (int*)malloc(sizeof(int) * _totalPixels);

	for(int i=0; i<_totalPixels; i++){
		_displayPixelMap[i] = COL_WHITE;
	}
}

unsigned int* DesktopPane::getDesktopPixelMapFor(byte x, byte y, byte width, byte height){
	int *tempPixelMap = (int*)malloc(sizeof(int) * (width * height));
	int pixelCounter = 0;
	int startPos = 0;

	for(int j=0; j<height; j++){
		startPos = (_width*(y+j)) + x;
		for(int i=0; i< width; i++){
			tempPixelMap[pixelCounter++] = _displayPixelMap[startPos + i];
		}
	}

	return tempPixelMap;
}

void DesktopPane::add(Panel* panel){
	if(_panelCounter < CONF_MAX_PANELS){
		_panels[_panelCounter] = panel;
		_panels[_panelCounter]->setDesktopPane(this);
		_panels[_panelCounter++]->draw();

		refresh();
	}
}

void DesktopPane::remove(Panel* panel){
	if(_panelCounter > 0){
			for(int i=0; i < _panelCounter; i++){
				if(_panels[i]->_panelId == panel->_panelId){
					/*********************************************
					 * TODO: Restore panel background pixels on desktop
					 *********************************************/

					delete _panels[i];

					//push back the pointers to fill in the empty space
					for(int j=i; j < _panelCounter - 1; j++){
						_panels[j] = _panels[j+1];
					}
					_panelCounter--;
				}
			}
		}
}

Panel* DesktopPane::findPanel(int panelId){
	for(int i=0; i<_panelCounter; i++){
			if(_panels[i]->_panelId == panelId)
				return _panels[i];
		}

		return NULL;
}

void DesktopPane::refresh(void){
	_driver->renderFrame(_x, _y, _width, _height, _displayPixelMap, _totalPixels);
}

AADLCDDriversInterface* DesktopPane::getDriver(void){
	return _driver;
}

void DesktopPane::pixel(byte x, byte y, int color){}

void DesktopPane::print_char(byte x, byte y, unsigned char c, unsigned int color){}

void DesktopPane::print_string(byte x, byte y, char *str, unsigned int color){}

void DesktopPane::line(byte x0, byte y0, byte x1, byte y1, unsigned int color){}

void DesktopPane::circle(byte x0, byte y0, byte r, unsigned int color){}

void DesktopPane::v_line(byte x, byte y, byte h, unsigned int color){}

void DesktopPane::h_line(byte x, byte y, byte w, unsigned int color){}

void DesktopPane::rectangle(byte x, byte y, byte w, byte h, unsigned int color){}

void DesktopPane::fill(byte x, byte y, byte w, byte h, unsigned int color){}

void DesktopPane::bitmap(byte x, byte y, const byte *bitmap, byte w, byte h, unsigned int color){}


