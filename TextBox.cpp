#include "TextBox.h"

TextBox::TextBox() : text_texture(NULL), mRenderer(NULL), mX(0), mY(0), mWidth(300), mHeight(100) {}

TextBox::~TextBox() {
	Free();
}
