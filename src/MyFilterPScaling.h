#pragma once
#include "DrawingFilters.h"

class MyFilterPScaling :
	public FilterPointsScaling
{
public:
	MyFilterPScaling(double xCompress, double yCompress, FilterPoints* pNextFilter = nullptr)
		:FilterPointsScaling(xStretch, xCompress, yStretch, yCompress, pNextFilter), 
			pNextFilter(pNextFilter), 
			xCompress(xCompress), yCompress(yCompress), 
			xStretch(0), yStretch(0)
	{
		if (xCompress < 1) xCompress = 1;
		if (xCompress < 1) xCompress = 1;
	}
	virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		handleXthenY(surface, xVirtual, yVirtual, uiColour);
		return false; // We already coloured the pixel anyway
	}
	
private:
	FilterPoints* pNextFilter;
	double xStretch, yStretch, xCompress, yCompress;
	
	void handleXthenY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
	{
			if ((xVirtual % (int)xCompress) != 0) // We only need the nth pixel drawing now
				return; // Don't draw it
			xVirtual /= xCompress; // Shrink the coordinate by this amount
			xVirtual += 1;
			handleY(surface, xVirtual, yVirtual, uiColour);
	}

	void handleY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
	{
		if (yStretch > 1) // Stretch it!
		{
			yVirtual *= yStretch; // First multiply the point coordinates
			for (int i = 0; i < yStretch; i++)
			{
				// If no following filter, or filter permits it, then colour the pixel
				int yTest = yVirtual + i; // Need to be able to pass in by reference...
				if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yTest, uiColour))
					surface->rawSetPixel(xVirtual, yTest, uiColour); // Colour this pixel now
			}
		}
		else
		{
			//if ((yVirtual % yCompress) != 0) // We only need the nth pixel drawing now
			//	return; // Don't draw it
			yVirtual /= yCompress; // Shrink the coordinate by this amount
			if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
				surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel now
		}
	}
	
};