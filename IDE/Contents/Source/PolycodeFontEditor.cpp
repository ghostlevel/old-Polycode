

#include "PolycodeFontEditor.h"

PolycodeFontEditor::PolycodeFontEditor() : PolycodeEditor(true){
	
}

PolycodeFontEditor::~PolycodeFontEditor() {
	
}

bool PolycodeFontEditor::openFile(String filePath) {
	
	CoreServices::getInstance()->getFontManager()->registerFont(filePath, filePath);
	
	
	
	grid = new ScreenImage("editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;
	
	grid->getTexture()->clamp = false;
	grid->getTexture()->recreateFromImageData();	
	
//	bg = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	bg = new UIBox("fontBox.png", 29,9,9,9, 10,10);	
	bg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bg->setPosition(-50,-50);
	
	
	anchor = new ScreenEntity();
	addChild(anchor);
	anchor->addChild(bg);
	anchor->snapToPixels = true;
	
	editorLabel = new ScreenLabel(filePath, L"ABCDEFGHIJKLM", 48, Label::ANTIALIAS_FULL);
	anchor->addChild(editorLabel);
	editorLabel2 = new ScreenLabel(filePath, L"NOPQRSTUVWXYZ", 48, Label::ANTIALIAS_FULL);
	editorLabel2->setPosition(0, 48);
	editorLabel->setPosition((editorLabel2->getWidth()-editorLabel->getWidth())/2, 0);
	anchor->addChild(editorLabel2);
	editorLabel3 = new ScreenLabel(filePath, L"abcdefghijklm", 48, Label::ANTIALIAS_FULL);
	editorLabel3->setPosition((editorLabel2->getWidth()-editorLabel3->getWidth())/2, 96);	
	anchor->addChild(editorLabel3);
	editorLabel4 = new ScreenLabel(filePath, L"nopqrstuvwxyz", 48, Label::ANTIALIAS_FULL);
	editorLabel4->setPosition((editorLabel2->getWidth()-editorLabel4->getWidth())/2, 144);		
	anchor->addChild(editorLabel4);
	editorLabel5 = new ScreenLabel(filePath, L"1234567890", 48, Label::ANTIALIAS_FULL);
	editorLabel5->setPosition((editorLabel2->getWidth()-editorLabel5->getWidth())/2, 192);			
	anchor->addChild(editorLabel5);

	editorLabel->setColor(0,0,0,1);
	editorLabel2->setColor(0,0,0,1);
	editorLabel3->setColor(0,0,0,1);
	editorLabel4->setColor(0,0,0,1);
	editorLabel5->setColor(0,0,0,1);
	
	bg->resizeBox(editorLabel2->getWidth()+100, 192+48+100);
	
	anchor->setHeight(192+48);
	anchor->setWidth(editorLabel2->getWidth());
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeFontEditor::Resize(int x, int y) {
	anchor->setPosition((x-anchor->getWidth()) /2, (y-anchor->getHeight()) /2);
	grid->setImageCoordinates(0,0,x,y);
}

