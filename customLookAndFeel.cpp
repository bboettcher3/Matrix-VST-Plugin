#include "customLookAndFeel.h"


customLookAndFeel::customLookAndFeel()
{
	setColour(Slider::thumbColourId, Colours::red);
}

void customLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height,
	float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) 
{
	const float radius = jmin(width / 2, height / 2) - 4.0f;
	const float centreX = x + width * 0.5f;
	const float centreY = y + height * 0.5f;
	const float rx = centreX - radius;
	const float ry = centreY - radius;
	const float rw = radius * 2.0f;
	const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - 
		rotaryStartAngle);
	//fill
	g.setColour(Colours::darkblue);
	g.setOpacity(0.7f);
	g.fillEllipse(rx, ry, rw, rw);
	//outline
	g.setColour(Colours::navy);
	g.drawEllipse(rx, ry, rw, rw, 1.0f);

	Path p;
	const float pointerLength = radius * 0.8f;
	const float pointerThickness = 2.0f;
	p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
	p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
	//pointer
	g.setColour(Colours::yellow);
	g.fillPath(p);

}


customLookAndFeel::~customLookAndFeel()
{
}
