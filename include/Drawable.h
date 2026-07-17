#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "RenderTarget.h"
#include "RenderState.h"

class RenderTarget;

class Drawable
{
public:
	virtual ~Drawable() = default;
protected:
	friend class RenderTarget;
	virtual void draw(RenderTarget& target, RenderState state) const = 0;
};

#endif