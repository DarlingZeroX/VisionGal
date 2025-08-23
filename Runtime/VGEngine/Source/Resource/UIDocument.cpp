#include "Resource/UIDocument.h"

namespace VisionGal
{
	RmlUIDocument::RmlUIDocument()
	{
	}

	RmlUIDocument::~RmlUIDocument()
	{
		Close();
	}

	void RmlUIDocument::Close()
	{
		if (document && !isClosed)
		{
			document->Close();
			isClosed = true;
		}

	}
}
